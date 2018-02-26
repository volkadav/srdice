CC=gcc
CFLAGS=-O2 -Wall --std=c99

srdice: srdice.c
	$(CC) -o srdice $(CFLAGS) srdice.c

clean:
	rm srdice *.o
