from PySide6.QtWidgets import QMainWindow, QVBoxLayout, QWidget, QToolBar, QPushButton, QTabWidget, QHBoxLayout, QLabel
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtCore import QUrl, Qt
import sys

class MainWindow(QMainWindow):
    def __init__(self, http_server):
        super().__init__()

        self.http_server = http_server
        self.setWindowTitle("Purrooser")
        self.setGeometry(100, 100, 1600, 900)

        self.setup_ui()
        self.http_server.start()
        self.load_local_file()

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

        forward_button = QPushButton(">")
        forward_button.clicked.connect(self.current_web_view().forward)
        toolbar.addWidget(forward_button)

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
        self.tab_widget.addTab(new_tab, "New Tab")
        self.tab_widget.setCurrentWidget(new_tab)
        new_tab.loadFinished.connect(self.on_load_finished)

        new_tab.load(QUrl("http://localhost:54365/index.html"))

    def create_tab_label(self, title):
        tab_label = QWidget()
        layout = QHBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)

        title_label = QLabel(title)
        layout.addWidget(title_label)

        close_button = QPushButton("X")
        close_button.setFixedSize(20, 20)
        close_button.clicked.connect(lambda: self.close_tab(title))
        layout.addWidget(close_button)

        tab_label.setLayout(layout)
        return tab_label

    def on_load_finished(self, success):
        pass
          
    def close_current_tab(self):
        current_index = self.tab_widget.currentIndex()
        if current_index != -1:
            self.tab_widget.removeTab(current_index)

    def close_tab(self, title):
        index = self.tab_widget.indexOf(self.tab_widget.findChild(QWidget, title))
        if index != -1:
            self.tab_widget.removeTab(index)

    def current_web_view(self):
        return self.tab_widget.currentWidget()

    def update_buttons(self):
        current_view = self.current_web_view()
        if current_view:
            self.back_button.setEnabled(current_view.history().canGoBack())
            self.forward_button.setEnabled(current_view.history().canGoForward())

    def load_local_file(self):
        self.current_web_view().load(QUrl("http://localhost:54365/index.html"))

    def set_dark_mode(self):
        dark_stylesheet = """
        QMainWindow {
            background-color: #2E2E2E;
        }
        QToolBar {
            background-color: #3C3C3C;
        }
        QPushButton {
            background-color: #4C4C4C;
            color: white;
            border: none;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: #5C5C5C;
        }
        """
        self.setStyleSheet(dark_stylesheet)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_F5 or (event.key() == Qt.Key_R and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier)):
            self.current_web_view().reload()
        elif event.key() == Qt.Key_T and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.add_new_tab()
        elif event.key() == Qt.Key_W and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close_current_tab()
        elif event.key() == Qt.Key_Q and (event.modifiers() & Qt.ControlModifier or event.modifiers() & Qt.MetaModifier):
            self.close()
