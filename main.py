from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QToolBar, QPushButton
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtCore import QUrl, Qt
import sys
import threading
import os
from http.server import SimpleHTTPRequestHandler, HTTPServer

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Purrooser")
        self.setGeometry(100, 100, 1600, 900)

        self.setup_ui()
        self.start_http_server()
        self.load_local_file()

    def setup_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        self.web_view = QWebEngineView()
        layout.addWidget(self.web_view)

        toolbar = QToolBar()
        self.addToolBar(toolbar)

        # Back button
        back_button = QPushButton("<")
        back_button.clicked.connect(self.web_view.back)
        toolbar.addWidget(back_button)

         # Reload button
        reload_button = QPushButton("↻")
        reload_button.clicked.connect(self.web_view.reload)
        toolbar.addWidget(reload_button)

        # Forward button
        forward_button = QPushButton(">")
        forward_button.clicked.connect(self.web_view.forward)
        toolbar.addWidget(forward_button)

        # Home button
        home_button = QPushButton("⌂")
        home_button.clicked.connect(self.load_local_file)
        toolbar.addWidget(home_button)

        self.web_view.loadFinished.connect(self.on_load_finished)

        self.set_dark_mode()

    def on_load_finished(self):
        pass

    def load_local_file(self):
        self.web_view.load(QUrl("http://localhost:54365/index.html"))

    def start_http_server(self):
        os.chdir(os.path.join(os.path.dirname(__file__), 'browser'))

        server_address = ('', 54365)
        httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)
        threading.Thread(target=httpd.serve_forever, daemon=True).start()

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
            self.web_view.reload()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())