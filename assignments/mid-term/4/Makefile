CXX=clang++
CFLAGS=--std=c++11 -Wall -O0 -g
SRCS=$(wildcard *.cc)
OBJS=$(SRCS:.cpp=.o)

.DEFAULT: all

all: build run

build: $(SRC)
	$(CXX) $(CFLAGS) $(SRCS)

run: a.out
	./a.out

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -rf *.dSYM
