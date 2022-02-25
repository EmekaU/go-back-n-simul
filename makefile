# Author - Emeka V Umeozo [cvu302, 11249945]

CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu99 -Wall -pedantic

## gets platform and architecture for getting pthreads
#PLATFORM=$(shell uname -s)
#ARCH=$(shell uname -m)

.PHONY: ALL clean

ALL: sender receiver

common.o: imports.h ports.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c common.c -o common.o

# sender
sender: sender.o common.o
	$(CC) common.o sender.o -o sender

sender.o: sender.c ports.h imports.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sender.c -o sender.o

# receiver
receiver: receiver.o common.o
	$(CC) common.o receiver.o -o receiver 

receiver.o: receiver.c ports.h imports.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c receiver.c -o receiver.o

clean:
	rm *.o sender receiver
