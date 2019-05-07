#ifndef __LL__

#define TYPE float

typedef struct Node
{
    TYPE value;
    struct Node* next;
} Node;

typedef struct List
{
    size_t length;
    Node* first;
} List;

List newList();

void push(List *l, TYPE v);

TYPE get(List l, size_t i);

void free_list(List* l);

List* allocate_lists_array(size_t n);

void free_lists_array(List* l, size_t n);

#endif // __LL__