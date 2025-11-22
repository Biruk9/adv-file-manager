CC=gcc
CFLAGS=-Wall -Wextra

all: filemanager

filemanager: main.o file_ops.o
	$(CC) $(CFLAGS) main.o file_ops.o -o filemanager

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

file_ops.o: file_ops.c
	$(CC) $(CFLAGS) -c file_ops.c

clean:
	rm -f *.o filemanager
