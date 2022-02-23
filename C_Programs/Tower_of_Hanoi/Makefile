CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
all: tower
tower: tower.o stack.o
	$(CC) -o tower tower.o
tower.o: tower.c stack.c stack.h
	$(CC) $(CFLAGS) -c tower.c stack.c stack.h
clean:
	rm -rf tower tower.o stack.o infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
