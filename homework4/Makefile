CXX = gcc
OPT = -O4

all: test.x

test.x: matrix.c binaryHeap.c main.c
	$(CXX) $(OPT) -o $@ $^

clean:
	@rm -r *.x

.PHONY: clean all
