import sys

from PySide6.QtWidgets import QApplication

from Light import Renderer
from Lambda import Server


def main():
    lambda_server = Server()
    light_renderer = Renderer(lambda_server)
    light_renderer.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    try:
        main()
    except KeyboardInterrupt:
        print("Goodbye!")
    sys.exit(app.exec())
