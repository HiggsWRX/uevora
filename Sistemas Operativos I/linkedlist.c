#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

node_t *new_list()
{
    node_t *head = malloc(sizeof(node_t));
    head->val = NULL;
    head->next = NULL;

    return head;
}

void add_start(node_t **head, void *val)
{
    if ((*head)->val != NULL) {
        node_t *new_node = malloc(sizeof(node_t));
        new_node->val = val;
        new_node->next = *head;
        *head = new_node;
    } else {
        (*head)->val = val;
    }
}

void add_end(node_t **head, void *val)
{
    if ((*head)->val != NULL) {
        node_t *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(node_t));
        current->next->val = val;
        current->next->next = NULL;
    } else {
        (*head)->val = val;
    }
}

void *remove_first(node_t **head)
{
    node_t *next_node = NULL;
    void *retval;

    if (*head == NULL) {
        return NULL;
    }

    if ((*head)->next != NULL) {
        next_node = (*head)->next;
        retval = (*head)->val;
        free(*head);
        *head = next_node;
    } else {
        retval = (*head)->val;
        (*head)->val = NULL;
    }

    return retval;
}

void *remove_last(node_t **head)
{
    node_t *current = *head;
    node_t *previous;
    void *retval;

    if ((*head)->next == NULL) {
        retval = (*head)->val;
        free(*head);
        *head = NULL;
        return retval;
    }

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    retval = current->val;
    free(current);
    previous->next = NULL;

    return retval;
}

void *getelement(node_t *head, int n)
{
    int i;
    void *retval;
    node_t *current = head;
    for (i = 0; i < n; i++) {
        if (current->next != NULL) {
            current = current->next;
        }
    }

    retval = current->val;

    return retval;
}

void clear_list(node_t **head)
{
    node_t *current = *head;
    while (current->next != NULL) {
        current = current->next;
        free(*head);
        *head = current;
    }
    current->val = NULL;
}