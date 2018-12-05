#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct vecinos{
    int v_nodo;
    double peso;
    struct vecinos* next;
}*vecinos;

void agregarVecino(vecinos* the_files, int vecino,double new_peso);

vecinos* crearVecinos(int N, int vertices);
