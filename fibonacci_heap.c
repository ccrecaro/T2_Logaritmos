#include "fibonacci_heap.h"

Node* initialize_node(int k){
    Node *n = malloc(sizeof(Node));
    n->key = k;
    n->degree = 0;
    n->mark = false;
    n->p = NULL;
    n->child = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;

}

FibonacciHeap* initialize_fh(){
    FibonacciHeap *H = malloc(sizeof(FibonacciHeap));
    H->n = 0;
    H->min = NULL;
    return H;
}

/*Insertar un nodo x en un Fibonacci Heap H*/
void insert(FibonacciHeap *H, Node *x){
    x->degree = 0;
    x->p = NULL;
    x->child = NULL;
    x->mark = false;

    if(H->min==NULL){
        //root list para H contiene solo a x
        x->left = x;
        x->right = x;
        H->min = x;
    }

    else{
        //Inserto x en la root list de H
        H->min->right->left = x;
        x->left = H->min;
        x->right = H->min->right;
        H->min->right = x;

        //De ser necesario, se cambia nodo minimo
        if(x->key < H->min->key){
            H->min = x;
        }
    }
    H->n++;
}

Node* find_min(FibonacciHeap *H){
    return H->min;
}


void link(FibonacciHeap *H, Node *y, Node *x){
    y->left->right = y->right;
    y->right->left = y->left;
    y->p = x;
    y->right = y;
    y->left = y;

    if(x->child != NULL){
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->child = y;
    x->degree++;
    y->mark = false;
}


FibonacciHeap* fib_heap_union(FibonacciHeap *H1, FibonacciHeap *H2){
    FibonacciHeap *H= initialize_fh();
    H->min = H1->min;
    //concateno H2 a root list de H
    H->min->left->right = H2->min->right;
    H2->min->right->left = H->min->left;
    H->min->left = H2->min;
    H2->min->right = H->min;
    
    if(H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key)){
        H->min = H2->min;
    }

    H->n = H1->n + H2->n;
    return H;
}


void consolidate(FibonacciHeap *H){
    int DH_n = (int)floor(log10(H->n -1)/log10(2)); //upper bound D(H->n) en el degree maximo

    Node **A= malloc(DH_n * sizeof(Node*));
    for(int i=0; i<DH_n; i++){
        A[i]= NULL;
    }
    
    //calcular numero de nodos en root list
    int n_rlist = 0; //cantidad de nodos en root list
    Node *w =  H->min; //Para recorrer nodos en root list
    if(H->min != NULL){
        n_rlist++;
        while(w != H->min->left){
            n_rlist++;
            Node *buf = w->right;
            w = buf;
        }
    }

    w = H->min;

    for(int k=0; k<n_rlist; k++){
        
        Node *x = w;
        int d = x->degree;

        while(A[d] != NULL){
            
            Node *y = A[d]; //Otro nodo con el mismo degree que x
            if(x->key > y->key){
                Node *buf = x;
                x = y;
                y = buf;
            }
            link(H, y, x);
            A[d] = NULL;
            d++;
            
        }
        A[d] = x;

        w = w->right;
        
    }

    H->min = NULL;

    for(int i=0; i<=DH_n; i++){
        
        if(A[i] != NULL){
            if (H->min == NULL){
				H->min = A[i];
			} 
            else{
				H->min->left->right = A[i];
				A[i]->left = H->min->left;
				A[i]->right = H->min;
				H->min->left = A[i];
				if (A[i]->key < H->min->key){
					H->min = A[i];
				}
            }
        }
    }
    
}

/*Corta el link entre x  y su padre y, haciendo de x una raiz*/
void cut(FibonacciHeap *H, Node *x, Node *y){
    //sacar x de la child list de y, decrementando y.degree
    if(x == x->right){
        y->child = NULL;
    }
    else{
        x->left->right = x->right;
        x->right->left = x->left;
    }
    y->degree--;

    //Agregar x a la root list de H
    H->min->right->left = x;
    x->right = H->min->left;
    x->left = H->min;
    H->min->right = x;

    x->p = NULL;
    x->mark = false;
}

/**/
void cascading_cut(FibonacciHeap *H, Node *y){
    Node *z = y->p;
    if(z != NULL){
        if(y->mark == false){
            y->mark = true;
        }
        else{
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}

Node* extract_min(FibonacciHeap *H){
    Node *z = H->min;

    if(z != NULL){
        if(z == z->right){
            H->min = z->child;
           
            consolidate(H);
        }
        else{
            if(z->child == NULL){
                z->left->right = z->right;
                z->right->left = z->left;
                H->min = z->right;
               
                consolidate(H);
            }
            else{
                z->left->right = z->child;
                z->right->left = z->child->left;
                z->child->left->right = z->right;
                z->child->left = z->left;
                H->min = z->right;
              
                consolidate(H);
            }
        }
        H->n--;

    }
    return z;
}


/*Cambia la key del nodo x por una menor*/
void decreaseKey(FibonacciHeap *H, Node *x, int k){
    if(k > x->key){
        printf("Error: La nueva key es mas grande que la key actual");
    }
    else{
        x->key = k;
        Node *y = x->p;
        if (y != NULL && x->key < y->key){
            cut(H, x, y);
            cascading_cut(H, y);
        }
        if (x->key < H->min->key){
            H->min = x;
        }
    }
}

int main(){

	FibonacciHeap *H = initialize_fh();
	Node *x1 = initialize_node(1);
    Node *x2 = initialize_node(2);
    Node *x3 = initialize_node(3);
    Node *x4 = initialize_node(9);

    insert(H, x1);
    insert(H,x2);
    insert(H, x3);
    insert(H, x4);

    Node *min= find_min(H);
    assert(min->key == 1);
    assert(min->left->key == 2);
    assert(min->left->left->key == 3);
    assert(min->left->right->key == 1);
    assert(min->left->left->left->key == 9);
    assert(min->right->key == 9);

    Node  *n= extract_min(H);
    assert(n->key == 1);

    Node *min2= find_min(H);
    assert(min2->key == 2);

	printf("\nSuccess!\nResults are in the file output.txt\n");

	return 0;
}