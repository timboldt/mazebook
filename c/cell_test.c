#include "cell.h"

#include <stdbool.h>

#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

bool cells_equal(Cell c1, Cell c2) {
    return c1.x == c2.x && c1.y == c2.y;
}

void test_CellHashWorks(void) {
    Cell c;

    c = (Cell){
        .x = 0,
        .y = 0,
    };
    TEST_ASSERT_EQUAL_HEX32(0x00000000, cell_hash(c));

    c = (Cell){
        .x = 1,
        .y = -1,
    };
    TEST_ASSERT_EQUAL_HEX32(0x0001FFFF, cell_hash(c));

    c = (Cell){
        .x = -1,
        .y = 1,
    };
    TEST_ASSERT_EQUAL_HEX32(0xFFFF0001, cell_hash(c));
}

void test_DirectionsWork(void) {
    Cell c;
    Cell c2;

    c = (Cell){
        .x = 0,
        .y = 0,
    };

    c2 = (Cell){
        .x = 0,
        .y = 1,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, north_of(c)));
    c2 = (Cell){
        .x = 0,
        .y = -1,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, south_of(c)));
    c2 = (Cell){
        .x = 1,
        .y = 0,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, east_of(c)));
    c2 = (Cell){
        .x = -1,
        .y = 0,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, west_of(c)));

    c = (Cell){
        .x = 42,
        .y = 6,
    };
    
    c2 = (Cell){
        .x = 42,
        .y = 7,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, north_of(c)));
    c2 = (Cell){
        .x = 42,
        .y = 5,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, south_of(c)));
    c2 = (Cell){
        .x = 43,
        .y = 6,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, east_of(c)));
    c2 = (Cell){
        .x = 41,
        .y = 6,
    };
    TEST_ASSERT_TRUE(cells_equal(c2, west_of(c)));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CellHashWorks);
    RUN_TEST(test_DirectionsWork);
    return UNITY_END();
}