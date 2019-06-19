CC=gcc
CFLAGS= 

all: domes2

domes2: main.o Session.o
	$(CC) $(CFLAGS) -o domes2 main.o Session.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

Session.o: Session.c
	$(CC) $(CFLAGS) -c Session.c 

.PHONY: clean

clean:
	rm -f *o domes2
