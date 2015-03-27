/* 
 * File:   main.c
 * Author: julior
 *
 * Created on 25 de marzo de 2015, 07:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * 
 */



typedef int tipoElemento;


 struct nodo{
    tipoElemento dato;
    int fe;
    struct nodo *izdo,*dcho; 

};

typedef struct nodo Nodo;


Nodo * crearNodo(tipoElemento x);
void rotacionII(Nodo** n, Nodo* n1);
void rotacionDD(Nodo** n,Nodo* n1 );
void rotacionID(Nodo** n,Nodo* n1);
void rotacionDI(Nodo** n, Nodo* n1);
void insertarAVL(Nodo** raiz,tipoElemento clave,int *h);
void insertar(Nodo** raiz,tipoElemento dato);
void vizualizar(Nodo * r);
int  numDatos(Nodo * r);
void Burbuja(int v[],int n);
void quicksort(int a[],int primero,int ultimo);



int main(int argc, char** argv) {
 
    
    
int v[]={3, 34, 1, 53, 15, 6,2,7};
int i,j;


//Burbuja(v,6);
// Ordenación
quicksort(v,0,8);


for(i=0;i<8;i++){
    printf("%d\n",v[i]);
}


   
    /*
    Nodo * raiz;
    raiz=NULL;
   
   // inicio del archivo 
    FILE *flujo = fopen("mis_numeros.txt","rb");
    if(flujo==NULL){
        perror("error");
        return 1;
    }
    int numero;
    double end;
    double tiempoTotal;
    while (feof(flujo)==0){
    
        fscanf(flujo,"%d \n",&numero);
        
        //*********************************
        clock_t start = clock(); 
        insertar(&raiz,numero);
        end=  (((double)clock() - start) / CLOCKS_PER_SEC);
        tiempoTotal+=end;  
        printf("Tiempo transcurrido : %f seg", end); 
        printf("\n");
        
        //**********************************
        
    }
    
    // tiempo en recorrer el arbol...
    //*************************************
      double final;
     // printf("\n"); 
      clock_t inicio= clock();
       vizualizar(raiz);
      final= (((double)clock() - inicio) / CLOCKS_PER_SEC);
      printf("Tiempo en Recorrer El arbol : %f seg",final); 
       //*******************************************  
      int num= numDatos(raiz);
      printf("\n\nTiempo Total en Insertar  %d Datos al Arbol : %f seg", num,tiempoTotal);
      fclose(flujo);
      printf("\n\n El archivo a sido leido correctamente.");
   
      //************************************************
      // final del archivo
    
     // return 0;
    
    
    */
    return (EXIT_SUCCESS);
}





// funciones de rotacion dobles y simples...

Nodo * crearNodo(tipoElemento x){
    Nodo * t;
    t= (Nodo*)malloc(sizeof(Nodo));
    t->dato=x;
    t->izdo=t->dcho=NULL;
    t->fe=0;
    return t;

}


void rotacionII(Nodo** n, Nodo* n1){
   (*n)->izdo=n1->dcho;
   n1->dcho=(*n);
   if (n1->fe==-1){
       (*n)->fe=0;
       n1->fe=0;
   }else{
   (*n)->fe=-1;
   n1->fe=1;
   
   }
   (*n)=n1;
            
}


void rotacionDD(Nodo** n,Nodo* n1 ){
  
    (*n)->dcho = n1->izdo;
    n1->izdo=(*n);
    if(n1->fe==+1){
        (*n)->fe=0;
        n1->fe=0;
    }else{
        (*n)->fe=+1;
        n1->fe=-1;
    }
    (*n)=n1;

}

void rotacionID(Nodo** n,Nodo* n1){
    Nodo *n2;
    n2= n1->dcho;
    (*n)->izdo= n2->dcho;
    n2->dcho=*n;
    n1->dcho=n2->izdo;
    n2->izdo=n1;
    
    // actualizacion de factores de equilibrio

    if (n2->fe==+1)
        n1->fe=-1;
    else
        n1->fe=0;
    
    if (n2->fe==-1)
        
      (*n)->fe=1;
    else
        (*n)->fe=0;
    
    
    n2->fe=0;
    (*n)=n2;

}

