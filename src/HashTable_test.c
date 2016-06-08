/*
 * HashTable_test.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

#define TABLE_SIZE 5

int main(void) {
    struct ht_table hash_table;

    ht_create(&hash_table, TABLE_SIZE);

    char key[8];
    for (int i = 0; i < 10; i++) {
        sprintf(key, "key_%d", i);
        printf("Putting value %d with key %s.\n", i, key);
        ht_put(&hash_table, key, i);
    }

    ht_put(&hash_table, "key_5", 69);

    int32_t value;
    for (int i = 9; i >= 1; i--) {
        sprintf(key, "key_%d", i);
        ht_get(&hash_table, key, &value);
        printf("Getting Key: %s, Value: %d\n", key, value);
    }

    return EXIT_SUCCESS;
}
