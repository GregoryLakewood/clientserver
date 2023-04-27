#include "linkedlist.h"

void printlist(node_t *head) {
  node_t *temporary = head;

  while (temporary != NULL) {
    printf("%s(%d) - ", temporary->client_address, temporary->value);
    temporary = temporary->next;
  }
  printf("\n");
}

node_t *create_new_node(int client_socket, SA *client_addr) {
  node_t *result = malloc(sizeof(node_t));

  result->client_socket = client_socket;
  inet_ntop(AF_INET, &client_addr, result->client_address, MAXLINE);
  result->client_addr = client_addr;
  result->client_name = "default";

  result->next = NULL;
  result->prev = NULL;
  return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
  node_to_insert->next = *head;
  if (*head != NULL) {
    (*head)->prev = node_to_insert;
  }
  *head = node_to_insert;
  node_to_insert->prev = NULL;
  return node_to_insert;
}

void remove_node(node_t **head, node_t *node_to_remove) {
  if (*head == node_to_remove) {
    *head = node_to_remove->next;
    if (*head != NULL) {
      (*head)->prev = NULL;
    }
  } else {
    node_to_remove->prev->next = node_to_remove->next;
    if (node_to_remove->next != NULL) {
      node_to_remove->next->prev = node_to_remove->prev;
    }
  }
  node_to_remove->next = NULL;
  node_to_remove->prev = NULL;

  free(node_to_remove);

  return;
}

node_t *find_node(node_t *head, int client_socket) {
  node_t *tmp = head;
  while (tmp != NULL) {
    if (tmp->client_socket == client_socket)
      return tmp;
    tmp = tmp->next;
  }
  return NULL;
}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode) {
  newnode->next = node_to_insert_after->next;
  if (newnode->next != NULL) {
    newnode->next->prev = node_to_insert_after;
  }
  newnode->prev = node_to_insert_after;
  node_to_insert_after->next = newnode;
}