import os
import platform
import re

from PySide6.QtCore import QUrl, Qt
from PySide6.QtGui import QIcon
from PySide6.QtWebEngineCore import QWebEnginePage, QWebEngineProfile
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtWidgets import QMainWindow, QVBoxLayout, QWidget, QToolBar, QPushButton, QTabWidget, QLineEdit


# noinspection PyMethodOverriding,HttpUrlsUsage,PyPep8Naming
class CustomWebEnginePage(QWebEnginePage):
    def acceptNavigationRequest(self, url: QUrl, isMainFrame: bool) -> bool:
        if url.host() == "localhost" and url.port() == 54365:
            self.load(QUrl("purr://newtab"))
            return False
        if url.scheme() == "http" and not (url.host() in ["localhost", "0.0.0.0", "127.0.0.1"]):
            https_url = url.toString().replace("http://", "https://")
            self.load(QUrl(https_url))
            return False
        return super().acceptNavigationRequest(url, isMainFrame)


# noinspection PyUnresolvedReferences,HttpUrlsUsage
class Renderer(QMainWindow):
    def __init__(self, http_server):
        super().__init__()
        self.forward_button = None
        self.back_button = None
        self.url_bar = None
        self.tab_widget = QTabWidget()
        self.profile = QWebEngineProfile("web_profile", self)
        self.http_server = http_server
        self.setWindowTitle("Purrooser")
        self.setGeometry(100, 100, 900, 600)
        self.setWindowIcon(QIcon("assets/icon.ico"))

        self.setup_profile()
        self.setup_ui()
        self.http_server.start()
        self.load_local_file()
        self.is_dark_mode = True

    def setup_profile(self):
        storage_path = os.path.join(os.getcwd(), "web_storage")
        if not os.path.exists(storage_path):
            try:
                os.makedirs(storage_path)
            except Exception as e:
                print(f"Error creating storage directory: {e}")
                return

        self.profile.setPersistentStoragePath(storage_path)
        self.profile.setPersistentCookiesPolicy(QWebEngineProfile.ForcePersistentCookies)
        self.profile.setHttpCacheType(QWebEngineProfile.DiskHttpCache)
        self.profile.setHttpCacheMaximumSize(0)

    def setup_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        toolbar = QToolBar()
        self.addToolBar(toolbar)

        back_button = QPushButton("<")
        back_button.clicked.connect(self.back)
        toolbar.addWidget(back_button)
        self.back_button = back_button

        forward_button = QPushButton(">")
        forward_button.clicked.connect(self.forward)
        toolbar.addWidget(forward_button)
        self.forward_button = forward_button

        reload_button = QPushButton("↻")
        reload_button.clicked.connect(self.reload)
        toolbar.addWidget(reload_button)

        home_button = QPushButton("⌂")
        home_button.clicked.connect(self.load_local_file)
        toolbar.addWidget(home_button)

        self.url_bar = QLineEdit()
        self.url_bar.returnPressed.connect(self.navigate_to_url)
        toolbar.addWidget(self.url_bar)

        new_tab_button = QPushButton("+")
        new_tab_button.clicked.connect(self.add_new_tab)
        toolbar.addWidget(new_tab_button)

        close_tab_button = QPushButton("X")
        close_tab_button.clicked.connect(self.close_current_tab)
        toolbar.addWidget(close_tab_button)

        self.apply_css()

        if platform.system() not in ["Darwin", "Windows"]:
            toggle_button = QPushButton("🌙")
            toggle_button.clicked.connect(self.toggle_dark_light_mode)
            toolbar.addWidget(toggle_button)

        self.tab_widget.currentChanged.connect(self.update_buttons)
        layout.addWidget(self.tab_widget)

        self.add_new_tab()

    def toggle_dark_light_mode(self):
        if platform.system() not in ["Darwin", "Windows"]:
            self.is_dark_mode = not self.is_dark_mode
            if self.is_dark_mode:
                self.setStyleSheet("background-color: #2E2E2E; color: white;")
            else:
                self.setStyleSheet("background-color: white; color: black;")

    def add_new_tab(self):
        new_tab = QWebEngineView()
        new_tab.setPage(CustomWebEnginePage(self.profile))
        self.tab_widget.addTab(new_tab, "New Tab")
        self.tab_widget.setCurrentWidget(new_tab)
        new_tab.loadFinished.connect(self.on_load_finished)
        new_tab.page().titleChanged.connect(lambda title: self.update_tab_title(new_tab, title))
        new_tab.load(QUrl("http://localhost:54365/index.html"))

    def on_load_finished(self, success):
        self.update_buttons()
        if not success:
            self.current_web_view().load(QUrl("http://localhost:54365/error.html"))
        self.update_url_bar()

    def update_tab_title(self, web_view, title):
        index = self.tab_widget.indexOf(web_view)
        if index != -1:
            self.tab_widget.setTabText(index, title if title else "Untitled")

    def close_current_tab(self):
        current_index = self.tab_widget.currentIndex()
        if current_index != -1:
            self.tab_widget.removeTab(current_index)

    def current_web_view(self):
        return self.tab_widget.currentWidget()

    def update_buttons(self):
        current_view = self.current_web_view()
        if current_view:
            self.back_button.setEnabled(current_view.history().canGoBack())
            self.forward_button.setEnabled(current_view.history().canGoForward())

    def load_local_file(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.load(QUrl("http://localhost:54365/index.html"))
        else:
            self.add_new_tab()

    def back(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.back()

    def forward(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.forward()

    def reload(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.reload()

    def navigate_to_url(self):
        url_text = self.url_bar.text().strip()
        url_mapping = {
            "purr://newtab": "http://localhost:54365/index.html",
            "purr://error": "http://localhost:54365/error.html",
            "purr://about": "http://localhost:54365/about.html",
            "purr://kitty": "http://localhost:54365/kitty.html",
            "purr://settings": "http://localhost:54365/settings.html",
            "purr://weather": "http://localhost:54365/weather.html",
        }

        if url_text in url_mapping:
            self.current_web_view().load(QUrl(url_mapping[url_text]))
        else:
            tld_pattern = r'\.[a-zA-Z]{2,}'
            if not re.search(tld_pattern, url_text):
                search_url = f"https://www.google.com/search?q={url_text}"
                self.current_web_view().load(QUrl(search_url))
            else:
                if not url_text.startswith("http://") and not url_text.startswith("https://"):
                    url_text = "http://" + url_text
                self.current_web_view().load(QUrl(url_text))

    def update_url_bar(self):
        current_view = self.current_web_view()
        if current_view:
            current_url = current_view.url().toString()
            url_display_mapping = {
                "http://localhost:54365/index.html": "purr://newtab",
                "http://localhost:54365/error.html": "purr://error",
                "http://localhost:54365/about.html": "purr://about",
                "http://localhost:54365/kitty.html": "purr://kitty",
                "http://localhost:54365/settings.html": "purr://settings",
                "http://localhost:54365/weather.html": "purr://weather",
            }

            display_text = url_display_mapping.get(current_url, current_url)
            self.url_bar.setText(display_text)

    def apply_css(self):
        css_file_path = os.path.join('ui', 'core', 'core.css')
        if os.path.exists(css_file_path):
            with open(css_file_path, 'r') as css_file:
                dark_stylesheet = css_file.read()
            self.setStyleSheet(dark_stylesheet)
        else:
            print(f"[ERR] CSS file not found: {css_file_path}")

    def keyPressEvent(self, event):
        if (event.key() == Qt.Key_F5 or
                (event.key() == Qt.Key_R and
                 (event.modifiers() & Qt.ControlModifier or
                  event.modifiers() &
                  Qt.MetaModifier))):
            self.current_web_view().reload()
        elif event.key() == Qt.Key_T and (
                event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.add_new_tab()
        elif event.key() == Qt.Key_W and (
                event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close_current_tab()
        elif event.key() == Qt.Key_Q and (
                event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close()
