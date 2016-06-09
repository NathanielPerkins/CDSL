/*
 * HashMap_test.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include <stdio.h>
#include <stdlib.h>

#include "HashMap.h"

#define HASHMAP_SIZE 128

int main(void) {
    struct hashmap_t *hashmap;

    hashmap = hm_create(HASHMAP_SIZE);

    char test_key[16];
    for (int i = 0; i < 16; i++) {
        sprintf(test_key, "test_key%d", i);
        hm_put(hashmap, test_key, &i, sizeof(i));
    }

    char key[16];
    int *value;
    for (int i = 0; i < hashmap->size; i++) {
        sprintf(key, "test_key%d", i);
        value = hm_get(hashmap, key);
        (value == NULL) ? printf("Key not found\n") : printf("Getting Key: %s, Value: %d\n", key, *value);
    }

    printf("Hashmap size: %d\n", hashmap->size);
    printf("Hashmap entries: %d\n", hashmap->entries);

    hm_free(hashmap);

    return EXIT_SUCCESS;
}
