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
	
	
}
