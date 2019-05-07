CXX = gcc
OPT = -O4

all: chain.x

chain.x: main.c matrix.c chain_matrix_multiplication.c
	$(CXX) $(OPT) -o $@ $^

clean:
	@rm *.x

.PHONY: clean all
