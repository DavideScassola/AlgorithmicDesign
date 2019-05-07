CXX = gcc
OPT = -O4

all: strassen_test.x

strassen_test.x: main.c matrix.c strassen.c strassen_improved.c
	$(CXX) $(OPT) -o $@ $^

clean:
	@rm *.x

.PHONY: clean all
