#include "arreglo.h"


void dijkstra_arreglo(vecinos *lista, int N, int O){
	//1 es true 0 es false
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
		
		vecinos aux = lista[u]->next;
		while(aux!=NULL){
			if(dist[aux->v_nodo]>dist[u]+ aux->peso ){
				dist[aux->v_nodo] = dist[u]+aux->peso;
				prev[aux->v_nodo] = u;
			}
			aux = aux->next;
		}
		
		
	}
	
	for(i=0;i<N;i++)
		printf("%f\t%d\n",dist[i],prev[i]);
	
}




