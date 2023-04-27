#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "common.h"

#ifndef __null
// #define NULL ((void *)0)
#endif /* NULL */

struct node {
  int client_socket;
  char client_address[MAXLINE];
  char *client_name;

  int id;

  struct node *next;
  struct node *prev;
};
typedef struct node node_t;

void printlist(node_t *head);
node_t *create_new_node(int client_socket, char *client_address, int id);
node_t *insert_at_head(node_t **head, node_t *node_to_insert);
void remove_node(node_t **head, node_t *node_to_remove);
node_t *find_node(node_t *head, int client_socket);
void insert_after_node(node_t *node_to_insert_after, node_t *newnode);

#endif /* _LINKEDLIST_H_ */
