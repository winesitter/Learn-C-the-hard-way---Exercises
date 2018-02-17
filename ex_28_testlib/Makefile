#***************************************************************************
#
#		 MM   MM	     A				K   K		EEEEE		FFFFF		I		L				EEEEE
#		 M M M M	    A A				K	 K		E				F				I		L				E
#		 M  M  M	   A   A	 		KKK			EEEE		FFFF		I		L				EEEE
#		 M     M	  AAAAAAA 	 	K  K		E				F				I		L				E
#		 M		 M 	 A	 		 A 		K   K 	EEEEE 	F		  	I 	LLLLL		EEEEE
#
#***************************************************************************

#***************************************************************************
# Usual CFLAGS, along with some others that are needed for building 
# libraries. The OPTFLAGS variable lets you augment the build options as 
# needed.
#***************************************************************************
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

#***************************************************************************
# This option is used when linking a library. You can augment the linking 
# options using the OPTLIBS variable
#***************************************************************************
LIBS=-ldl $(OPTLIBS)

#***************************************************************************
# Set an optional (denoted by ?=) variable PREFIX that will only have this
# value if you didn't already give a PREFIX setting.
#***************************************************************************
PREFIX?=/usr/local

#***************************************************************************
# Dynamically allocate the SOURCES variable by doing a wildcard search for
# all *.c files in the src directory and all folders below it
#***************************************************************************
SOURCES=$(wildcard src/**/*.c src/*.c)
#***************************************************************************
# Use patsubst to take the SOURCES list of *.c files and make a new list of
# all the object files by changing all %.c extensions to %.o and assign 
# these new objects to OBJECTS
#***************************************************************************
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

#***************************************************************************
# Allocate all test source files for the unit test and get all the TEST
# targets. Strip away the .c extension so that a full program will be made
# with the same name.
#***************************************************************************
TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

#***************************************************************************
# The ultimate target is build/libYOUR-LIBRARY.a, whose name will be changed
# by you to whatever library you're trying to build
#***************************************************************************
TARGET=build/libtest.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))



#***************************************************************************
# This is the target that make runs by default (first target).
# First its builds the library. Then it runs the tests target
#***************************************************************************
# The target build
all: $(TARGET) $(SO_TARGET) tests

#***************************************************************************
# Target for making developer builds that introduces a technique for 
# changing options for just one target. 
#***************************************************************************
dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

#***************************************************************************
# This builds the TARGET library, whatever that is. First make the build 
# directory and then compile all of the objects. 
# ar actually makes the target. The syntax $@ $(OBJECTS) is a way of saying
# "put the target for the Makefile source here and all the OBJECTS after 
# that". The $@ maps back to the $(TARGET), which maps to 
# build/libYOUR_LIBRARY.a
# Use ranlib to actually build the library.
#***************************************************************************
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

#***************************************************************************
# Create the /build and /bin libraries 
#***************************************************************************
build:
	@mkdir -p build
	@mkdir -p bin


#***************************************************************************
#	Do Unit Tests
#***************************************************************************
# If you have a target that is not real, but there is a file or a directory
# with that name, tag the target with .PHONY: - so make will ignore the 
# file and always run
#***************************************************************************
.PHONY: tests

#***************************************************************************
# Add TARGET to the build, so each of the test programm will be linked 
# with the TARGET library.
#***************************************************************************
tests: CFLAGS += $(TARGET)

#***************************************************************************
# Build each program in $(TESTS) separately and run the shell script 
# runtests.sh
#***************************************************************************
tests: $(TESTS)
	sh ./tests/runtests.sh



#***************************************************************************
# The Cleaner
#***************************************************************************
# Clean out most of the junk that various compilers and tools leave behind
#***************************************************************************
clean:
	rm -fr build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#***************************************************************************
# The Install
#***************************************************************************
# Install the library
#***************************************************************************
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/


#***************************************************************************
# The Checker
#***************************************************************************
# Look for any bad patterns in functions.
#***************************************************************************
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
							|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true



