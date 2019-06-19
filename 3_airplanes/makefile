CC=gcc
CFLAGS=-Wall -g

all: domes3

domes3: AirportManagement.o Evretirio.o TSDDA.o TSEvr.o ch8_BSTpointer.o ch8_AVLpointer.o
	$(CC) $(CFLAGS) -o domes3 AirportManagement.o Evretirio.o TSDDA.o TSEvr.o ch8_BSTpointer.o ch8_AVLpointer.o

AirportManagement.o: AirportManagement.c
	$(CC) $(CFLAGS) -c AirportManagement.c 

Evretirio.o: Evretirio.c
	$(CC) $(CFLAGS) -c Evretirio.c 

TSDDA.o: TSDDA.c
	$(CC) $(CFLAGS) -c TSDDA.c 

TSEvr.o: TSEvr.c
	$(CC) $(CFLAGS) -c TSEvr.c

ch8_BSTpointer.o: ./BST/ch8_BSTpointer.c
	$(CC) $(CFLAGS) -c ./BST/ch8_BSTpointer.c

ch8_AVLpointer.o: ./AVL/ch8_AVLpointer.c
	$(CC) $(CFLAGS) -c ./AVL/ch8_AVLpointer.c

.PHONY: clean

clean:
	rm -f *o domes3
