CC = clang
CFLAGS = -Wall -Werror -Wextra -pedantic -pthread
all:	queue.o
queue.o:	queue.c queue.h
		$(CC) $(CFLAGS) -c queue.c
clean:
	rm -f queue.o
format:
	clang-format -i -style=file *.c