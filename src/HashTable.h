/*
 * HashMap.h
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stdbool.h>
#include <stdint.h>

struct ht_entry {
    void *key;
    void *value;
    struct ht_entry *next; // Used for separate chaining.
};

struct ht_hashmap {
    struct ht_entry *table;
    uint32_t size;
    uint32_t entries;
};

void ht_create(struct ht_hashmap *hashmap, uint32_t size);

void ht_put(struct ht_hashmap *hashmap, void *key, void *value);

void* ht_get(struct ht_hashmap *hashmap, void *key);

static uint32_t ht_hash(char *key);

static void ht_resize(struct ht_hashmap *hashmap);

#endif /* HASHMAP_H_ */
