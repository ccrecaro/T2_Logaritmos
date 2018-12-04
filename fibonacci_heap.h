#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


typedef int bool;
#define true 1
#define false 0

typedef struct Node{
    int value; //valor del nodo
    int degree; //numero de childrens
    bool mark; //si perdio un hijo
    struct Node *p; //puntero a los padres
    struct Node *child; //puntero a un hijo
    struct Node *left;
    struct Node *right;
    double prioridad; //Se trabaja la prioridad como el key del fibonacci heap
    void *payload; 
}Node;

typedef struct FibonacciHeap{
    Node *min; //minimum node 
    int n; //numero actual de nodos en el heap
}FibonacciHeap;
