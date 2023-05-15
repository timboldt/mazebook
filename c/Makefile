CFLAGS = -Ithird_party/tigr -Ithird_party/unity/src

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -framework OpenGL -framework Cocoa
else ifeq ($(UNAME_S),Linux)
	LDFLAGS = -s -lGLU -lGL -lX11
endif

all: builddir maze celltest

clean:
	rm -rf build

builddir:
	mkdir build

maze: main.c cell.c edge.c third_party/tigr/tigr.c
	gcc $^ -Os -o build/$@ $(CFLAGS) $(LDFLAGS)

celltest: cell_test.c cell.c third_party/unity/src/unity.c
	gcc $^ -Os -o build/$@ $(CFLAGS) $(LDFLAGS)
	./build/celltest

