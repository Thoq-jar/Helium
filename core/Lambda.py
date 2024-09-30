import os
import threading
from http.server import SimpleHTTPRequestHandler, HTTPServer


# noinspection PyTypeChecker
class Server:
    def __init__(self, port=54365):
        self.port = port
        self.server_address = ('', self.port)

    def start(self):
        os.chdir(os.path.join(os.path.dirname(__file__), '..', 'ui'))
        httpd = HTTPServer(self.server_address, SimpleHTTPRequestHandler)
        threading.Thread(target=httpd.serve_forever, daemon=True).start()
