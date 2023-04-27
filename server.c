#include "common.h"
#include "linkedlist.h"

#define BUFSIZE 4096
#define SERVER_BACKLOG 1

void receive_msg(int client_socket);
int server_start(void);
int accept_new_connection(int server_socket, char *client_address);

int main(int argc, char **argv) {
  node_t *room = NULL;
  node_t *tmp;

  int server_socket;

  server_socket = server_start();

  fd_set current_sockets, ready_sockets;
  FD_ZERO(&current_sockets);
  FD_SET(server_socket, &current_sockets);

  printf("Server started.\n");

  int id = 1;
  while (1) {
    ready_sockets = current_sockets;

    if (select(MAXBUFFER + 1, &ready_sockets, NULL, NULL, NULL) < 0) {
      perror("Select Failed!");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (MAXBUFFER + 1); i++) {
      if (i == server_socket) {
        // new connection
        char client_address[MAXLINE + 1];
        int client_socket = accept_new_connection(server_socket, client_address);

        tmp = insert_at_head(&room,
                       create_new_node(client_socket, client_address, id));
        printf("Connected with ip: %s ID:(%d) !\n", tmp->client_address, tmp->id);
        id++;
      }
    }

    // printlist(room);
  }

  return 0;
}

void receive_msg(int client_socket) {
  char buffer[MAXLINE];
  bzero(buffer, MAXLINE);
  read(client_socket, buffer, sizeof(buffer));
  printf("user ip %s: %s", "todo", buffer);
  bzero(buffer, MAXLINE);
  return;
}

int server_start(void) {
  int server_socket;
  SA_IN server_addr;

  check(server_socket = socket(AF_INET, SOCK_STREAM, 0),
        "Failed to create socket");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVER_PORT);

  check(bind(server_socket, (SA *)&server_addr, sizeof(server_addr)),
        "Bind Failed!");
  check(listen(server_socket, SERVER_BACKLOG), "Listen Failed!");

  return server_socket;
}

int accept_new_connection(int server_socket, char *client_address) {
  int addr_size = sizeof(SA_IN);
  int client_socket;
  SA_IN client_addr;

  check(client_socket =
            accept(server_socket, (SA *)&client_addr, (socklen_t *)&addr_size),
        "accept failed");
  inet_ntop(AF_INET, &client_addr, client_address, MAXLINE);

  return client_socket;
}

/*
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
          FD_SET(client_socket, &current_sockets);
        } else {
          // this is signal from client
          receive_msg(i);
          FD_CLR(i, &current_sockets);
        }
      }
    }
*/