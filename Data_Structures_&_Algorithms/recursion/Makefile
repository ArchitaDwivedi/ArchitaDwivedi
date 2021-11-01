# Makefile for Program assignment 0
#
# make                   makes prog0 executable
# make prog0             makes prog0 executable as well
# make clean             removes all binaries
#------------------------------------------------------------------------------

prog0 : prog0.o
	gcc -std=c11 -Wall -o prog0 prog0.o

prog0.o : prog0.c
	gcc -std=c11 -Wall -c prog0.c
clean :
	rm -f prog0 prog0.o