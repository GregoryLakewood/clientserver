CC=clang
CFLAGS=-g
COMMON_OBJS = common.o linkedlist.o

all: $(COMMON_OBJS) server client

common.o: common.h common.c
	$(CC) $(CFLAGS) -c common.c

linkedlist.o: linkedlist.h linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

tcpc: tcpclient.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpc tcpclient.c $(COMMON_OBJS)

tcps: tcpserver.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcps tcpserver.c $(COMMON_OBJS)

server: server.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o server server.c $(COMMON_OBJS)

client: client.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o client client.c $(COMMON_OBJS)

linkedlist: linkedlist_template.c
	$(CC) $(CFLAGS) -o linkedlist linkedlist_template.c

clean:
	rm -rf *.o *.dSYM tcpc tcps server client linkedlist