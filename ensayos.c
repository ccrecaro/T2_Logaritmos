#include "fibonacci_heap.c"
#include "arreglo.c"
#include "heap.c"
#include "grafo.c"

int main(){
	
	int i,j;
	
	int N=100000;
	int K=10;
	int N_ensayos=10;
	double** matriz=crearGrafo(N,10*N);
	int O;
	clock_t begin, end;
	double time_spent;
	
	FILE *archivoF = fopen("fibonacci.dat","w"); 
	FILE *archivoH = fopen("heap.dat","w"); 
	FILE *archivoA = fopen("arreglo.dat","w"); 
	
	for(i=1;i<4;i++){
		
		matriz=crearGrafo(N,K*N);
		
		
		for(j=0;j<N_ensayos;j++){
			
			O = rand()%N;
			
			begin = clock();
			dijkstra_fibonacciHeap(matriz, N, O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoF,"%.5f\n",time_spent);
	
	
			begin = clock();
			dijkstra_fibonacciHeap(matriz, N, O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoH,"%.5f\n",time_spent);
	
	
			begin = clock();
			dijkstra_arreglo(matriz,N,O);
			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fprintf(archivoA,"%.5f\n",time_spent);
			
			
			
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


