#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "list.h"



typedef struct hash_table_s {
    uint32_t ht_size;
    node_t **ht_buckets;
} hash_table_t;

static int32_t
hash_function (int32_t input, uint32_t size)
{
    return (input % size);
}

static hash_table_t *
hash_table_create (uint32_t size)
{
    hash_table_t *hash_table;

    hash_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    hash_table->ht_size = size;
    hash_table->ht_buckets = (node_t **)malloc(sizeof(node_t *) * size);
    for (int iter = 0; iter < size; iter++) {
        hash_table->ht_buckets[iter] = NULL;
    }

    return hash_table;
}

static bool
hash_table_insert (hash_table_t *hash_table, int32_t input)
{
    if (hash_table == NULL) {
        return false;
    }

    uint32_t bucket;

    bucket = hash_function(input, hash_table->ht_size);
    add_to_list(&hash_table->ht_buckets[bucket], input);

    return true;
}

static bool
hash_table_search (hash_table_t *hash_table, int32_t input)
{
   if (hash_table == NULL) {
        return false;
    }

    uint32_t bucket;

    bucket = hash_function(input, hash_table->ht_size);

    return search_in_list(hash_table->ht_buckets[bucket], input);
}

static bool
hash_table_delete (hash_table_t *hash_table, int32_t input)
{
    if (hash_table == NULL) {
        return false;
    }

    uint32_t bucket;

    bucket = hash_function(input, hash_table->ht_size);
    if (!hash_table->ht_buckets[bucket]) {
        return false;
    }

    return remove_from_list(&hash_table->ht_buckets[bucket], input);
}

static void
hash_table_destroy (hash_table_t *hash_table)
{
    free(hash_table->ht_buckets);
    free(hash_table);
}

int
main () {
    hash_table_t *hash_table;

    hash_table = hash_table_create(10);
    assert(hash_table_insert(hash_table, 1100) == true);
    assert(hash_table_insert(hash_table, 1103) == true);
    assert(hash_table_insert(hash_table, 4) == true);
    assert(hash_table_insert(hash_table, 33) == true);
    assert(hash_table_search(hash_table, 27) == false);
    assert(hash_table_search(hash_table, 4) == true);
    assert(hash_table_delete(hash_table, 1100) == true);
    assert(hash_table_delete(hash_table, 33) == true);
    assert(hash_table_delete(hash_table, 1103) == true);
    hash_table_destroy(hash_table);

    return 0;
}