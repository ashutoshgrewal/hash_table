#ifndef _LIST_H_
#define _LIST_H_

typedef struct node_s node_t;

bool add_to_list(node_t **, int32_t);
bool remove_from_list(node_t **, int32_t);
bool search_in_list(node_t *, int32_t);

#endif