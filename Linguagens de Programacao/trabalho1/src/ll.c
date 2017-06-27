#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ll.h"

listnode *new_list()
{
    listnode *head = malloc(sizeof(listnode));
    head->val = NULL;
    head->next = NULL;

    return head;
}

void add(listnode **head, char *val)
{
    if (val == NULL)
        return;
    listnode *c = *head;
    if ((*head)->val != NULL) {
        while (c != NULL) {
            if (strcmp(c->val, val) == 0) {
                break;
            }
            c = c->next;
        }
        if (c == NULL) {
            listnode *new_node = malloc(sizeof(listnode));
            new_node->val = val;
            new_node->next = *head;
            *head = new_node;
        }
    } else {
        (*head)->val = val;
    }
}

void join(listnode **l1, listnode *l2, listnode *l3)
{
    while (l2 != NULL) {
        add(l1, l2->val);
        l2 = l2->next;
    }
    while (l3 != NULL) {
        add(l1, l3->val);
        l3 = l3->next;
    }
}

void del(listnode **head, char *val)
{
    listnode *c, *p;
    p = NULL;

    for (c = *head; c->next != NULL; c = c->next) {
        if (strcmp(val, c->val) == 0) {
            break;
        }
        p = c;
    }

    if (c != NULL) {
        if (c == *head) {
            if (c->next) {
                *head = c->next;
                free(c);
            } else {
                c->val = NULL;
            }
        } else {
            p->next = c->next;
            free(c);
        }
    }
}

void *getelement(listnode *head, int n)
{
    int i;
    void *retval;
    listnode *current = head;
    for (i = 0; i < n; i++) {
        if (current->next != NULL) {
            current = current->next;
        }
    }

    retval = current->val;

    return retval;
}

int contains(listnode *head, char *v)
{
    int found = 0;
    while (head->val != NULL) {
        if (strcmp(head->val, v) == 0) {
            found = 1;
            break;
        }
        if (head->next) {
            head = head->next;
        } else {
            break;
        }
    }

    return found;
}

void print(listnode *head)
{
    listnode *c = head;
    while (c) {
        if (c->val) {
            printf("%s ", c->val);
        }
        c = c->next;
    }
}