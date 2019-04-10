#include<stdlib.h>
#include<stdio.h>
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

Node* newNode(TYPE v)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = v;
    n->next = NULL;
    return n;
}

List newList()
{
    List l;
    l.length=0;
    l.first=NULL;
    return l;
}

Node* getNode(List l, size_t j)
{
    Node* n = l.first;
    for(int i=0;i<j;i++)
        n = n->next;

    return n;
}

void push(List *l, TYPE v)
{
    if(l->length==0)
        l->first=newNode(v);

    else
    {
        Node* last_node =  getNode(*l, l->length-1);
        last_node->next = newNode(v);
    }

    l->length++;
}

TYPE get(List l, size_t i)
{
    return getNode(l, i)->value;
}

void free_node(Node* node)
{
    if(node->next != NULL)
        free_node(node->next);

    free(node);
}

void free_list(List l)
{
    if(l.first!=NULL)
        free_node(l.first);
}

List* allocate_lists_array(size_t n)
{
    List* l = (List*)malloc(sizeof(List)*n);
    for(int i=0;i<n;i++)
        l[i]=newList();
    return l;
}

void free_lists_array(List* l, size_t n)
{
    for(int i=0;i<n;i++)
        free_list(l[i]);
    free(l);
}

/*
int main()
{
    
    List* h = allocate_lists_array(100);
    h[3] = newList();
    push(&h[3], 4);
    push(&h[3], 5);
    push(&h[3], 9);
    push(&h[3], 19);
    printf("\n%f\n", get(h[3],3));
    //free_list(h[3]);
    //free(h);
    free_lists_array(h,100);
    //free_list(h[3]);
    return 0;
}
*/