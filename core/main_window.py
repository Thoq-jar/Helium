import os
from PySide6.QtCore import QUrl, Qt
from PySide6.QtGui import QIcon
from PySide6.QtWebEngineCore import QWebEnginePage, QWebEngineProfile
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtWidgets import QMainWindow, QVBoxLayout, QWidget, QToolBar, QPushButton, QTabWidget


class MainWindow(QMainWindow):
    def __init__(self, http_server):
        super().__init__()
        self.http_server = http_server
        self.setWindowTitle("Purrooser")
        self.setGeometry(100, 100, 1600, 900)

        self.setup_profile()
        self.setup_ui()
        self.setWindowIcon(QIcon("assets/icon.ico"))
        self.http_server.start()
        self.load_local_file()

    def setup_profile(self):
        storage_path = os.path.join(os.getcwd(), "web_storage")
        if not os.path.exists(storage_path):
            try:
                os.makedirs(storage_path)
            except Exception as e:
                print(f"Error creating storage directory: {e}")
                return
        self.profile = QWebEngineProfile.defaultProfile()
        self.profile.setPersistentStoragePath(storage_path)

    def setup_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout()
        central_widget.setLayout(layout)
        self.tab_widget = QTabWidget()
        layout.addWidget(self.tab_widget)
        self.add_new_tab()
        toolbar = QToolBar()
        self.addToolBar(toolbar)

        back_button = QPushButton("<")
        back_button.clicked.connect(self.current_web_view().back)
        toolbar.addWidget(back_button)
        self.back_button = back_button

        forward_button = QPushButton(">")
        forward_button.clicked.connect(self.current_web_view().forward)
        toolbar.addWidget(forward_button)
        self.forward_button = forward_button

        reload_button = QPushButton("↻")
        reload_button.clicked.connect(self.current_web_view().reload)
        toolbar.addWidget(reload_button)

        home_button = QPushButton("⌂")
        home_button.clicked.connect(self.load_local_file)
        toolbar.addWidget(home_button)

        new_tab_button = QPushButton("+")
        new_tab_button.clicked.connect(self.add_new_tab)
        toolbar.addWidget(new_tab_button)

        close_tab_button = QPushButton("X")
        close_tab_button.clicked.connect(self.close_current_tab)
        toolbar.addWidget(close_tab_button)

        self.tab_widget.currentChanged.connect(self.update_buttons)
        self.set_dark_mode()

    def add_new_tab(self):
        new_tab = QWebEngineView()
        new_tab.setPage(QWebEnginePage(self.profile))
        self.tab_widget.addTab(new_tab, "New Tab")
        self.tab_widget.setCurrentWidget(new_tab)
        new_tab.loadFinished.connect(self.on_load_finished)
        new_tab.page().titleChanged.connect(lambda title: self.update_tab_title(new_tab, title))
        new_tab.load(QUrl("http://localhost:54365/index.html"))

    def on_load_finished(self, success):
        if not success:
            self.current_web_view().load(QUrl("http://localhost:54365/error.html"))

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

    def set_dark_mode(self):
        css = os.path.join('..', 'ui', 'core', 'window.css')
        if os.path.exists(css):
            with open(css, 'r') as css_file:
                dark_stylesheet = css_file.read()
            self.setStyleSheet(dark_stylesheet)
        else:
            print(f"CSS file not found: {css}")

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_F5 or (event.key() == Qt.Key_R and
                (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier)):
            self.current_web_view().reload()
        elif event.key() == Qt.Key_T and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.add_new_tab()
        elif event.key() == Qt.Key_W and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close_current_tab()
        elif event.key() == Qt.Key_Q and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close()
