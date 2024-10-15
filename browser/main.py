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

######## Main function ########
def main():
    light_renderer = Renderer()
    light_renderer.show()

######## Entry point ########
if __name__ == "__main__":
    app = QApplication(sys.argv)
    try:
        main()
    except KeyboardInterrupt:
        print("Goodbye!")
    sys.exit(app.exec())
