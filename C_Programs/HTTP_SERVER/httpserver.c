#include "httpserver.h"
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h> // for openf
#include <unistd.h> // for close
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>

// To calculate a string's length
int string_length(char *ch) {
    int i;
    for (i = 0; ch[i] != '\0'; ++i)
        ;
    return i;
}

// Provided to us in bind.c
int create_listen_socket(uint16_t port) {
    signal(SIGPIPE, SIG_IGN);
    if (port == 0) {
        return -1;
    }
    struct sockaddr_in addr;
    // This is the socket i.e like file handler
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        return -2;
    }
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr *) &addr, sizeof addr) < 0) {
        return -3;
    }
    if (listen(listenfd, 500) < 0) {
        return -4;
    }
    return listenfd;
}

// This function checks to see if a file is a regular file!
int is_regular_file(const char *filepath) {
    struct stat file_to_check;
    stat(filepath, &file_to_check);
    return S_ISREG(file_to_check.st_mode);
}

// Main Head Function
void HEAD_handler(int clientSocket, char *FL) {
    // getting file size
    struct stat st;
    if (stat(FL, &st))
        exit(EXIT_FAILURE);
    int fz = st.st_size;
    char filesize[100];
    sprintf(filesize, "%d\r\n\r\n", fz);

    // define local buffers for strong modularity
    char HEADbuff[4096];
    memset(HEADbuff, 0, 4096);

    // open the actual file to GET from
    int head_file_descriptor = open(FL, O_RDONLY);
    // If file-opening was unsuccessful, throw back an error code!
    if (head_file_descriptor == -1) {
        printf("lol bye\n");
        return;
    }

    // This is what we will use to write to our client socket
    // This because the request + header will be upto 2048
    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: ";

    // Write client response
    write(clientSocket, response, string_length(response));
    write(clientSocket, filesize, string_length(filesize));

    //memset
    memset(response, 0, string_length(response));
    // close the file and return
    close(head_file_descriptor);
    return;
}

// Main PUT_handler Function
int PUT_handler(int fd, char *message) {

    // write to the message to the file description
    int wb = write(fd, message, string_length(message));
    return wb;
}

// Main GET_handler Function
void GET_handler(int clientSocket, char *FL) {

    // getting file size
    struct stat st;
    if (stat(FL, &st))
        exit(EXIT_FAILURE);
    int fz = st.st_size;
    char filesize[100];
    sprintf(filesize, "%d\r\n\r\n", fz);

    // local buffers for strong modularity
    char GETbuff[4096];
    memset(GETbuff, 0, 4096);
    //char response[fz + 2048];

    int get_file_descrp = open(FL, O_RDONLY);
    if (get_file_descrp == -1) {
        printf("issue \n");
        return;
    }

    //write response
    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: ";
    write(clientSocket, response, string_length(response));
    write(clientSocket, filesize, string_length(filesize));

    // Otherwise, parse through the file
    while (1) {
        int br = read(get_file_descrp, GETbuff, 4096);
        write(clientSocket, GETbuff, br);
        memset(GETbuff, 0, 4096);
        if (br <= 0) {
            break;
        }
    }

    close(get_file_descrp);
    return;
}

