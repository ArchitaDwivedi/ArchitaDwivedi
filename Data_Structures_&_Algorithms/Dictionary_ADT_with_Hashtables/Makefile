Enrollment:	Enrollment.o HashTable.o Dictionary.o List.o
	cc -o prog3 Enrollment.o HashTable.o Dictionary.o List.o

Enrollment.o:	Enrollment.h Enrollment.c
	cc -c Enrollment.c

HashTable.o:	HashTable.h HashTable.c
	cc -c HashTable.c

Dictionary.o:	Dictionary.h Dictionary.c HashTable.o
	cc -c Dictionary.c

List.o: List.h List.c
	cc -c List.c

clean:
	rm -f prog3 Enrollment Enrollment.o HashTable.o Dictionary.o List.o

