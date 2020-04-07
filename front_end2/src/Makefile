# Source: https://gist.github.com/zachwhaley/9458612 and modified accordingly

CC = g++
CFLAGS = -g -Wall -std=c++14
LDLIBS =

PRGM  = auction-system
SRCS := $(filter-out test.cpp, $(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(PRGM)

$(PRGM): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(DEPS)