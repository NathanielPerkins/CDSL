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

struct hm_entry {
    void *key;
    void *value;
    struct hm_entry *next; // Used for separate chaining.
};

struct hm_hashmap {
    struct hm_entry *table;
    uint32_t size;
    uint32_t entries;
};

void hm_create(struct hm_hashmap *hashmap, uint32_t size);

void hm_put(struct hm_hashmap *hashmap, void *key, void *value);

void* hm_get(struct hm_hashmap *hashmap, void *key);

static uint32_t hm_hash(char *key);

static void hm_resize(struct hm_hashmap *hashmap);

#endif /* HASHMAP_H_ */
