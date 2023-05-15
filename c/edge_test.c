#include "edge.h"

#include <stdbool.h>

#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_EdgeCreationWorks(void) {
    Edge e;

    Cell c1 = (Cell){
        .x = 10,
        .y = 11,
    };
    Cell c2 = (Cell){
        .x = -1,
        .y = 42,
    };

    e = new_edge(c1, c2);
    TEST_ASSERT_EQUAL_UINT32(cell_hash(c1), e.src_cell_hash);
    TEST_ASSERT_EQUAL_UINT32(cell_hash(c2), e.dst_cell_hash);

    e = new_edge(c2, c1);
    TEST_ASSERT_EQUAL_UINT32(cell_hash(c1), e.src_cell_hash);
    TEST_ASSERT_EQUAL_UINT32(cell_hash(c2), e.dst_cell_hash);

    e = new_edge(c1, c1);
    TEST_ASSERT_EQUAL_UINT32(INT32_MAX, e.src_cell_hash);
    TEST_ASSERT_EQUAL_UINT32(INT32_MIN, e.dst_cell_hash);
}

void test_EdgeHashWorks(void) {
    Edge e = {
        .src_cell_hash = 0x12345678,
        .dst_cell_hash = 0xABCDEF01,
    };
    TEST_ASSERT_EQUAL_HEX64(0x12345678ABCDEF01, edge_hash(e));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_EdgeCreationWorks);
    RUN_TEST(test_EdgeHashWorks);
    return UNITY_END();
}