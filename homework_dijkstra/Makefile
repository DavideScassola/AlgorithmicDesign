CXX = gcc
OPT = -O4

all: test.x

test.x: dijkstra_test.c binaryHeap.c array.c Dijkstra.c
	$(CXX) $(OPT) -o $@ $^

clean:
	@rm -r *.x

.PHONY: clean all
