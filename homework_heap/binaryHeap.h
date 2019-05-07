#ifndef __BH__

#include<stdio.h>
#include<stdlib.h>
#include "limits.h"

typedef struct BinaryHeap
{
    int* H;
    size_t size;
    int (*compare)(int,int);
} BinaryHeap;

BinaryHeap newBinaryHeap(size_t size);

void freeBinaryHeap(BinaryHeap bh);

int left_child(int i);

int right_child(int i);

int parent(int i);

int root();

int is_root(int i);

int last(BinaryHeap h);

int is_valid_node(BinaryHeap h, int i);

int heap_minimum(BinaryHeap h);

void heapify(BinaryHeap h, int i);

void remove_minimum(BinaryHeap *h);

BinaryHeap build_binary_heap(int* A, size_t n, int (*compare_function)(int,int));

void heap_decrease_key(BinaryHeap h, int i, int value);

void heap_insert(BinaryHeap* h, int value);

void show_heap(BinaryHeap h);

#endif // __BH__
