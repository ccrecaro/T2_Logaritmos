#include "grafo.h"

void agregarVecino(vecinos* new_vecino, int vecino,double new_peso) 
{ 
    vecinos new_insert = (vecinos) malloc(sizeof(vecinos)); 
    new_insert->next = NULL; 
    
    new_insert->v_nodo=vecino;
    new_insert->peso=new_peso; 
    

    if (*new_vecino == NULL) 
    { 
       new_vecino = &new_insert; 
       return; 
    }   
    
    vecinos last = *new_vecino;

    while (last->next != NULL) 
        last = last->next; 

    last->next = new_insert; 
    return;     
}



vecinos* crearVecinos(int N, int vertices){
	
	vecinos* lista;
	int marcados[N][N];
	lista=malloc(N*sizeof(vecinos));

	for(int i=0;i<N;i++){
		lista[i]=malloc(sizeof(vecinos));
		lista[i]->v_nodo=i;
		lista[i]->peso = 0;
		lista[i]->next=NULL;
		
		for(int j=0;j<N;j++)
			marcados[i][j]=0;
	}
	
	
	double new_peso;
	for(int i=0;i<N;i++){
		new_peso=rand()/((double) RAND_MAX);
		agregarVecino(&lista[i],(i+1)%N,new_peso);
		marcados[i][i]=1;
		marcados[i][(i+1)%N]=1;
		
	}
	
	
	int cada_uno = (int)ceil(vertices/N)-1;
	int new_cada_uno;
	vertices=vertices-N;
	int num;
	
	while(vertices>0){
		
		for(int i=0;i<N;i++){
			if(vertices<=0)
				break;
			new_cada_uno = cada_uno;
			while(new_cada_uno>0){
				num = rand()%N;
				if(marcados[i][num]==1)
					continue;
				new_peso=rand()/((double) RAND_MAX);
				agregarVecino(&lista[i],num,new_peso);
				marcados[i][num]=1;
				new_cada_uno--;
				vertices--;
				if(vertices<=0)
					break;
			}
			
			
			
		}
		
	}
	
	return lista;
	
	
}
