CC=clang
CFLAGS=-g

all: tcpc tcps


tcpc: tcpclient.c
	$(CC) $(CFLAGS) -o tcpc tcpclient.c

tcps: tcpserver.c
	$(CC) $(CFLAGS) -o tcps tcpserver.c


clean:
	rm -rf *.dSYM tcpc tcps