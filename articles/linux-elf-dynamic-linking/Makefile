CC := gcc
CFLAGS := -Wall -Wextra -O2
ROOT := .
SRC := src

.PHONY: all clean

all: hello_world hello_world_static hello_world_write libhacker.so

hello_world: $(SRC)/hello_world.c
	$(CC) $(CFLAGS) $< -o $(ROOT)/$@

hello_world_static: $(SRC)/hello_world.c
	$(CC) $(CFLAGS) -static $< -o $(ROOT)/$@

hello_world_write: $(SRC)/hello_world_write.c
	$(CC) $(CFLAGS) $< -o $(ROOT)/$@

libhacker.so: $(SRC)/libhacker.c
	$(CC) -fPIC -shared $< -o $(ROOT)/$@ -ldl -lpthread

clean:
	rm -f $(ROOT)/hello_world $(ROOT)/hello_world_static $(ROOT)/hello_world_write $(ROOT)/libhacker.so
