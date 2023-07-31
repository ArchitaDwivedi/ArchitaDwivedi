from socket import *
import sys
import argparse
import os
import datetime

parser = argparse.ArgumentParser(description = 'Part 2')
parser.add_argument('-p', '--port', type=int,help='port', required=True)
parser.add_argument('-d', '--directory' ,help='directory', required=True)
args = parser.parse_args()
port = args.port
directory = args.directory
#------- Checks -------- #
if port < 0 or port > 65536:
    sys.stderr.write("Error: Port number out of range.\n")
    sys.exit(1)
    
elif 1024 <= port <= 49151:
    sys.stderr.write("Warning: Port number is a registered port.\n")

if not os.path.exists(directory):
    sys.stderr.write("Error: Root directory does not exist.\n")
    sys.exit(1)
#----------------------#
# Construct HTTP response headers
extension_type= {
    "html": "text/html",
    "png": "image/png",
    "jpg": "image/jpeg",
    "jpeg": "image/jpeg",
    "gif": "image/gif",
    'csv': 'text/csv',
    'zip': 'application/zip',
    'txt': 'text/plain',
    'doc': 'application/msword',
    'docx': 'application/vnd.openxmlformats-officedocument.wordprocessingml.document'
}

serverPort = port
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
serverIp = serverSocket.getsockname()[0]
CL = ''
print("Welcome socket created: {}, {}".format(serverIp, serverPort))

while True:
    connectionSocket, addr = serverSocket.accept()
    client_ip = addr[0]
    client_port = addr[1]
    print('Connection requested from {}, {}'.format(client_ip, client_port))
    HTTP_request = connectionSocket.recv(1024).decode()
    
    status_line = HTTP_request.split('\r\n')[0]
    req_type, filepath, ver = status_line.split(' ')
    fname = filepath.split('/')[-1]
    if (req_type != 'GET'):
        connectionSocket.send("HTTP/1.1 501 Not Implemented\r\n\r\n".encode())
        connectionSocket.close()
    elif (os.path.exists(filepath) == False):
        connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())
        connectionSocket.close()
    elif (ver != 'HTTP/1.1'):
        connectionSocket.send("HTTP/1.1 505 HTTP Version Not Supported\r\n\r\n".encode())
        connectionSocket.close()
    else:
        with open(filepath, "rb") as f:
            content = f.read()

        content_type = extension_type.get(fname.split('.')[-1], 'application/octet-stream')
        content_length = len(content)
        CL = CL + content_length
        current_time = datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")
        last_modified = os.path.getmtime(filepath)
        local_time = datetime.datetime.fromtimestamp(last_modified)
        formatted_time = local_time.strftime("%a, %d %b %Y %H:%M:%S GMT")

        headers = [
            "HTTP/1.1 200 OK",
            "Content-Type: {}".format(content_type),
            "Content-Length: {}".format(content_length),
            "Last-Modified: {}".format(formatted_time),
            "Date: {}".format(current_time),
            "Connection: close"
        ]
        headers_str = "\r\n".join(headers)
        headers = headers_str.encode()
        message = headers + b"\r\n\r\n" + content
        connectionSocket.sendall(message)


    # A safety connection.close() in case some socket is open.
    connectionSocket.close()

    print(f"Connection to {addr[0]}, Source port {addr[1]} is closed.")

    # Open the CSV file for writing
    with open("adwivediSocketOutput.csv", mode="a") as file:
        data = "Client request served, 4-Tuple:, {}, {}, {}, {}, Requested URL, {}, {}, Bytes transmitted:, {}\n".format(serverIp,serverPort,client_ip,client_port,filepath,status_line,CL)
        file.write(data)
    CL = ''
    # Open the CSV file for writing
    with open("adwivediHTTPResponses.txt", mode="a") as file:
        data = headers_str + "\n\n"
        file.write(data)
