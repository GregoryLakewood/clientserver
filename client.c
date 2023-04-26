#include "common.h"

#define MAXMSG 127

void handle_connection(int server_socket);

int main(int argc, char **argv) {
  int server_socket, client_socket;
  SA_IN server_addr, client_addr;

  check(server_socket = socket(AF_INET, SOCK_STREAM, 0),
        "Failed to create socket!");
  bzero(&server_addr, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(SERVER_PORT);

  check(connect(server_socket, (SA *)&server_addr, sizeof(server_addr)),
        "Failed to connect!");
  printf("Connected to server!\n");

  handle_connection(server_socket);

  close(server_socket);
}

void handle_connection(int server_socket) {
  char buffer[MAXMSG];
}
