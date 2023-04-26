#ifndef _COMMON_H_
#define _COMMON_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 18000
#define MAXLINE 128
#define MAXBUFFER 5
#define SOCKETERROR (-1)

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

void err_n_die(const char *fmt, ...);
char *bin2hex(const unsigned char *input, size_t len);
int check(int exp, const char *msg);

#endif /* _COMMON_H_ */