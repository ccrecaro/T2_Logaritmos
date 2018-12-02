#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

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

FibonacciHeap* initialize_fh(){
    FibonacciHeap *H = malloc(sizeof(FibonacciHeap));
    H->n = 0;
    H->min = NULL;
    return H;
}

/*Insertar un nodo x en un Fibonacci Heap H*/
void insert(FibonacciHeap *H, Node *x){
    x->degree = 0;
    x->p = NULL;
    x->child = NULL;
    x->mark = false;

    if(H->min==NULL){
        //root list para H contiene solo a x
        x->left = x;
        x->right = x;
        H->min = x;
    }

    else{
        //Inserto x en la root list de H
        H->min->right->left = x;
        x->left = H->min;
        x->right = H->min->right;
        H->min->right = x;

        //De ser necesario, se cambia nodo minimo
        if(x->key < H->min->key){
            H->min = x;
        }
    }
    H->n++;
}

Node* find_min(FibonacciHeap *H){
    return H->min;
}

FibonacciHeap* fib_heap_union(FibonacciHeap *H1, FibonacciHeap *H2){
    FibonacciHeap *H= initialize_fh();
    H->min = H1->min;
    //concateno H2 a root list de H
    H->min->left->right = H2->min->right;
    H2->min->right->left = H->min->left;
    H->min->left = H2->min;
    H2->min->right = H->min;
    
    if(H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key)){
        H->min = H2->min;
    }

    H->n = H1->n + H2->n;
    return H;
}

/*Cambia la key del nodo x por una menor*/
void decreaseKey(FibonacciHeap *H, Node *x, int k){
    if(k > x->key){
        printf("Error: La nueva key es mas grande que la key actual");
    }
    else{
        x->key = k;
        Node *y = x->p;
        if (y != NULL && x->key < y->key){
            cut(H, x, y);
            cascading_cut(H, y);
        }
        if (x->key < H->min->key){
            H->min = x;
        }
    }
}

/*Corta el link entre x  y su padre y, haciendo de x una raiz*/
void cut(FibonacciHeap *H, Node *x, Node *y){
    //sacar x de la child list de y, decrementando y.degree
    if(x == x->right){
        y->child = NULL;
    }
    else{
        x->left->right = x->right;
        x->right->left = x->left;
    }
    y->degree--;

    //Agregar x a la root list de H
    H->min->right->left = x;
    x->right = H->min->left;
    x->left = H->min;
    H->min->right = x;

    x->p = NULL;
    x->mark = false;
}

/**/
void cascading_cut(FibonacciHeap *H, Node *y){
    Node *z = y->p;
    if(z != NULL){
        if(y->mark == false){
            y->mark = true;
        }
        else{
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}