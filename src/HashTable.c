/*
 * HashTable.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include "HashTable.h"

#include <stdlib.h> // malloc()
#include <string.h> // strcmp()

#include <stdio.h> // For debugging.

void ht_create(struct ht_table *hash_table, uint32_t size) {
    hash_table->table = calloc(size, sizeof(struct ht_entry*));
    hash_table->size = size;
    hash_table->entries = 0;
}

void ht_put(struct ht_table *hash_table, char *key, int32_t value) {
    // TODO: Check if resize is needed. Probably use 0.8 as load factor.

    uint32_t bucket = ht_hash(key) % hash_table->size;
    struct ht_entry *entry = hash_table->table[bucket];

    if (entry == NULL) { // Bucket is empty, create new entry.
        struct ht_entry *new_entry = malloc(sizeof(struct ht_entry));
        new_entry->key = malloc(sizeof(char) * strlen(key)); // Allocate memory for key.
        strcpy(new_entry->key, key);
        new_entry->value = value;
        new_entry->next = NULL;
        hash_table->table[bucket] = new_entry;
        hash_table->entries++;
    } else {
        struct ht_entry *previous_entry;
        while (entry != NULL) {
            if (strcmp(key, entry->key) == 0) { // Key already exists, overwrite value.
                entry->value = value;
                return;
            } else {
                previous_entry = entry;
                entry = entry->next;
            }
        }

        // Key doesnt exist, add to chain of entries in the bucket.
        struct ht_entry *new_entry = malloc(sizeof(struct ht_entry));
        new_entry->key = malloc(sizeof(char) * strlen(key)); // Allocate memory for key.
        strcpy(new_entry->key, key);
        new_entry->value = value;
        new_entry->next = NULL;
        previous_entry->next = new_entry;
        hash_table->entries++;
    }
}

void ht_get(struct ht_table *hash_table, char *key, int32_t *value) {
    uint32_t bucket = ht_hash(key) % hash_table->size;

    struct ht_entry *entry = hash_table->table[bucket];

    while (entry != NULL) {
        if (strcmp(key, entry->key) == 0) {
            *value = entry->value;
            return;
        } else {
            entry = entry->next;
        }
    }

    *value = NULL; /* Key not found. */
}

// Simple Bob Jenkins's hash algorithm taken from the wikipedia description.
static uint32_t ht_hash(char *key)
{
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

static void ht_resize(struct ht_table *hash_table) {

}
