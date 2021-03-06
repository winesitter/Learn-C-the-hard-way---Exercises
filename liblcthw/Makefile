CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl &(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_OBJ=$(patsubst $.c, %.o, $(TEST_SRC))
TEST_TARGET=tests/unit_tests
#TESTS=$(patsubst %.c, %, $(TEST_SRC))

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a, %.so, $(TARGET))


# The target build
#---------------------------------------------------------------
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests - see [1] for reference
#---------------------------------------------------------------
.PHONY: tests
tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET) $(TARGET)
	./tests/runtests.sh

# The cleaner
#---------------------------------------------------------------
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The install
#---------------------------------------------------------------
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The checker
#---------------------------------------------------------------
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true


# References: 
#---------------------------------------------------------------
# [1]: https://stackoverflow.com/questions/4349553/multiple-source-files-in-c-how-exactly-do-makefiles-work
