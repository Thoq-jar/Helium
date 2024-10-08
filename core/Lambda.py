"""
--[[
-- Purrooser
-- File: Lambda.py
-- Purpose: Lambda Server
-- License: MIT
-- (C) Thoq
]]--
"""

import os
import threading
from http.server import SimpleHTTPRequestHandler, HTTPServer


######## Server Class #########
class Server:
    ######## __init__ server ########
    def __init__(self, port=54365):
        self.port = port
        self.server_address = ('127.0.0.1', self.port)
    
    ######## Start the server ########
    def start(self):
        os.chdir(os.path.join(os.path.dirname(__file__), '..', 'ui'))
        httpd = HTTPServer(self.server_address, SimpleHTTPRequestHandler)
        threading.Thread(target=httpd.serve_forever, daemon=True).start()
