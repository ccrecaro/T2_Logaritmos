#include "grafo.h"

// para compilar 
// gcc -g -o ensayos ensayos.c arreglo.c grafo.c heap.c fibonacci_heap.c -lm
void dijkstra_arreglo(vecinos *lista, int N, int O);
void dijkstra_heapNormal(vecinos *lista, int N, int O);
void dijkstra_fibonacciHeap(vecinos *grafo,int N, int origen);

int main(){
	
	int i,j;
	
	int N=100000;
	int K=10;
	int N_ensayos=10;
	
	vecinos* lista;
	int O;
	clock_t begin, end;
	double time_spent;
	
	FILE *archivoF = fopen("fibonacci.dat","w"); 
	FILE *archivoH = fopen("heap.dat","w"); 
	FILE *archivoA = fopen("arreglo.dat","w"); 
	
	for(i=1;i<4;i++){
		
		printf("\ngenerando datos\n");
		lista=crearVecinos(N,K*N);
		printf("generacion de datos terminada\n");
		
		for(j=0;j<N_ensayos;j++){
			
			O = rand()%N;
			
			
			printf("\narreglo\n");
			begin = clock();
			dijkstra_arreglo(lista,N,O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoA,"%.5f\n",time_spent);
			
			printf("\nheap\n");
			begin = clock();
			dijkstra_heapNormal(lista, N, O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoH,"%.5f\n",time_spent);
	
			
			printf("\nfibonacci\n");
			begin = clock();
			dijkstra_fibonacciHeap(lista, N, O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoF,"%.5f\n",time_spent);
			
	
			
			
			
			
		}
		fprintf(archivoF,"\n");
		fprintf(archivoH,"\n");
		fprintf(archivoA,"\n");
		
		
		K=K*10;
		
	}
		
    
	fclose(archivoF);
	fclose(archivoH);
	fclose(archivoA);
	
	
	
	return 0;
}


