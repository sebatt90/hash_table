CC := gcc

BUILD_DIR = build
SO_TARGET = libhashtable.so
SL_TARGET = libhashtable.a
LDFLAGS :=
CFLAGS := -fpic -g # enable debugging

# Tests
TEST_DIR := tests
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst %.c,%.o,$(TEST_SRCS))
TEST_LDFLAGS := -L$(BUILD_DIR) -lhashtable -Wl,-rpath=$(shell pwd)/$(BUILD_DIR)
TEST_CFLAGS := -I. -g 

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) -o $(BUILD_DIR)/$(patsubst $(TEST_DIR)/%.o,%,$@) $<  

tests: sharedobj $(TEST_OBJS)
	echo "built tests"

mk_build:
	mkdir -p $(BUILD_DIR) 

hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c $<

sharedobj: hash_table.o mk_build
	$(CC) $(LDFLAGS) -shared -o $(BUILD_DIR)/$(SO_TARGET) $<  

clean:
	rm -rf build
	rm *.o
	rm tests/*.o
