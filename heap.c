#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct vertice{
	int i;
	double prioridad;
	
}vertice;


typedef struct normalHeap{ 
    vertice *arreglo; 
    int size; 
}normalHeap;
  

normalHeap crearHeapNormal(int size){
	vertice* verts = (vertice*) malloc(size * sizeof(vertice));
	normalHeap heapNormal;
	heapNormal.arreglo=verts;
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
    heapNormal->arreglo[i] = k; 
  

	while (i != 0 && heapNormal->arreglo[(i-1)/2].prioridad > heapNormal->arreglo[i].prioridad){ 
       cambiar(&heapNormal->arreglo[(i-1)/2],&heapNormal->arreglo[i]); 
       i = (i-1)/2; 
    } 
} 

void decreaseKey(normalHeap* heapNormal, int i, double newPrior){
	
	for(int k=0;k<heapNormal->size;k++){
		
		if(heapNormal->arreglo[k].i==i){
			
			heapNormal->arreglo[k].prioridad = newPrior;
			
			while (k!= 0 && heapNormal->arreglo[(k-1)/2].prioridad > heapNormal->arreglo[k].prioridad){ 
				cambiar(&heapNormal->arreglo[(k-1)/2],&heapNormal->arreglo[k]); 
				k = (k-1)/2; 
			}
			break;
			
		}
		
		
	}

}

void reordenar(normalHeap* heapNormal, int i) { 
	
    int min = i; 
    
    if (heapNormal->size>2*i + 1 && heapNormal->arreglo[2*i + 1].prioridad < heapNormal->arreglo[i].prioridad) 
        min = 2*i + 1; 
        
    if (heapNormal->size>2*i + 2 && heapNormal->arreglo[2*i + 2].prioridad < heapNormal->arreglo[min].prioridad) 
        min = 2*i + 2; 
        
    if (min != i){ 
        cambiar(&heapNormal->arreglo[i], &heapNormal->arreglo[min]); 
        reordenar(heapNormal,min); 
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




void dijkstra_heapNormal(double **matriz, int N, int O){

	int i,j;
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
		for(j=0;j<N;j++){
			
			if(matriz[auxV.i][j]>0){
				
				newDist = auxV.prioridad + matriz[auxV.i][j];
				
				if(newDist < dist[j]){
					dist[j] = newDist; 
					prev[j] = auxV.i; 
					decreaseKey(&NH,j,newDist);

				}
				
				
			}
			
		}
		
		
	}
	
	
	
	for(i=0;i<N;i++)
		printf("%f\t%d\n",dist[i],prev[i]);
	
}





  

int main(int argc, char **argv){
	
	int i,j;
	double **matriz;
	int N = 5;
	matriz = (double**) malloc( N * sizeof(double*) );
	for(i=0; i< N; i++){
		matriz[i] = (double*) malloc( N * sizeof(double) );
	}
	
	double matriz_aux[5][5] = { {0,7,-1,2,-1},{-1,0,1,2,-1},{-1,-1,0,-1,5},{-1,3,8,0,5},{-1,-1,4,-1,0}};
	
	for(i=0; i< N; i++){
		for(j=0; j< N; j++)
			matriz[i][j] = matriz_aux[i][j];
	}
	
	
	


	dijkstra_heapNormal(matriz,N,4);
	

	
	
	






    return 0; 
} 
