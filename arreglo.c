#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



void dijkstra_arreglo(double **matriz, int N, int O){

	int i,j;


	double dist[N];
	int marcados[N];
	int prev[N];
	
	for(i=0;i<N;i++){
		dist[i]=INFINITY;
			
		marcados[i] = 0;
		prev[i] = -1;
		
	}
	dist[O]=0.0;
	
	double minDist;
	int minNodo;
	int u;
	for(i=0;i<N;i++){
		minDist=INFINITY;
		minNodo=0;
		
		for(j=0;j<N;j++){
			
			if(!marcados[j] && dist[j]<minDist){
				minDist = dist[j];
				minNodo = j;
				
			}
			
		}
		
		
		u = minNodo;
		marcados[u]=1;
		
		
		
		for(j=0;j<N;j++){
			
			if(matriz[u][j]>0){
				
				if(dist[j]>dist[u]+matriz[u][j]){
					dist[j] = dist[u]+matriz[u][j];
					prev[j] = u;
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
	
	
	


	dijkstra_arreglo(matriz,N,4);
	
	return 0;
}
