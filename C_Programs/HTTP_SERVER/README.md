# CSE130 - Assignment 1 : httpserver

This program is a httpserver, which is an implementation of the topic of client/server systems and strong modularity, and it made to support GET, PUT and HEAD functionality.


## List of files:

The program directory should include:

```
README.md - Details about the program.

httpserver.c - Main program file (source code),

httpserver.h - Header file for httpserver.c .

Makefile - To make (compile, clean, format, etc.) the code.

test_files - This is a directory, that contains the files that maybe required by the scripts in test_scripts.

test_scripts - This is a directory that contains the test scripts.
```

## How to run the program:

Make sure  you're in the directory where 'httpserver.c', 'httpserver.h' and 'Makefile' exists and run the following command
```
make (you could also use - make all)
```

Next, run the following command and make sure to replace <port> a valid port number i.e it must only be an integer. Make sure that port number is between 1024 to 65535. This is because 1 - 1023 are reserved port numbers.
```
./httpserver <port>
```


## Test Scripts

There are some test scripts in the test_scripts directory, you should run this from within that directory itself, you do not need to move them anywhere else. Otherwise, they wont work. The files that these test scripts use are in the test_files directory and they are files that were provided to us in class.
If the tests pass, 'echo $?' command should return 0, else it should return 1.
## Program Design

The program is designed within a main outer infinite while loop where in, after socket creation (using the function given to us), the accept() function is used to continuously listen to a client's request, on that socket, unless the admin explicity shuts the server using CTRL + C. Strong Modularity is implemented in terms of segregating request methods into separate functions and minimizing interactions in code.

This socket creation is done using a port number that was given as input when running the server. The request body is stored into a buffer (the size choice is described in detail in the next section.). From this buffer, we segregate, the message body from the rest of the body. The message body begins after '\r\n\r\n', so we find where in the buffer that is and save a pointer to it. This will be used later in the program when we need to mark the end of request line and headers. We make a copy of this as well i.e of the message body.

Now, as for the parsing, Each line of the request is parsed using 'strtok_r()',
as it is safe for threads. For the first iteration i.e METHOD URI HTTP_Version, each of these is stored in variables for checking. Their validity is checked i.e If the METHOD is valid i.e less than 8 charactars and is exactly GET, PUT or HEAD. Similarly, the URI is checked to be less than 19 charactars and upper and lowercase alphabets, 0-9 or . and _ must accepted in the URI and nothing else. This program supports only HTTP/1.1 and that is checked against the version from the request as well. Other checks relating to request and header size is also done. i.e must be upto 2048 bytes, permissions, existence, type of file, access and so on is also done within the first iteration itself.


For the second iteration, we will have most of our stuff in place and would now want to actually start getting our method type to do its work. Firstly, each method type has its own function named GET_handler, PUT_handler and HEAD_handler. Now, depending on the request type, each of these methods is called. Details of each module and its implementation is in the sections below:

Also, there are functions to calculate a string's length and to check if a file is a regular file or not. If nor in, it should give back an error.

Side Note:- After every request ends or error, we close the clientSocket as a good practice. This shouldn't affect us since the clientSocket will start listening again as the loop has an accept() at the very top.


# GET_handler
The clientSocket i.e client file descriptor and filename is sent to this function. A local buffer variable is created (refer to buffer design section below for more details on buffer size) so as to align with strong modularity.

It simply opens up the file that the client requested to GET.  If there was no error, in opening it, we get details of the number of bytes in the file so that we can prepare a header -> Content-Length and send to the client as a part of our response. Else we must send error message on client. We first, send a 200 OK header to the client after which we start writing to the client in loop until all bytes from the file are sent, after which we return. memset() is used each time to reset buffer so as to avoid garbage to persist in the buffer and c() was used for the purpose of finding the file's size.


# HEAD_handler
Just like in GET, the clientSocket i.e client file descriptor and filename is sent to this function. A local buffer variable is created (refer to buffer design section below for more details on buffer size) so as to align with strong modularity.

We get details of the number of bytes in the file so that we can prepare a header -> Content-Length and send to the client as a part of our response. We first, send a 200 OK header to the client after which we write this to the client, after which we return. memset() is used each time to reset buffer so as to avoid garbage to persist in the buffer and stat() was used for the purpose of finding the file's size.


# PUT_handler
This function is somewhat segregated, the main PUT_handler function only handles writing the message it was passed to the fd that it was passed and returning. Under the main while loop, as we parse the request lines and do the basic checks that were done in the first loop, we check if the request is a PUT request, in which case. We checked a few things before calling the PUT_handler function:-

1. If the file, exists in the first place and if access is Forbidden in which case it should send a 403 Forbidden to the client.

2. Depending on whether or not the file exists, it is either opened or created and then opened. 

3. We parse the headers and check if they are in the form -> 'key: value'.

4. If we notice details related to Expect: 100 Continue or Content-Length, we take note of this.

To handle PUT requests:-

1. If the request was sent with a -T flag i.e if the data is coming from another file or the file is essentially being uploaded. We need to wait until the data comes to us and then read. i.e the data will be sent to us separate from the request line and the header body. In this case, if as we were parsing and found Expect: 100-Continue, we handle this case as mentioned above by reading again and making sure we wait until we have read bytes! 

Note that if the some bytes for the message body were found in the first iteration of 4096 bytes of the buffer then we store this in a variable, and if this variable is not empty, it is written first and only then the buffer is read. The loop breaks once all bytes are written, in which case we break and write the response code to the client i.e 200 OK if the file already existed or 201 CREATED if the file was created.


## How Buffer Size was chosen:
As per this [source](https://stackoverflow.com/questions/236861/how-do-you-determine-the-ideal-buffer-size-when-using-fileinputstream), I noted that the file system's buffer size is what is the ideal block size but I wanted to further investigate this.
Firstly, for the linux file system, the default block size is 4096 Bytes. 

So what do you mean by block size?

When we do the I/O operations, say read, we read in blocks i.e in linux we would read about 4096 bytes by default. 
Now we definitely could use read more than 4096 bytes if we wanted but there is a problem. When we try to read more than what is advised by default, even though the overall clock time (real time) for the program will reduce, we will be compromising our CPU usage i.e there will be a load on our CPU !

On the other hand, if we try to read less than what is advised, even though the the CPU usage reduces , our program will execute very slowly i.e the real time will increase significantly!

## Conclusion on Buffer Size decision

Hence, the optimum choice is when we go by the default block size of the linux filesystem as we do not put excessive load on the CPU and do not have a large execution time as well i.e it is the optimum choice in this case.
