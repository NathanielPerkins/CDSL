/*
 * HashMap.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include "HashTable.h"

#include <stdlib.h> // malloc()
#include <string.h> // strcmp()

void ht_create(struct ht_hashmap *hashmap, uint32_t size) {
    hashmap->table = calloc(size, sizeof(struct ht_entry));
    hashmap->size = size;
    hashmap->entries = 0;
}

void ht_put(struct ht_hashmap *hashmap, void *key, void *value) {
    // TODO: Check if resize is needed. Probably use 0.8 as load factor.

    uint32_t hash = ht_hash(key);
    uint32_t bucket = hash % hashmap->size;

    struct ht_entry *entry = &(hashmap->table[bucket]);
    struct ht_entry *prev = entry;

    if (entry->key == NULL) { // Empty bucket.
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
        hashmap->entries++;
        return;
    }

    /* Iterate over entries in bucket. */
    while (entry != NULL) {
        if (strcmp(key, entry->key) == 0) { // Key exists, update value.
            entry->value = value;
            return;
        } else {
            prev = entry;
            entry = entry->next;
        }
    }

    /* Add to chain of entries. */
    struct ht_entry *new_entry = malloc(sizeof(struct ht_entry));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = NULL;

    prev->next = new_entry;
    hashmap->entries++;
}

void* ht_get(struct ht_hashmap *hashmap, void *key) {
    uint32_t bucket = ht_hash(key) % hashmap->size;

    struct ht_entry *entry = &(hashmap->table[bucket]);

    while (entry != NULL && entry->key != NULL) {
        if (strcmp(key, entry->key) == 0) {
            return entry->value;
        } else {
            entry = entry->next;
        }
    }

    return NULL; /* Key not found. */
}

// Simple Bob Jenkins's hash algorithm taken from the wikipedia description.
static uint32_t ht_hash(char *key) {
    size_t len = strlen(key);
    uint32_t hash = 0;

    for (uint32_t i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

static void ht_resize(struct ht_hashmap *hashmap) {

}
