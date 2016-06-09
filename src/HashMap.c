/*
 * HashMap.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include "HashMap.h"

#include <string.h> // strcmp()

struct hashmap_t *hm_create(uint32_t size) {
    struct hashmap_t *hashmap = malloc(sizeof(struct hashmap_t));
    hashmap->entries = 0;
    hashmap->size = size;
    hashmap->table = calloc(size, sizeof(struct hashmap_node_t));

    return hashmap;
}

void hm_free(struct hashmap_t *hashmap) {
    struct hashmap_node_t *node;
    struct hashmap_node_t *temp;

    for (int i = 0; i < hashmap->size; i++) {
        node = &(hashmap->table[i]);

        if (node->key != NULL) {
            /* First data is stored in the array, don't free it. */
            node = node->next;

            /* Check for chained entries. */
            while (node != NULL) {
                free(node->key);
                free(node->data);
                temp = node;
                node = node->next;
                free(temp);
            }
        }
    }

    free(hashmap->table);
    free(hashmap);
}

void hm_put(struct hashmap_t *hashmap, char *key, void *data, size_t data_size) {
    if (((double) hashmap->entries / hashmap->size) > LOAD_FACTOR) { /* Resize the array. */
        hm_resize(hashmap);
    }

    uint32_t hash = hm_hash(key);
    uint32_t bucket = hash % hashmap->size;

    struct hashmap_node_t *node = &(hashmap->table[bucket]);
    struct hashmap_node_t *prev = node;
    if (node->key == NULL) { /* Empty bucket. */
        node->key = malloc(sizeof(char) * strlen(key));
        node->data = malloc(data_size);
        strcpy(node->key, key);
        memcpy(node->data, data, data_size);
        node->data_size = data_size;
        node->next = NULL;

        hashmap->entries++;
        return;
    }

    /* Iterate over nodes in bucket and check for existing key. */
    while (node != NULL) {
        if (strcmp(key, node->key) == 0) { /* Key already exists, overwrite data. */
            free(node->data);
            node->data = malloc(data_size);
            memcpy(node->data, data, data_size);
            node->data_size = data_size;
            return;
        } else { /* Check next node in chain. */
            prev = node;
            node = node->next;
        }
    }

    /* Add to chain of entries. */
    struct hashmap_node_t *new_node = malloc(sizeof(struct hashmap_node_t));
    new_node->key = malloc(sizeof(char) * strlen(key));
    new_node->data = malloc(data_size);
    strcpy(new_node->key, key);
    memcpy(new_node->data, data, data_size);
    new_node->data_size = data_size;
    new_node->next = NULL;

    prev->next = new_node;
    hashmap->entries++;
}

void *hm_get(struct hashmap_t *hashmap, char *key) {
    uint32_t bucket = hm_hash(key) % hashmap->size;

    struct hashmap_node_t *node = &(hashmap->table[bucket]);
    while (node != NULL && node->key != NULL) {
        if (strcmp(key, node->key) == 0) {
            return node->data;
        } else {
            node = node->next;
        }
    }

    return NULL; /* Key not found. */
}

/* Simple Bob Jenkins's hash algorithm taken from the wikipedia description. */
uint32_t hm_hash(char *key) {
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

void hm_resize(struct hashmap_t *hashmap) {
    uint32_t old_size = hashmap->size;
    struct hashmap_node_t *old_table = hashmap->table;

    hashmap->entries = 0;
    hashmap->size = old_size * 2;
    hashmap->table = calloc(hashmap->size, sizeof(struct hashmap_node_t));


    struct hashmap_node_t *node;
    struct hashmap_node_t *old_node;
    for (int i = 0; i < old_size; i++) {
        node = &(old_table[i]);

        if (node->key != NULL) {
            /* First data is stored in the array, don't free it. */
            hm_put(hashmap, node->key, node->data, node->data_size);
            node = node->next;

            /* Check for chained entries. */
            while (node != NULL) {
                hm_put(hashmap, node->key, node->data, node->data_size);
                old_node = node;
                node = node->next;
                free(old_node);
            }
        }
    }

    free(old_table);
}
