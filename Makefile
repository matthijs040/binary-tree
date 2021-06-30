CC=g++
CC_FLAGS+=-Wall -Werror -Wpedantic
CC_FLAGS+=-ggdb
CC_FLAGS+=-std=c++17

SOURCEDIR=./src/
SOURCES=$(SOURCEDIR)*.cpp
INCDIR=./inc/
INCLUDES=$(INCDIR)

BINARY=a.out

all:
	$(CC) $(CC_FLAGS) $(LDFLAGS) -c $(SOURCES) -I $(INCLUDES) -o $(BINARY)

clean:
	rm -rf $(BINARY)