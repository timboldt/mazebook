CFLAGS = -Wall -Ithird_party/tigr -Ithird_party/unity/src -DUNITY_OUTPUT_COLOR

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -framework OpenGL -framework Cocoa
else ifeq ($(UNAME_S),Linux)
	LDFLAGS = -s -lGLU -lGL -lX11
endif

.PHONY: all clean tests maze
all: maze tests

clean:
	rm -rf build

tests: build/celltest build/edgetest

maze: build/maze

build/maze: main.c cell.c edge.c maze.c third_party/tigr/tigr.c
	mkdir -p build
	gcc $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)

build/celltest: cell_test.c cell.c third_party/unity/src/unity.c
	mkdir -p build
	gcc $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)
	./$@

build/edgetest: edge_test.c edge.c cell.c third_party/unity/src/unity.c
	mkdir -p build
	gcc $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)
	./$@
