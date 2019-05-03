CFLAGS=-Wall -g

SOURCES=bintree.c
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
TARGET=glob_test.c
BINARY=glob_test


all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(TARGET) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $<

