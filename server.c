#include "common.h"

#define BUFSIZE 4096
#define SERVER_BACKLOG 1

struct client {
  int client_socket;
  SA *client_addr;
  char client_address[MAXLINE];
  char client_name[MAXLINE];
};

void handle_connection(int client_socket);

int main(int argc, char **argv) {
  int server_socket, client_socket, addr_size;
  addr_size = sizeof(SA_IN);
  SA_IN server_addr, client_addr;

  struct client *client_arr[MAXBUFFER];
  bzero(client_arr, sizeof(struct client));
  int n = 0;

  check(server_socket = socket(AF_INET, SOCK_STREAM, 0),
        "Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVER_PORT);

  check(bind(server_socket, (SA *)&server_addr, sizeof(server_addr)),
        "Bind Failed!");
  check(listen(server_socket, SERVER_BACKLOG), "Listen Failed!");

  fd_set current_sockets, ready_sockets;
  FD_ZERO(&current_sockets);
  FD_SET(server_socket, &current_sockets);

  printf("Server started.\n");

  while (1) {
    ready_sockets = current_sockets;

    if (select(MAXBUFFER + 1, &ready_sockets, NULL, NULL, NULL) < 0) {
      perror("Select Failed!");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (MAXBUFFER + 1); i++) {
      if (FD_ISSET(i, &ready_sockets)) {
        if (i == server_socket) {
          // this is new connection
          check(client_socket = accept(server_socket, (SA *)&client_addr,
                                       (socklen_t *)&addr_size),
                "Accept Failed!");
          client_arr[n] = malloc(sizeof(struct client));
          client_arr[n]->client_addr = (SA *)&client_addr;
          client_arr[n]->client_socket = client_socket;
          inet_ntop(AF_INET, &client_addr, client_arr[n]->client_address,
                    MAXLINE);
          printf("Connected with ip: %s!\n", client_arr[n]->client_address);
          n++;
        } else {
          // this is signal from client
          handle_connection(i);
        }
      }
    }
    handle_connection(client_arr);
  }

  return 0;
}

void handle_connection(int client_socket) {

  printf("IP number %s joined", client_socket
  return;
}
