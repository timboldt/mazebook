CFLAGS = -Ithird_party/tigr

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -framework OpenGL -framework Cocoa
else ifeq ($(UNAME_S),Linux)
	LDFLAGS = -s -lGLU -lGL -lX11
endif

maze : main.c third_party/tigr/tigr.c
	gcc $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)

clean :
	rm -f maze