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
#include <stdlib.h>

#define LOAD_FACTOR 0.8

struct hashmap_node_t {
    void *key;
    void *data;
    size_t key_size; /* Size of key in bytes. */
    size_t data_size; /* Size of data in bytes. */
    struct hashmap_node_t *next; /* Used for separate chaining. */
};

struct hashmap_t {
    struct hashmap_node_t *table;
    uint32_t size; /* Number of table array. Number of 'buckets'. */
    uint32_t nodes; /* Total number of nodes in hashmap, including chained. */
};

struct hashmap_t *hm_create(uint32_t size);

void hm_free(struct hashmap_t *hashmap);

void hm_put(struct hashmap_t *hashmap, void *key, void *data, size_t key_size, size_t data_size);

void *hm_get(struct hashmap_t *hashmap, void *key, size_t key_size);

int8_t hm_remove(struct hashmap_t *hashmap, void *key, size_t key_size);

void hm_resize(struct hashmap_t *hashmap);

uint32_t hm_hash(void *key, size_t key_len);

#endif /* HASHMAP_H_ */
