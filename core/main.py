"""
--[[
-- Purrooser
-- File: main.py
-- Purpose: Start the browser
-- License: MIT
-- (C) Thoq
]]--
"""

######## Imports ########
import sys
from PySide6.QtWidgets import QApplication
from Light import Renderer
from Lambda import Server

######## Main function ########
def main():
    lambda_server = Server()
    light_renderer = Renderer(lambda_server)
    light_renderer.show()

######## Entry point ########
if __name__ == "__main__":
    app = QApplication(sys.argv)
    try:
        main()
    except KeyboardInterrupt:
        print("Goodbye!")
    sys.exit(app.exec())
