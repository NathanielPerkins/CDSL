
#include "HashMap.h"
#include "unity.h"

#include <string.h>

#define HASHMAP_SIZE 4

struct person_t {
    char first_name[16];
    char second_name[16];
};

struct address_t {
    int street_number;
    char street_name[16];
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
    TEST_ASSERT_EQUAL_INT32(0, test_hashmap->nodes);
}

void test_PutAndGet_StringKeyAndIntData(void) {
    char one_key[8] = "one";
    char two_key[8] = "two";
    char no_key[8] = "no";
    int one = 1;
    int two = 2;

    hm_put(hashmap, one_key, &one, strlen(one_key), sizeof(one));
    hm_put(hashmap, two_key, &two, strlen(two_key), sizeof(two));

    TEST_ASSERT_EQUAL_MEMORY(&one, hm_get(hashmap, one_key, strlen(one_key)), sizeof(one));
    TEST_ASSERT_EQUAL_MEMORY(&two, hm_get(hashmap, two_key, strlen(two_key)), sizeof(two));
    TEST_ASSERT_NULL(hm_get(hashmap, no_key, strlen(no_key)));
}

void test_PutAndGet_ADTKeyAndIntData(void) {
    struct person_t steven = {"Steven", "Rogers"};
    struct person_t peter = {"Peter", "Parker"};
    struct person_t bruce = {"Bruce", "Banner"};
    struct address_t address_1 = {1, "Street Rd"};
    struct address_t address_2 = {2, "Street Rd"};

    hm_put(hashmap, &steven, &address_1, sizeof(steven), sizeof(address_1));
    hm_put(hashmap, &peter, &address_2, sizeof(peter), sizeof(address_2));

    TEST_ASSERT_EQUAL_MEMORY(&address_1, hm_get(hashmap, &steven, sizeof(steven)), sizeof(address_1));
    TEST_ASSERT_EQUAL_MEMORY(&address_2, hm_get(hashmap, &peter, sizeof(peter)), sizeof(address_2));
    TEST_ASSERT_NULL(hm_get(hashmap, &bruce, sizeof(bruce)));
}

void test_Remove_OnlyNode(void) {
    struct person_t steven = {"Steven", "Rogers"};
    struct address_t address_1 = {1, "Street Rd"};

    hm_put(hashmap, &steven, &address_1, sizeof(steven), sizeof(address_1));
    hm_remove(hashmap, &steven, sizeof(steven));

    TEST_ASSERT_NULL(hm_get(hashmap, &steven, sizeof(steven)));
}

void test_Remove_OneOfManyNodes(void) {
    struct person_t steven = {"Steven", "Rogers"};
    struct person_t peter = {"Peter", "Parker"};
    struct address_t address_1 = {1, "Street Rd"};
    struct address_t address_2 = {2, "Street Rd"};

    hm_put(hashmap, &steven, &address_1, sizeof(steven), sizeof(address_1));
    hm_put(hashmap, &peter, &address_2, sizeof(peter), sizeof(address_2));
    hm_remove(hashmap, &peter, sizeof(peter));

    TEST_ASSERT_NULL(hm_get(hashmap, &peter, sizeof(peter)));
    TEST_ASSERT_EQUAL_MEMORY(&address_1, hm_get(hashmap, &steven, sizeof(steven)), sizeof(address_1));
}

void test_Remove_NotInHashmap(void) {
    struct person_t steven = {"Steven", "Rogers"};
    struct person_t peter = {"Peter", "Parker"};
    struct address_t address_1 = {1, "Street Rd"};

    hm_put(hashmap, &steven, &address_1, sizeof(steven), sizeof(address_1));

    TEST_ASSERT_EQUAL_INT8(0, hm_remove(hashmap, &peter, sizeof(peter)));
    TEST_ASSERT_EQUAL_MEMORY(&address_1, hm_get(hashmap, &steven, sizeof(steven)), sizeof(address_1));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Create_SuccessfullyAllocatesHashmap);
    RUN_TEST(test_PutAndGet_StringKeyAndIntData);
    RUN_TEST(test_PutAndGet_ADTKeyAndIntData);
    RUN_TEST(test_Remove_OnlyNode);
    RUN_TEST(test_Remove_OneOfManyNodes);
    RUN_TEST(test_Remove_NotInHashmap);
    return UNITY_END();
}