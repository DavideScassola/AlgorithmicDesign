CXX = gcc
OPT = -O4

all: performance_test.x correctness_test.x

performance_test.x: performance_test.c binaryHeap.c array.c Dijkstra.c
	$(CXX) $(OPT) -o $@ $^

correctness_test.x: correctness_test.c binaryHeap.c array.c Dijkstra.c
	$(CXX) $(OPT) -o $@ $^

clean:
	@rm -r *.x

.PHONY: clean all
