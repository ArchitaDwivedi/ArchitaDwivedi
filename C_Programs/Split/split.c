#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char *argv[]) {

    // Initializing variables-------
    char buffer[4096];
    char *standard_input = "-";
    char *del_pointer = argv[argc - 1];
    char delimiter = del_pointer[0];
    //------------------------------

    //-----------------------------------------------------------------
    // Case 1:- What if the no filename and no delimiter was passed?--
    // Also, handles the case of special chars - &, \ and ; !
    if (argc <= 2) {
        warn("not enough arguments\nusage: ./split <files> <delimiter>");
        return -1;
    }
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    //Case 2:- What if the last argument is also a filename itself and not single char?

    else if (strlen(argv[argc - 1]) > 1) {
        warn("only single-character delimiters allowed\nusage: ./split <files> <delimiter>");
        return -1;
    }
    //-----------------------------------------------------------------

    //-----------------------------------------------------------------
    // Case3- This is where all files and delimiter is given
    // However, we need to split this in two halves
    //      1) If '-' is given in file -> keep looping until ctrl-d is found!
    //      2) In other cases

    else {

        for (int file = 1; file < (argc - 1); file++) {

            // Read file name,

            // if file name is '-', take stdin and split until EOF is found!
            if ((strcmp(argv[file], standard_input)) == 0) {

                // Loop until EOF is encountered
                while (1) {
                    // read bytes from stdin i.e 0!
                    size_t bytes_read = read(0, buffer, 4096);

                    // if EOF is encountered
                    if (bytes_read <= 0) {
                        // we clear the buffer content before breaking out!
                        memset(buffer, 0, bytes_read);
                        break;
                    }

                    // if bytes were read, we loop through the buffer,
                    for (size_t rc = 0; rc < bytes_read; rc++) {

                        // printf("buffer is: %s",buffer);
                        // if delimiter is encountered while parsing the buffer
                        if (delimiter == buffer[rc]) {
                            // replace it with a new line! Else do nothing
                            memcpy(&(buffer[rc]), "\n", 1);
                        }
                    }

                    // One we have parsed through the content in the buffer and replaced it as
                    // per need, then we can write it to stdout i.e 1!
                    write(1, buffer, bytes_read);

                    // Since the buffer content is written, we clear it!
                    memset(buffer, 0, bytes_read);
                }

            }

            // Else, if the name is a normal filename!
            else {

                // get the file descripter
                int fd = open(argv[file], O_RDONLY);

                // if file cannot be opened, warn!
                if (fd == -1) {
                    // File cannot be opened
                    warn("%s", argv[file]);

                    if (argv[file] == argv[argc - 2]) {
                        break;
                    }

                    else {
                        continue;
                    }
                }

                // else, parse through the file contents
                while (1) {

                    // read content from the file into the buffer!
                    size_t bytes_read = read(fd, buffer, 4096);

                    // now loop through the buffer's content
                    for (size_t rc = 0; rc < bytes_read; rc++) {

                        // if delimiter is found while parsing buffer
                        if (delimiter == buffer[rc]) {

                            // replace it with '\n', else do nothing!
                            memcpy(&(buffer[rc]), "\n", 1);
                        }
                    }

                    // One we have parsed through the content in the buffer and replaced it as
                    // per need, then we can write it to stdout i.e 1!
                    write(1, buffer, bytes_read);

                    // Since the buffer content is written, we clear it!
                    memset(buffer, 0, bytes_read);

                    // Once, we read less than 4096 bytes, that means we are almost done reading
                    // the file, so we break after it is written!
                    if (bytes_read < 4096) {
                        // Since the buffer content is written, we clear it!
                        memset(buffer, 0, bytes_read);
                        close(fd);
                        break;
                    }
                }
            }
        }
    }
    //-----------------------------------------------------------------

    return 0;
}
