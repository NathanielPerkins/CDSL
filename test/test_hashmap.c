
#include "HashMap.h"
#include "unity.h"

#include <string.h>

#define HASHMAP_SIZE 8

struct person_t {
    char first_name[16];
    char second_name[16];
};

struct hashmap_t *hashmap;

void setUp(void) {
    hashmap = hm_create(HASHMAP_SIZE);
}

void tearDown(void) {

}

void test_Create_SuccessfullyAllocatesHashmap(void){
    struct hashmap_t *test_hashmap;
    test_hashmap = hm_create(HASHMAP_SIZE);

    TEST_ASSERT_NOT_NULL(test_hashmap);
    TEST_ASSERT_NOT_NULL(test_hashmap->table);
    TEST_ASSERT_EQUAL_INT32(HASHMAP_SIZE, test_hashmap->size);
    TEST_ASSERT_EQUAL_INT32(0, test_hashmap->entries);
}

void test_Put_StringKeyAndIntData(void) {
    char one_key[8] = "one";
    int one = 10;
    hm_put(hashmap, one_key, &one, strlen(one_key), sizeof(one));

    int *one_get = hm_get(hashmap, one_key, strlen(one_key));

    TEST_ASSERT_EQUAL_MEMORY(&one, one_get, sizeof(one));
}

void test_Put_ADTKeyAndIntData(void) {
    struct person_t steven = {"Steven", "Rogers"};
    int data = 10;
    hm_put(hashmap, &steven, &data, sizeof(steven), sizeof(data));

    TEST_ASSERT_EQUAL_MEMORY(&data, hm_get(hashmap, &steven, sizeof(steven)), sizeof(data));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Create_SuccessfullyAllocatesHashmap);
    RUN_TEST(test_Put_StringKeyAndIntData);
    RUN_TEST(test_Put_ADTKeyAndIntData);
    return UNITY_END();
}