CC=clang
CFLAGS=-g
COMMON_OBJS = common.o

all: $(COMMON_OBJS) tcpc tcps server client

common.o: common.h common.c
	$(CC) $(CFLAGS) -c common.c

tcpc: tcpclient.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpc tcpclient.c $(COMMON_OBJS)

tcps: tcpserver.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcps tcpserver.c $(COMMON_OBJS)

server: server.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o server server.c $(COMMON_OBJS)

client: client.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o client client.c $(COMMON_OBJS)

clean:
	rm -rf *.o *.dSYM tcpc tcps server client