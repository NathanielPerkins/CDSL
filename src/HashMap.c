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
    hashmap->nodes = 0;
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
            /* First node is stored in the array, don't free it. */
            free(node->key);
            free(node->data);
            node = node->next;

            /* Check for chained nodes. */
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

void hm_put(struct hashmap_t *hashmap, void *key, void *data, size_t key_size, size_t data_size) {
    if (((double) hashmap->nodes / hashmap->size) > LOAD_FACTOR) { /* Resize the array. */
        hm_resize(hashmap);
    }

    uint32_t hash = hm_hash(key, key_size);
    uint32_t bucket = hash % hashmap->size;

    struct hashmap_node_t *node = &(hashmap->table[bucket]);
    struct hashmap_node_t *prev = node;

    /* If bucket is used iterate over nodes in bucket and check for existing key. */
    while (node != NULL && node->key != NULL) {
        if (memcmp(key, node->key, key_size) == 0) { /* Key already exists, overwrite data. */
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

    if (prev != node) { /* Bucket is used. Allocate a new node and point previous node to it. */
        node = malloc(sizeof(struct hashmap_node_t));
        prev->next = node;
    }
    node->key = malloc(key_size);
    node->data = malloc(data_size);
    memcpy(node->key, key, key_size);
    memcpy(node->data, data, data_size);
    node->key_size = key_size;
    node->data_size = data_size;
    node->next = NULL;

    hashmap->nodes++;
}

void *hm_get(struct hashmap_t *hashmap, void *key, size_t key_size) {
    uint32_t bucket = hm_hash(key, key_size) % hashmap->size;

    struct hashmap_node_t *node = &(hashmap->table[bucket]);
    while (node != NULL && node->key != NULL) {
        if (memcmp(key, node->key, key_size) == 0) {
            return node->data;
        } else {
            node = node->next;
        }
    }

    return NULL; /* Key not found. */
}

int8_t hm_remove(struct hashmap_t *hashmap, void *key, size_t key_size) {
    uint32_t hash = hm_hash(key, key_size);
    uint32_t bucket = hash % hashmap->size;

    struct hashmap_node_t *node = &(hashmap->table[bucket]);
    struct hashmap_node_t *prev = node;

    /* Case 1: Only entry in bucket. */
    while (node != NULL && node->key != NULL) {
        if (memcmp(key, node->key, key_size) == 0) {
            free(node->key);
            free(node->data);
            if (node->next == NULL) { /* First node with no chained node(s). */
                node->key = NULL;
                node->data = NULL;
                node->key_size = 0;
                node->data_size = 0;
            } else if (prev == node) { /* First node with chained node(s). */
                node = node->next;
                prev->key = node->key;
                prev->data = node->data;
                prev->key_size = node->key_size;
                prev->data_size = node->data_size;
                prev->next = node->next;
                free(node);
            } else { /* Node in chain. */
                prev->next = node->next;
                free(node);
            }

            hashmap->nodes--;
            return 1; /* Successfully removed node. */
        } else {
            prev = node;
            node = node->next;
        }
    }

    return 0; /* Node does not exist. Nothing removed. */
}

void hm_resize(struct hashmap_t *hashmap) {
    uint32_t old_size = hashmap->size;
    struct hashmap_node_t *old_table = hashmap->table;

    hashmap->nodes = 0;
    hashmap->size = old_size * 2;
    hashmap->table = calloc(hashmap->size, sizeof(struct hashmap_node_t));


    struct hashmap_node_t *node;
    struct hashmap_node_t *old_node;
    for (int i = 0; i < old_size; i++) {
        node = &(old_table[i]);

        if (node->key != NULL) {
            /* First node is stored in the array, don't free it. */
            hm_put(hashmap, node->key, node->data, node->key_size, node->data_size);
            free(node->key);
            free(node->data);
            node = node->next;

            /* Check for chained nodes. */
            while (node != NULL) {
                hm_put(hashmap, node->key, node->data, node->key_size, node->data_size);
                free(node->key);
                free(node->data);
                old_node = node;
                node = node->next;
                free(old_node);
            }
        }
    }

    free(old_table);
}

/* Simple Bob Jenkins's hash algorithm taken from the wikipedia description. */
uint32_t hm_hash(void *key, size_t key_len) {
    uint32_t hash = 0;

    for (uint32_t i = 0; i < key_len; ++i) {
        hash += ((uint8_t *) key)[i]; /* Cast to uint8_t pointer to dereference and get 1 byte. */
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}
