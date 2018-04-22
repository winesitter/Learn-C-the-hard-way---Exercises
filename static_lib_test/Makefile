

CFLAGS = -g -Wall -O2

# Folder for libraries
INCLUDE_LIB = -Llib

# Folder for source files
INCLUDE_SRC = -Isrc

# Libraries in lib folder to include
LIBRARIES = -ltestlib -lm

# Source files in src folder
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

# Test files in test folder
BIN_SRC = main/main.c
TEST_SRC = $(wildcard test/*_tests.c)
TEST_OBJ = $(patsubst %.c, %, $(TEST_SRC))

# Binary files in bin folder
BINARY = bin/test


# Make Routine 
all: make_lib make_binary

# Create binary file
make_binary: $(BIN_SRC)
	gcc $(INCLUDE_SRC) -static $^ $(INCLUDE_LIB) $(LIBRARIES) -o $(BINARY)

# Create library
make_lib: $(OBJECTS)
	ar rcs lib/libtestlib.a -o $^


# Create unit tests
tests: $(TEST_OBJ)
	gcc -static $^ $(INCLUDE_LIB) $(LIBRARIES) -o test/unit_test




.PHONY: clean
clean:
	rm -fr lib/*.a
	rm -fr src/*.o
	rm -fr $(BINARY)

