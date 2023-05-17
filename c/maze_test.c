#include "maze.h"

#include <memory.h>
#include <stdbool.h>

#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_MazeInitWorks(void) {
    Maze mz;
    memset(&mz, 0xA5, sizeof(mz));
    maze_init(&mz, "test", 42, 33);
    TEST_ASSERT_EQUAL_STRING("test", mz.name);
    TEST_ASSERT_EQUAL_INT16(42, mz.width);
    TEST_ASSERT_EQUAL_INT16(33, mz.height);
    Cell c1 = {
        .x = 21,
        .y = 16,
    };
    TEST_ASSERT_EQUAL_MEMORY(&c1, &mz.entrance, sizeof(Cell));
    Cell c2 = {
        .x = 41,
        .y = 0,
    };
    TEST_ASSERT_EQUAL_MEMORY(&c2, &mz.exit, sizeof(Cell));
    TEST_ASSERT_EQUAL_HEX32(0x00000000, mz.cell_set[0]);  // Because cell(0,0) is valid.
    TEST_ASSERT_EQUAL_HEX64(0xDFDFDFDFDFDFDFDF, mz.edge_set[0]);  // Because no edge is valid yet.
}

void test_MazeNameBufferOverrun(void) {
    Maze mz;
    char name[100];
    memset(name, 'x', sizeof(name));
    name[99] = '\0';
    maze_init(&mz, name, 42, 33);
    TEST_ASSERT_EQUAL(79, strlen(mz.name));
}

void test_MazeTooBig(void) {
    Maze mz;
    maze_init(&mz, "test", 1000, 1000);
    TEST_ASSERT_EQUAL_INT16(10, mz.width);
    TEST_ASSERT_EQUAL_INT16(10, mz.height);
}

void test_MazeCells(void) {
    Maze mz;
    maze_init(&mz, "test", 42, 33);
    TEST_ASSERT_TRUE(maze_has_cell(&mz, (Cell){.x = 0, .y=0}));
    TEST_ASSERT_FALSE(maze_has_cell(&mz, (Cell){.x = -1, .y=-1}));
    TEST_ASSERT_FALSE(maze_has_cell(&mz, (Cell){.x = 42, .y=33}));
    maze_add_cell(&mz, (Cell){.x = 42, .y=33});
    TEST_ASSERT_FALSE(maze_has_cell(&mz, (Cell){.x = 42, .y=33}));
}

void test_MazeEdges(void) {
    Maze mz;
    maze_init(&mz, "test", 42, 33);
    Cell cell1 = {.x = 2, .y=3};
    Cell cell2 = {.x = 2, .y=4};
    TEST_ASSERT_FALSE(maze_has_edge(&mz, cell1, cell2));
    TEST_ASSERT_FALSE(maze_has_edge(&mz, cell2, cell1));
    TEST_ASSERT_FALSE(maze_cell_has_connections(&mz, cell1));
    TEST_ASSERT_FALSE(maze_cell_has_connections(&mz, cell2));
    maze_add_edge(&mz, cell1, cell2);
    TEST_ASSERT_TRUE(maze_has_edge(&mz, cell1, cell2));
    TEST_ASSERT_TRUE(maze_has_edge(&mz, cell2, cell1));
    TEST_ASSERT_TRUE(maze_cell_has_connections(&mz, cell1));
    TEST_ASSERT_TRUE(maze_cell_has_connections(&mz, cell2));
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_MazeInitWorks);
    RUN_TEST(test_MazeNameBufferOverrun);
    RUN_TEST(test_MazeTooBig);
    RUN_TEST(test_MazeCells);
    RUN_TEST(test_MazeEdges);
    return UNITY_END();
}
