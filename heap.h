#include "grafo.h"

typedef struct vertice{
	int i;
	double prioridad;
	
}vertice;


typedef struct normalHeap{ 
    vertice *arreglo;
    int* posiciones;
    int size;
}normalHeap;


normalHeap crearHeapNormal(int size); 

void cambiar(vertice *x, vertice *y); 

void insertar(normalHeap* heapNormal, vertice k); 

void decreaseKey(normalHeap* heapNormal, int i, double newPrior);

void reordenar(normalHeap* heapNormal, int i); 

vertice extraerMin(normalHeap* heapNormal);

void dijkstra_heapNormal(vecinos *lista, int N, int O);

