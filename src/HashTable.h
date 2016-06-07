/*
 * HashTable.h
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdint.h>

// typedef int32_t ht_value_t;

struct ht_entry {
    char *key;
    int32_t value;
    struct ht_entry *next; // Used for separate chaining.
};

struct ht_table {
    struct ht_entry **table;
    uint32_t size;
    uint32_t entries;
};

void ht_create(struct ht_table *hash_table, uint32_t size);

void ht_put(struct ht_table *hash_table, char *key, int32_t value);
void ht_get(struct ht_table *hash_table, char *key, int32_t *value);

static uint32_t ht_hash(char *key);
static void ht_resize(struct ht_table *hash_table);

#endif /* HASHTABLE_H_ */
