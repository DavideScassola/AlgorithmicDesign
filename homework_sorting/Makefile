CXX = gcc
OPT = -O4
SOURCE = binaryHeap.c sorting.c floatLinkedList.c matrix.c 

all: insertion_sort.x quick_heap_sort.x linear_sort.x

insertion_sort.x: insertion_main.c $(SOURCE)
	$(CXX) $(OPT) -o $@ $^

quick_heap_sort.x: quick_heap_main.c $(SOURCE)
	$(CXX) $(OPT) -o $@ $^

linear_sort.x: linear_main.c $(SOURCE)
	$(CXX) $(OPT) -o $@ $(OPENPM) $^

clean:
	@rm -r *.x

.PHONY: clean all
