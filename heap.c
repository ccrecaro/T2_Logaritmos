#include "heap.h"


normalHeap crearHeapNormal(int size){
	vertice* verts = (vertice*) malloc(size * sizeof(vertice));
	int* pos = (int*) malloc(size * sizeof(int));
	
	normalHeap heapNormal;
	heapNormal.arreglo=verts;
	heapNormal.posiciones=pos;
	heapNormal.size=0;
	return heapNormal;
	
} 

void cambiar(vertice *x, vertice *y){ 
    vertice aux = *x; 
    *x = *y; 
    *y = aux; 
} 

    
void insertar(normalHeap* heapNormal, vertice k){ 
    heapNormal->size++; 
    int i = heapNormal->size - 1;
    heapNormal->posiciones[k.i]=i;
    heapNormal->arreglo[i] = k; 
  

	while (i != 0 && heapNormal->arreglo[(i-1)/2].prioridad > heapNormal->arreglo[i].prioridad){ 
		heapNormal->posiciones[heapNormal->arreglo[i].i]=(i-1)/2;
		heapNormal->posiciones[heapNormal->arreglo[(i-1)/2].i]=i;
       cambiar(&heapNormal->arreglo[(i-1)/2],&heapNormal->arreglo[i]); 
       
       i = (i-1)/2; 
    } 
} 

void decreaseKey(normalHeap* heapNormal, int i, double newPrior){
	
	int k=heapNormal->posiciones[i];
	
	heapNormal->arreglo[k].prioridad = newPrior;
	
	while (k!= 0 && heapNormal->arreglo[(k-1)/2].prioridad > heapNormal->arreglo[k].prioridad){
		heapNormal->posiciones[heapNormal->arreglo[k].i]=(k-1)/2;
		heapNormal->posiciones[heapNormal->arreglo[(k-1)/2].i]=k;
		cambiar(&heapNormal->arreglo[(k-1)/2],&heapNormal->arreglo[k]);
		

		k = (k-1)/2;
	}
		


}

void reordenar(normalHeap* heapNormal, int i) { 
	
    int min = i; 
    
    if (heapNormal->size>2*i + 1 && heapNormal->arreglo[2*i + 1].prioridad < heapNormal->arreglo[i].prioridad) 
        min = 2*i + 1; 
        
    if (heapNormal->size>2*i + 2 && heapNormal->arreglo[2*i + 2].prioridad < heapNormal->arreglo[min].prioridad) 
        min = 2*i + 2; 
        
    if (min != i){ 
		heapNormal->posiciones[heapNormal->arreglo[i].i]=min;
		heapNormal->posiciones[heapNormal->arreglo[min].i]=i;
        cambiar(&heapNormal->arreglo[i], &heapNormal->arreglo[min]);
        
    } 
} 


vertice extraerMin(normalHeap* heapNormal){
	vertice min = heapNormal->arreglo[0];
	heapNormal->size--;
	
    if (heapNormal->size > 0){
		
		heapNormal->arreglo[0] = heapNormal->arreglo[heapNormal->size]; 
		reordenar(heapNormal, 0);
      
    } 
  
    return min; 
}




void dijkstra_heapNormal(vecinos *lista, int N, int O){

	int i;
	double dist[N];
	int prev[N];
	normalHeap NH = crearHeapNormal(N);
	vertice auxV;
	for(i=0;i<N;i++){
		if(i==O)
			dist[i]=0.0;
		else
			dist[i]=INFINITY;

		prev[i] = -1;
		auxV.i=i;
		auxV.prioridad=dist[i];
		insertar(&NH,auxV);
		
	}

	
	double newDist;
	
	while(NH.size>0){
		
		auxV = extraerMin(&NH);
		
		vecinos aux = lista[auxV.i]->next;
		while(aux!=NULL){
			newDist = auxV.prioridad + aux->peso;
			
			if(newDist < dist[aux->v_nodo]){
					dist[aux->v_nodo] = newDist; 
					prev[aux->v_nodo] = auxV.i; 
					decreaseKey(&NH,aux->v_nodo,newDist);

				}
			aux = aux->next;
		}
		
		
	}
	
	
	
}
