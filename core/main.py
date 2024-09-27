import sys
from PySide6.QtWidgets import QApplication
from http_server import HttpServer
from main_window import MainWindow

if __name__ == "__main__":
    try:
        app = QApplication(sys.argv)
        http_server = HttpServer()
        window = MainWindow(http_server)
        window.show()
        sys.exit(app.exec())
    except KeyboardInterrupt:
        print("Goodbye!")
