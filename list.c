#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct node_s {
    struct node_s *next;
    int value;
};

bool
add_to_list (node_t **head, int32_t value)
{
    node_t *node;

    node = (node_t *) malloc(sizeof(node_t));
    node->value = value;

    if (*head == NULL) {
       node->next = NULL;
    } else {
        node->next = *head;
    }
    *head = node;

    return true;
}

bool
remove_from_list (node_t **head, int32_t value)
{
    if (*head == NULL) {
        return false;
    }
    node_t *node, *prev;

    prev = NULL;
    node = *head;

    while ( node) {
        if (node->value == value) {
            break;
        }
        prev = node;
        node = node->next;
    }

    if (!node) {
        return false;
    }
    if (prev) {
        prev->next = node->next;
    } else {
        /*
         * Head is being deleted.
         */
        *head = node->next;
    }
    free(node);

    return true;
}

bool
search_in_list (node_t *head, int32_t value)
{
    if (head == NULL) {
        return false;
    }

    for (node_t *node = head; node; node = node->next) {
        if (node->value == value) {
            return true;
        }        
    }
    return false;
}