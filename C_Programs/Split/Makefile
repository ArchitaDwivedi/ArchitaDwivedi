CC = clang
CFLAGS = -Wall -Werror -Wextra -pedantic
all:	split

split:	split.o
		$(CC) -o split split.o
split.o:	split.c
			$(CC) $(CFLAGS) -c split.c
clean:
		rm -f split split.o
format:
	clang-format -i -style=file *.c
