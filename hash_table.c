#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>



typedef struct hash_table_s {
    uint32_t ht_size;
    int32_t *ht_buckets; //TBD Mamta to make it a linked list.
    bool *ht_bucket_in_use;
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

    hash_table = (hash_table_t *) malloc (sizeof(hash_table_t));
    hash_table->ht_size = size;
    hash_table->ht_buckets = (int32_t *) malloc (sizeof(int32_t) * size);
    hash_table->ht_bucket_in_use = (bool *) malloc (sizeof(bool) * size);
    memset(hash_table->ht_bucket_in_use, false, sizeof(bool)*size);

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
    if (hash_table->ht_bucket_in_use[bucket]) {
        return false;
    }
    hash_table->ht_buckets[bucket] = input;
    hash_table->ht_bucket_in_use[bucket] = true;

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

    return (hash_table->ht_bucket_in_use[bucket]);
}

static bool
hash_table_delete (hash_table_t *hash_table, int32_t input)
{
    if (hash_table == NULL) {
        return false;
    }

    uint32_t bucket;

    bucket = hash_function(input, hash_table->ht_size);
    if (!hash_table->ht_bucket_in_use[bucket]) {
        return false;
    }
    hash_table->ht_bucket_in_use[bucket] = false;

    return true;
}

static void
hash_table_destroy (hash_table_t *hash_table)
{
    free(hash_table->ht_bucket_in_use);
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
    assert(hash_table_insert(hash_table, 1103) == false);
    assert(hash_table_search(hash_table, 27) == false);
    assert(hash_table_search(hash_table, 4) == true);
    assert(hash_table_delete(hash_table, 1100) == true);
    assert(hash_table_delete(hash_table, 1103) == true);
    assert(hash_table_delete(hash_table, 1103) == false);
    hash_table_destroy(hash_table);

    return 0;
}