import sys
from PySide6.QtWidgets import QApplication
from core.http_server import HttpServer
from core.main_window import MainWindow

if __name__ == "__main__":
    try:
        app = QApplication(sys.argv)
        http_server = HttpServer()
        window = MainWindow(http_server)
        window.show()
        sys.exit(app.exec())
    except KeyboardInterrupt:
        print("Goodbye!")