int main(int argc, char *argv[]) {

    // If the port was not passed in the first place, warn!
    if (argc <= 1) {
        warn("wrong arguments: ./httpserver port_num\nusage: ./httpserver <port>");
        return -1;
    }

    // Define variables for port number input and checking ---------------
    uint16_t port_number_input;
    char *ptr;
    // Conver the port number to int
    port_number_input = strtol(argv[1], &ptr, 10);
    char ch;
    int ok;
    //--------------------------------------------------------------------
    // If port number is not purely a number, then warn!
    if (sscanf(argv[1], "%d%c", &ok, &ch) != 1) {
        warn("invalid port number: %s\n", argv[1]);
        return -1;
    }
    // If port number is not within the range -> 1024 - 65535, then warn!
    if (port_number_input > 65535 || port_number_input < 1024) {

        warn("invalid port number: %s\n", argv[1]);
        return -1;
    }

    // Create a socket, with the number
    int soc = create_listen_socket(port_number_input);
    // Variables -------------------------------------------------------------------------------
    // buffer to read into
    char buffer[4096];
    // token for line parsing
    char *token;

    // This is what will start listening on port.
    int clientSocket;
    // For pointing to buffer
    char *rest;

    // We will use this to store, our request's METHOD, URI and version.
    char req_type[100];
    char file_name[100];
    char ver[100];
    // To store content length value
    int cl_value;

    // GET, PUT, HEAD, version string for comparison
    char *g = "GET";
    char *p = "PUT";
    char *h = "HEAD";
    //-----------------------------

    // main counter for lines
    int counter = 0;

    // Key, value pairs for headers
    char key[100] = { '\0' };
    char value[100] = { '\0' };

    // message body to purely store message body
    char message_body[4096];
    char *end_point;

    // pointer, ints, file descriptors and other vars.
    char *fn;
    // size_t bytes_read;
    int fd;
    // flag for Expect: 100 continue case
    int to_wait = 0;

    // Version for comparison
    char *version = "HTTP/1.1";
    //--------------------------------------------------------------------------------------------

    // Main while begings
    while (1) {
        // keep listening to requests
        clientSocket = accept(soc, NULL, NULL);
        // read request into buffer
        read(clientSocket, buffer, 4096);
        // point to buffer
        rest = buffer;
	
	printf("%s\n",buffer);
	
        // Find where request line + header is ending i.e after which message body starts.
        // make sure to store message body content!

        end_point = strstr(rest, "\r\n\r\n");
        // make a copy of message body content!
        sprintf(message_body, "%s", end_point);

        // Calculate the request line + headers length ---------------------------------------------------
        // Make sure its upto 2048, else return error
        int len_mes = string_length(message_body) - 4;
        int everything_else_len = string_length(rest);

        if (everything_else_len - len_mes > 2048) {

            write(clientSocket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request",
                60);
            memset(message_body, 0, 4096);
            memset(buffer, 0, 4096);
            close(clientSocket);
            break;
        }
        // ------------------------------------------------------------------------------------------------

        // Start parsing request, line by line
        while ((token = strtok_r(rest, "\r\n", &rest)) != NULL) {

            // If this is the first line,
            if (counter == 0) {
                // scan out the request type, filename and version in the request
                sscanf(token, "%s %s %s", req_type, file_name, ver);

                // Check if:-
                // The request type is less than 8, the request type is exactly GET, PUT or HEAD
                // The URI is less than 19 characters, the access permissions and HTTP version --------------------
                if (string_length(req_type) > 8) {
                    write(clientSocket,
                        "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);
                    close(clientSocket);
                    break;
                }

                if (strcmp(req_type, p) != 0 && strcmp(req_type, h) != 0
                    && strcmp(req_type, g) != 0) {
                    write(clientSocket,
                        "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);
                    close(clientSocket);
                    break;
                }

                if (string_length(file_name) > 19) {
                    write(clientSocket,
                        "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);
                    close(clientSocket);
                    break;
                }

                // get rid of the / in the filename
                fn = file_name;
                fn += 1;

                // Check if filename is in correct format!
                char FILENAME[100];
                sprintf(FILENAME, "%s", fn);

                char final_file[100] = { 0 };
                //FILENAME FORMAT

                sscanf(FILENAME, "%[a-zA-Z0-9_.]", final_file);
                if (string_length(final_file) != string_length(FILENAME)) {

                    write(clientSocket,
                        "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);
                    close(clientSocket);
                    break;
                }
                //-----------------------------------------

                // Check access, existence, correct file type ( if a directory fail and so on ), etc
                if ((string_length(FILENAME) > 0 && access(FILENAME, F_OK) == 0
                        && is_regular_file(FILENAME) == 0)
                    || (string_length(FILENAME) > 0 && is_regular_file(FILENAME) != 0
                        && access(FILENAME, F_OK) == 0 && access(FILENAME, W_OK) != 0)) {

                    write(clientSocket,
                        "HTTP/1.1 403 Forbidden\r\nContent-Length: 9\r\n\r\nForbidden", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);

                    close(clientSocket);
                    break;
                }

                if (string_length(FILENAME) > 0 && access(FILENAME, F_OK) != 0
                    && (strcmp(req_type, g) == 0 || strcmp(req_type, h) == 0)) {

                    write(clientSocket,
                        "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found", 55);
                    close(clientSocket);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    counter = 0;
                    break;
                }
                //----------------

                if (ver == version) {
                    write(clientSocket,
                        "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request", 60);
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    memset(req_type, 0, 100);
                    memset(file_name, 0, 100);
                    memset(ver, 0, 100);

                    close(clientSocket);
                    break;
                }

                // ------------------------------------------------------------------------------------------------------------------------

            }

            // For the lines after the request line
            else {

                // First check if the request type is GET,
                if (strcmp(req_type, g) == 0) {

                    // parse out the headers if they exist
                    sscanf(token, "%s %s", key, value);

                    // Check their key: value validity
                    if (key[string_length(key) - 1] != ':') {
                        write(clientSocket,
                            "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request",
                            60);
                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);

                        counter = 0;
                        close(clientSocket);
                        break;
                    }

                    // Once you reach message body i.e you are done dealing with headers, call GET handler and
                    // break out
                    if (end_point[0] == '\0') {
                        GET_handler(clientSocket, fn);
                        counter = 0;
                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);
                        close(clientSocket);
                        break;
                    }

                }

                // Else if request type is header,
                else if (strcmp(req_type, h) == 0) {

                    // parse out the headers if they exist
                    sscanf(token, "%s %s", key, value);

                    // Check their key: value validity
                    if (key[string_length(key) - 1] != ':') {

                        write(clientSocket,
                            "HTTP/1.1 409 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request",
                            60);
                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);

                        counter = 0;

                        close(clientSocket);
                        break;
                    }
                    // Once you reach message body i.e you are done dealing with headers, call HEAD handler and
                    // break out
                    if (end_point[0] == '\0') {
                        //break karo
                        HEAD_handler(clientSocket, fn);
                        counter = 0;

                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);
                        close(clientSocket);
                        break;
                    }

                }

                // Else if request type is PUT
                else if (strcmp(req_type, p) == 0) {

                    // parse out the headers if they exist
                    sscanf(token, "%s %s", key, value);

                    // If Expect: 100-continue header is found, set flag to 1.
                    if (strcmp("Expect:", key) == 0 && strcmp("100-continue", value) == 0) {
                        to_wait = 1;
                        memset(message_body, 0, 4096);
                        memset(value, 0, 100);
                        break;
                    }

                    // If all headers are parsed, break out
                    if (end_point[0] == '\0') {
                        break;
                    }

                    // Check their key: value validity
                    if (key[string_length(key) - 1] != ':') {
                        write(clientSocket,
                            "HTTP/1.1 400 Bad Request\r\nContent-Length: 11\r\n\r\nBad Request",
                            60);
                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);

                        counter = 0;
                        close(clientSocket);
                        break;
                    }

                    // Store content-length if found
                    if (strcmp("Content-Length:", key) == 0) {
                        sscanf(value, "%d", &cl_value);
                    }
                }
            }
            // increament line counter
            counter++;
        }

        // Once broken out of loop, this means, you're done dealing with headers and none of the conditions below will match,
        // since they're aleady dealt with or the headers never existed and now you simply need to handle the requests

        // If request type is HEAD, call it and handle it,
        // Else if request type is GET, call it and handle it, Else if request type is PUT, call it and handle it

        if (strcmp(req_type, g) == 0) {
            GET_handler(clientSocket, fn);
            memset(message_body, 0, 4096);
            memset(buffer, 0, 4096);
            memset(req_type, 0, 100);
            memset(file_name, 0, 100);
            memset(ver, 0, 100);
            counter = 0;
            close(clientSocket);

        } else if (strcmp(req_type, h) == 0) {
            HEAD_handler(clientSocket, fn);
            memset(message_body, 0, 4096);
            memset(buffer, 0, 4096);
            memset(req_type, 0, 100);
            memset(file_name, 0, 100);
            memset(ver, 0, 100);
            counter = 0;
            close(clientSocket);

        } else if (strcmp(req_type, p) == 0) {

            int written_bytes = 0;
            int exists = access(fn, F_OK);

            int acc = access(fn, W_OK);

            // First check if file exists then do we have permissions on it.
            if (exists == 0 && acc != 0) {

                write(clientSocket, "HTTP/1.1 403 Forbidden\r\nContent-Length: 9\r\n\r\nForbidden",
                    60);

                memset(message_body, 0, 4096);
                memset(buffer, 0, 4096);
                memset(req_type, 0, 100);
                memset(file_name, 0, 100);
                memset(ver, 0, 100);
                counter = 0;
                close(clientSocket);
                continue;
            }

            // next open it, or create it if it never existed!
            fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0644);

            // If there was error in opening file, send error
            if (fd == -1) {
                // File cannot be opened return to client socket
                // warn("%s",argv[file]);

                write(clientSocket, "HTTP/1.1 403 Forbidden\r\nContent-Length: 9\r\n\r\nForbidden",
                    60);
                memset(message_body, 0, 4096);
                memset(buffer, 0, 4096);
                memset(req_type, 0, 100);
                memset(file_name, 0, 100);
                memset(ver, 0, 100);
                counter = 0;
                close(clientSocket);
                continue;
            }

            //Else begin executing request
            while (1) {

                // if something was read in message body during first the 4096 read,
                // write that first and if it is the only content to be written then break out!
                if (string_length(message_body) > 0) {
                    written_bytes += write(fd, message_body + 4, string_length(message_body));
                    printf("LMUI 1\n");
                    // If all bytes are written, send relevant message and exit.
                    if (written_bytes >= cl_value) {
                        if (exists == -1) {

                            write(clientSocket,
                                "HTTP/1.1 201 CREATED\r\nContent-Length: 7\r\n\r\nCREATED", 51);
                        } else if (exists == 0) {

                            write(
                                clientSocket, "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK", 41);
                        }
                        printf("LMAO 1\n");
                        close(fd);
                        counter = 0;
                        memset(message_body, 0, 4096);
                        memset(buffer, 0, 4096);
                        written_bytes = 0;
                        close(clientSocket);
                        break;
                    }
                }

                // else, read from clientSocket into buffer
                int rb = read(clientSocket, buffer, 4096);

                // wait until something is read.
                if (rb < 0) {
                    rb = read(clientSocket, buffer, 4096);
                }

                // write the bytes to the file descriptor
                written_bytes += write(fd, buffer, rb);
                memset(buffer, 0, 4096);

                // If all bytes are written, send relevant message and exit.
                if (written_bytes >= cl_value) {
                    if (exists == -1) {

                        write(clientSocket,
                            "HTTP/1.1 201 CREATED\r\nContent-Length: 7\r\n\r\nCREATED", 51);
                    } else if (exists == 0) {
                        write(clientSocket, "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK", 41);
                    }
                    printf("LMAO 2\n");
                    close(fd);
                    counter = 0;
                    memset(message_body, 0, 4096);
                    memset(buffer, 0, 4096);
                    written_bytes = 0;
                    close(clientSocket);
                    break;
                }
            }
        }
    }
    // Close client socket
    close(clientSocket);
    return 0;
}
