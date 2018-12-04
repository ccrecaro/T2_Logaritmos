#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



double** crearGrafo(int N, int aristas){
	int i,j;
	int selected[N];
	double **matriz;
	matriz = (double**) malloc( N * sizeof(double*) );
	for(i=0; i< N; i++){
		matriz[i] = (double*) malloc( N * sizeof(double) );
		selected[i]=0;
	}
	
	for(i=0;i<N;i++){
		
		for(j=0;j<N;j++){
			
			if(j==i)
				matriz[i][j]=0.;
			else
				matriz[i][j]=-1.;
		}
		
		
		
	}
	
	for(i=0;i<N-1;i++){
		
		matriz[i][i+1]= rand() / ((double) RAND_MAX);
		
	}
	
	
	aristas = aristas-N+1;

	int num;
           
	while(aristas>0){
		
		num = rand()%N;
	
		if(selected[num]==0){
			selected[num]=1;
			for(i=0;i<N;i++){
				if(aristas==0)
					break;
				if(matriz[num][i]<0){
					matriz[num][i]= rand() / ((double) RAND_MAX);
					aristas--;
					printf("%d\n",aristas);
					
				}
				
			}
			
		}
		
		else
			continue;		
		
		
	}
	
	return matriz;
	
} 


int main(int argc, char **argv){
	
	
	int i,j;
	int N=100000;
	double** matriz=crearGrafo(N,10*N);



    return 0; 
} 
