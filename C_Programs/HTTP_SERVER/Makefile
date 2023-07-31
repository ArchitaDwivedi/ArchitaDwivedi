CC = clang
CFLAGS = -Wall -Werror -Wextra -pedantic
all:	httpserver

httpserver:	httpserver.o
		$(CC) -o httpserver httpserver.o
httpserver.o:	httpserver.c
		$(CC) $(CFLAGS) -c httpserver.c
clean:
	rm -f httpserver httpserver.o
format:
	clang-format -i -style=file *.c
