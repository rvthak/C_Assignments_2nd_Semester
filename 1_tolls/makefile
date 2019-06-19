#Ioannis Rovithakis sdi1800164 | 20/03/2019
CC=gcc
CFLAGS= 

all: domes1

domes1: ch6_QArray.o ch6_Simulation.o controller.o TStoixeiouOuras.o
	$(CC) $(CFLAGS) -o domes1 ch6_QArray.o ch6_Simulation.o controller.o TStoixeiouOuras.o

ch6_QArray.o: ch6_QArray.c
	$(CC) $(CFLAGS) -c ch6_QArray.c 

ch6_Simulation.o: ch6_Simulation.c
	$(CC) $(CFLAGS) -c ch6_Simulation.c 

controller.o: controller.c
	$(CC) $(CFLAGS) -c controller.c 

TStoixeiouOuras.o: TStoixeiouOuras.c
	$(CC) $(CFLAGS) -c TStoixeiouOuras.c 

.PHONY: clean

clean:
	rm -f *o domes1
