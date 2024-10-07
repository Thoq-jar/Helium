"""
--[[
-- Purrooser
-- File: Light.py
-- Purpose: Frontend for the Light renderer
-- License: MIT
-- (C) Thoq
]]--
"""

############################## Imports ##############################
import os
import platform
import re
from lupa import LuaRuntime
from PySide6.QtCore import QUrl, Qt
from PySide6.QtGui import QIcon
from PySide6.QtWebEngineCore import QWebEnginePage, QWebEngineProfile
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtWidgets import QMainWindow, QVBoxLayout, QWidget, QToolBar, QPushButton, QTabWidget, QLineEdit


############################## Engine Class ##############################
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


############################## Renderer Class ##############################
class Renderer(QMainWindow):
    def __init__(self, http_server):
        super().__init__()

        self.lua = LuaRuntime(unpack_returned_tuples=True)

        lua_script_path = os.path.join('core', 'lua', 'main.lua')
        if os.path.exists(lua_script_path):
            self.load_lua_script(lua_script_path)
        else:
            print("Error loading lua!")

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

    ############################## Setup Web Storage ( WIP ) ##############################
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

    ############################## Setup UI ##############################
    def setup_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        self.apply_css()
        self.tab_widget.currentChanged.connect(self.update_buttons)
        layout.addWidget(self.tab_widget)

        self.add_new_tab()

    ############################## Load Lua Script(s) ##############################
    def load_lua_script(self, script_path):
        if os.path.exists(script_path):
            with open(script_path, 'r') as lua_file:
                lua_code = lua_file.read()
            self.lua.execute(lua_code)
            self.lua.globals().PrintInfo()
            self.lua.globals().CreateUI(self)

    ############################## Handle Dark Mode ##############################
    def toggle_dark_light_mode(self):
        if platform.system() not in ["Darwin", "Windows"]:
            self.is_dark_mode = not self.is_dark_mode
            if self.is_dark_mode:
                self.setStyleSheet("background-color: #2E2E2E; color: white;")
            else:
                self.setStyleSheet("background-color: white; color: black;")

    ############################## Add New Tab ##############################
    def add_new_tab(self):
        new_tab = QWebEngineView()
        new_tab.setPage(CustomWebEnginePage(self.profile))
        self.tab_widget.addTab(new_tab, "New Tab")
        self.tab_widget.setCurrentWidget(new_tab)
        new_tab.loadFinished.connect(self.on_load_finished)
        new_tab.page().titleChanged.connect(lambda title: self.update_tab_title(new_tab, title))
        new_tab.load(QUrl("http://localhost:54365/index.html"))

    ############################## Event Handler For Finsihed Loading Site ##############################
    def on_load_finished(self, success):
        self.update_buttons()
        if not success:
            self.current_web_view().load(QUrl("http://localhost:54365/error.html"))
        self.update_url_bar()

    ############################## Update Tab Title Based On Website ##############################
    def update_tab_title(self, web_view, title):
        index = self.tab_widget.indexOf(web_view)
        if index != -1:
            self.tab_widget.setTabText(index, title if title else "Untitled")
    
    ############################## Close Current Tab ##############################
    def close_current_tab(self):
        current_index = self.tab_widget.currentIndex()
        if current_index != -1:
            self.tab_widget.removeTab(current_index)

    ############################## Return View ##############################
    def current_web_view(self):
        return self.tab_widget.currentWidget()

    ############################## Update Buttons ##############################
    def update_buttons(self):
        current_view = self.current_web_view()
        if current_view:
            pass

    ############################## Load Homepage ##############################
    def load_local_file(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.load(QUrl("http://localhost:54365/index.html"))
        else:
            self.add_new_tab()

    ############################## Handle Back ##############################
    def back(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.back()

    ############################## Handle Forword ##############################
    def forward(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.forward()

    ############################## Handle Reload ##############################
    def reload(self):
        current_view = self.current_web_view()
        if current_view:
            current_view.reload()

    ############################## Go To A Purr URL ##############################
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

    ############################## Change URL Bar ##############################
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

    ############################## Add Styles ##############################
    def apply_css(self):
        css_file_path = os.path.join('ui', 'core', 'core.css')
        if os.path.exists(css_file_path):
            with open(css_file_path, 'r') as css_file:
                dark_stylesheet = css_file.read()
            self.setStyleSheet(dark_stylesheet)
        else:
            print(f"[ERR] CSS file not found: {css_file_path}")

    ############################## Handle Keypress ##############################
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

    ############################## Create Toolbar ##############################
    def addToolBar(self, name):
        toolbar = QToolBar(name)
        super().addToolBar(toolbar) 
        return toolbar

    ############################## Create Buttons ##############################
    def addButton(self, toolbar, text, callback):
        button = QPushButton(text)
        button.clicked.connect(callback)
        toolbar.addWidget(button)
        return button

    ############################## Create URL Bar ##############################
    def addUrlBar(self, toolbar, callback):
        url_bar = QLineEdit()
        url_bar.returnPressed.connect(callback)
        toolbar.addWidget(url_bar)
        self.url_bar = url_bar
        return url_bar

    ############################## Check if on Linux/FreeBSD ##############################
    def is_dark_mode_supported(self):
        return platform.system() not in ["Darwin", "Windows"]