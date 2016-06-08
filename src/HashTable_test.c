/*
 * HashTable_test.c
 *
 * Created on: 07/06/2016
 * Author: Shaun Karran
 */

#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

#define TABLE_SIZE 10

int main(void) {
    struct ht_hashmap hashmap;

    ht_create(&hashmap, TABLE_SIZE);

    char test_value1[] = "test_value1";
    char test_value2[] = "test_value2";
    char test_value3[] = "test_value3";
    char test_value4[] = "test_value4";
    char test_value69[]  = "test_value69";

    ht_put(&hashmap, "test_key1", &test_value1);
    ht_put(&hashmap, "test_key2", &test_value2);
    ht_put(&hashmap, "test_key3", &test_value3);
    ht_put(&hashmap, "test_key4", &test_value4);

    ht_put(&hashmap, "test_key3", &test_value69);

    char key[16];
    void *value;
    for (int i = 4; i >= 1; i--) {
        sprintf(key, "test_key%d", i);
        value = ht_get(&hashmap, key);
        printf("Getting Key: %s, Value: %s\n", key, value);
    }

    value = ht_get(&hashmap, "doesnt_exist");
    value == NULL ? printf("Key not found\n") : printf("Getting Key: %s, Value: %s\n", key, value);

    printf("Number of entries: %d\n", hashmap.entries);

    return EXIT_SUCCESS;
}
