#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int degree; //numero de childrens
    bool mark; //si perdio un hijo
    Node *p; //puntero a los padres
    Node *child; //puntero a un hijo
    Node *left;
    Node *right;
    int key; //key del heap
    void *payload; 
}Node;

typedef struct FibonacciHeap{
    Node *min; //minimum node 
    int n; //numero actual de nodos en el heap
}FibonacciHeap;

FibonacciHeap* initialize_fh();

/*Insertar un nodo x en un Fibonacci Heap H*/
void insert(FibonacciHeap *H, Node *x);

/*Entrega el nodo minimo del heap sin sacarlo*/
Node* find_min(FibonacciHeap *H);

/*Extrae y retorna el nodo minimo del heap*/
Node* extract_min(FibonacciHeap *H);

/*Hacer que cada raiz de la root list tenga distinto degree*/
void consolidate(FibonacciHeap *H);

FibonacciHeap* fib_heap_union(FibonacciHeap *H1, FibonacciHeap *H2);

/*Corta el link entre x  y su padre y, haciendo de x una raiz*/
void cut(FibonacciHeap *H, Node *x, Node *y);

/**/
void cascading_cut(FibonacciHeap *H, Node *y);

/*Cambia la key del nodo x por una menor*/
void decreaseKey(FibonacciHeap *H, Node *x, int k);