from socket import *
import sys
import argparse
import os
import datetime

# -------------------------- Command Line argument parsing ---------------------------- #
# Make a parser instance
parser = argparse.ArgumentParser(description = 'Part 2')
# Add the port arg
parser.add_argument('-p', '--port', type=int, help='port', required=True)
# Add the directory arg
parser.add_argument('-d', '--directory' ,help='directory', required=True)
# read arguments provided to the program
args = parser.parse_args()
port = args.port
directory = args.directory
#----------------------#


#------- Checks -------- #
if port <= 0 or port >= 65536:
    sys.stderr.write("Error: Port number out of range.\n")
    sys.exit(1)
    
elif 1024 <= port <= 49151:
    sys.stderr.write("Warning: Port number is a registered port.\n")

if os.path.exists(directory) == False:
    sys.stderr.write("Error: Root directory does not exist.\n")
    sys.exit(1)
#----------------------#

# All supported extension types
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

# Safety measure will opening socket
with socket(AF_INET, SOCK_STREAM) as serverSocket:
    # assign port
    serverPort = port
    # Bind IP and Port to socket
    serverSocket.bind(('', serverPort))
    # listen(1) means that the server will only entertain 1 connection at a time.
    serverSocket.listen(1)
    # Getting the server IP -> localhost
    serverIp = serverSocket.getsockname()[0]

    # Print statment
    print("Welcome socket created: {}, {}".format(serverIp, serverPort))

    # Keep listening for connections
    while True:
        # Here when some client requests for a connection, we listen to it (3-way handshake first)
        connectionSocket, addr = serverSocket.accept()
        # Get the client's IP and port details
        client_ip = addr[0]
        client_port = addr[1]

        # Initialing parent variables for content-length and Headers
        CL = 0
        HS = ''

        # Print statement
        print('Connection requested from {}, {}'.format(client_ip, client_port))

        # Get the request from the client
        HTTP_request = connectionSocket.recv(1024).decode()
        # Get the HTTP request line
        request_line = HTTP_request.split('\r\n')[0]
        # Extract the request type, filepath and the version
        req_type, filepath, ver = request_line.split(' ')
        # Get the extension of the file
        fname = filepath.split('/')[-1]
        # Building the path for looking within directory upon request received
        filepath = directory + filepath

        # If anything apart from 'GET' request received, return 501 with relevant headers
        if (req_type != 'GET'):
            headers = [
                "HTTP/1.1 501 Not Implemented",
                "Content-Length: 0",
                "Date: {}".format(datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")),
                "Connection: close"
            ]
            headers_str = "\r\n".join(headers)
            headers = headers_str.encode()
            message = headers + b"\r\n\r\n"
            connectionSocket.sendall(message)
            connectionSocket.close()

        # If anything apart from 'HTTP/1.1' used, return 505 with relevant headers
        elif (ver != 'HTTP/1.1'):
            headers = [
                "HTTP/1.1 505 HTTP Version Not Supported",
                "Content-Length: 0",
                "Date: {}".format(datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")),
                "Connection: close"
            ]
            headers_str = "\r\n".join(headers)
            headers = headers_str.encode()
            message = headers + b"\r\n\r\n"
            connectionSocket.sendall(message)
            connectionSocket.close()

        # If file doesn't exist, return 404 with relevant headers.
        elif (os.path.exists(filepath) == False):
            headers = [
                "HTTP/1.1 404 Not Found",
                "Content-Length: 0",
                "Date: {}".format(datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")),
                "Connection: close"
            ]
            headers_str = "\r\n".join(headers)
            headers = headers_str.encode()
            message = headers + b"\r\n\r\n"
            connectionSocket.sendall(message)
            connectionSocket.close()

        # If conditions match
        elif (os.path.exists(filepath) == True and ver == 'HTTP/1.1' and req_type == 'GET'):
            # Read the requested file
            with open(filepath, "rb") as f:
                content = f.read()

            # Depending on extension type, get content-type
            content_type = extension_type.get(fname.split('.')[-1], 'application/octet-stream')
            # Get content-length
            content_length = len(content)
            # Also, save to parent variable
            CL = content_length

            # Get the last-modified and current time
            current_time = datetime.datetime.now().strftime("%a, %d %b %Y %H:%M:%S GMT")
            last_modified = os.path.getmtime(filepath)
            local_time = datetime.datetime.fromtimestamp(last_modified)
            formatted_time = local_time.strftime("%a, %d %b %Y %H:%M:%S GMT")

            # Build status line and headers
            headers = [
                "HTTP/1.1 200 OK",
                "Content-Type: {}".format(content_type),
                "Content-Length: {}".format(content_length),
                "Last-Modified: {}".format(formatted_time),
                "Date: {}".format(current_time),
                "Connection: close"
            ]

            # append \r\n after each line
            headers_str = "\r\n".join(headers)
            # Encode string to bytes
            headers = headers_str.encode()
            # end the final header line with '\r\n\r\n' and then join the content to it
            message = headers + b"\r\n\r\n" + content
            # Finally send the entire response to the client
            connectionSocket.sendall(message)
            # Also save the HEAD information to the parent variable
            HS = headers_str

            # close connection
            connectionSocket.close()

        # Print statement
        print(f"Connection to {addr[0]}, Source port {addr[1]} is closed.")

        # Open the CSV file for writing
        with open("adwivediSocketOutput.csv", mode="a") as file:
            data = "Client request served, 4-Tuple:, {}, {}, {}, {}, Requested URL, {}, {}, Bytes transmitted:, {}\n".format(serverIp,serverPort,client_ip,client_port,filepath,request_line,CL)
            file.write(data)
        # Reset Parent Variable
        CL = 0
        # Open the CSV file for writing
        with open("adwivediHTTPResponses.txt", mode="a") as file:
            data = HS + "\n\n"
            file.write(data)
        # Reset Parent Variable
        HS = ''