void rotacionDI(Nodo** n, Nodo* n1){
    Nodo* n2;
    
    n2= n1->izdo;
    (*n)->dcho= n2->izdo;
    n2->izdo=*n;
    n1->izdo=n2->dcho;
    n2->dcho=n1;
    
    if (n2->fe==+1)
        (*n)->fe=-1;
    else
        (*n)->fe=0;
    
    if (n2->fe==-1)
        n1->fe=1;
    else
        n1->fe=0;
                
     n2->fe=0;
    (*n)=n2;
              

}

// funcion para insertar en el arbol

void insertarAVL(Nodo** raiz,tipoElemento clave,int *h){
    Nodo* n1;
    if(!(*raiz)){
    
        *raiz = crearNodo(clave);
        *h=1;
    
    }
    else if(clave<(*raiz)->dato){
        insertarAVL(&((*raiz)->izdo),clave,h);
        
        if (*h){
        
            switch ((*raiz)->fe){
            
                case 1: (*raiz)->fe=0;
                (*h)=0;
                break;
                
                case 0: (*raiz)->fe=-1;
                break;
                
                case -1: 
                    n1=(*raiz)->izdo;
                    if(n1->fe==-1)
                        
                        rotacionII(raiz,n1);
                    else
                        rotacionID(raiz,n1);
                    
                    (*h)=0;
                   // break;
            }
        
        }
            
            
    
    }
    else if (clave>(*raiz)->dato){
        
        insertarAVL(&((*raiz)->dcho),clave,h);
        
        if (*h){
        
            switch ((*raiz)->fe){
            
                case 1:
                    n1=(*raiz)->dcho;
                    if(n1->fe==+1)
                        rotacionDD(raiz,n1);
                    else
                        rotacionDI(raiz,n1);
                    
                    (*h)=0;
                    break;
                    
                case 0: (*raiz)->fe=+1;
                break;
                case -1: (*raiz)->fe=0;
                (*h)=0;
                break;
            
            
            }
        
        }
        
        
        
    
    }else{
    
        puts("Error se ha repetido la clave");
        (*h)=0;
    }
}


void insertar(Nodo** raiz,tipoElemento dato){
   
    int creceAltura;
    insertarAVL(raiz,dato,&creceAltura);
}


// funcion que cuenta y muestra arbol
void vizualizar(Nodo* r){
    
    if (r){
        
        int izq,der;
        vizualizar(r->izdo);
        printf(" Dato: %d  ",r->dato);
        printf("\n");
         vizualizar(r->dcho);
        
        
        
        //return izq+der+1;
    
    }
}

int numDatos(Nodo* r){
   
    if (r){
        
        int izq,der;
        izq= numDatos(r->izdo);
        //printf(" Dato: %d  ",r->dato);
        
        //printf("\n");
        
        der= numDatos(r->dcho);
        
       
        
        return izq+der+1;
    
    }else
        
        
        return 0;
}


void Burbuja(int v[],int n){

    int j,i,aux;
    
    for(i=0; i<n; i++){
	// Comparaciones
	for(j=0; j<n-i; j++){
	// Intercambiar los elementos
	if(v[j] > v[j+1]){
		aux=v[j];
		v[j]=v[j+1];
		v[j+1]=aux;
		}
	}
}

    

}


void quicksort(int a[],int primero,int ultimo){

    int i,j,central;
    int pivote;
    
    central= (primero+ultimo)/2;
    pivote=a[central];
    i=primero;
    j=ultimo;
    
    do{
    
        while (a[i]<pivote)i++;
        while (a[j]>pivote)j--;
    
        if(i<=j){
            
            int tmp;
            tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
            i++;
            j--;
        
        }
    
    
    }while (i<=j);
    
    if(primero<j)
        quicksort(a,primero,j);
    if(i<ultimo)
        quicksort(a,i,ultimo);

    

} 



