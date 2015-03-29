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

 struct nLista{
    int dato;
    struct nLista *sig;
};
      typedef struct nLista NodoLista1;
      
        struct node
{
    int data;
    struct node *next;
};
  typedef struct node NodoLista;
      

      
     


Nodo * crearNodo(tipoElemento x);
void rotacionII(Nodo** n, Nodo* n1);
void rotacionDD(Nodo** n,Nodo* n1 );
void rotacionID(Nodo** n,Nodo* n1);
void rotacionDI(Nodo** n, Nodo* n1);
void insertarAVL(Nodo** raiz,tipoElemento clave,int *h);
void insertar(Nodo** raiz,tipoElemento dato);
void vizualizar(Nodo * r);
int  numDatos(Nodo * r);
int principal1();



      NodoLista1 *agregar(NodoLista1 *apuntador,int dato); 
      void ordenarLista(NodoLista1* lista);
      void showList(NodoLista1 *apuntador);
      void push(NodoLista** head_ref, int new_data);
      void printList(NodoLista *node);
      NodoLista *getTail(NodoLista *cur);
      NodoLista *partition(NodoLista *head, NodoLista *end,NodoLista **newHead, NodoLista**newEnd);
      NodoLista *quickSortRecur(NodoLista *head, NodoLista *end);
      void quickSort(NodoLista **headRef);
          

int main(int argc, char** argv) {

    
    
    
    principal1();
    
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
        printf(" ");
        vizualizar(r->dcho);



        //return izq+der+1;

    }
}

void vizualizar2(Nodo* r){
   
    
    
    if (r){

        int izq,der;
        vizualizar2(r->izdo);
        printf("%d ",r->dato);
        vizualizar2(r->dcho);



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


 NodoLista1 *agregar(NodoLista1 *apuntador,int dato){
          
              NodoLista1 *nuevo;
              nuevo= (NodoLista1*)malloc(sizeof(NodoLista1));
              nuevo->dato=dato;
              nuevo->sig=NULL;
                      
              if(apuntador==NULL){
              
                  apuntador=nuevo;
                  
              }else{
                  
                  NodoLista1* tmp;
                  tmp=apuntador;
                  while(tmp->sig!=NULL){
                      tmp=tmp->sig;
                  }
              
                  tmp->sig=nuevo;
              }        
              
              return apuntador;
              
          }

          
          void ordenarLista(NodoLista1* lista){
          
              NodoLista1 *actual,*siguiente;
              int t;
              
              actual=lista;
              
              while(actual->sig!=NULL){
                  siguiente= actual->sig;
                  
                  while(siguiente!=NULL){
                  
                      if(actual->dato > siguiente->dato){
                          t= siguiente->dato;
                          siguiente->dato=actual->dato;
                          actual->dato=t;
                      
                      }
                      siguiente= siguiente->sig;
                  }
                  
                  actual=actual->sig;
                  siguiente=actual->sig;
              }
              
          }
          
          
          
       
 
   
          void showList(NodoLista1 *apuntador){
          
              NodoLista1 *aux;
              aux=apuntador;
              while(aux!=NULL){
                  printf("Dato:%d\n",aux->dato);
                  aux=aux->sig;
              }
          
          }
    
          
          
          
          
          
          
        
/* A utility function to insert a node at the beginning of linked list */
void push(NodoLista** head_ref, int new_data)
{
    /* allocate node */
    NodoLista *new_node;
    new_node= (NodoLista*)malloc(sizeof(NodoLista));
    
 
    /* put in the data  */
    new_node->data  = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* A utility function to print linked list */
void printList(NodoLista *node)
{
      
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
 
// Returns the last node of the list
NodoLista *getTail(NodoLista *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}
 
// Partitions the list taking the last element as the pivot
NodoLista *partition(NodoLista *head, NodoLista *end,
                       NodoLista **newHead, NodoLista**newEnd)
{
    NodoLista *pivot = end;
    NodoLista *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot)
    {
        if (cur->data < pivot->data)
        {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur; 
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
           NodoLista *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    // Update newEnd to the current last node
    (*newEnd) = tail;
 
    // Return the pivot node
    return pivot;
}
 
 
//here the sorting happens exclusive of the end node
NodoLista *quickSortRecur(NodoLista *head, NodoLista *end)
{
    // base condition
    if (!head || head == end)
        return head;
 
   NodoLista *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    NodoLista *pivot = partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
       NodoLista *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);
 
        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);
 
    return newHead;
}
 
// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void quickSort(NodoLista **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}
    







int principal1(){
 
 Nodo * raiz;
 raiz=NULL;
 
 NodoLista *a = NULL;
    NodoLista1 *raiz1;
    raiz1= NULL;
   
    

   // inicio del archivo
    FILE *flujo = fopen("mis_numeros.txt","rb");
    if(flujo==NULL){
        perror("error");
        return 1;
    }
    int numero;
    int n;
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
        push(&a, numero);
        raiz1= agregar(raiz1,numero);
       

      //**********************************

    }
      
     double final;
       clock_t inicio= clock();
       vizualizar(raiz);
       printf("\n");
       final= (((double)clock() - inicio) / CLOCKS_PER_SEC);
      printf("Tiempo en Recorrer El arbol : %f seg",final);
      
      int num= numDatos(raiz);
      printf("\n\nTiempo Total en Insertar  %d Datos al Arbol : %f seg", num,tiempoTotal);
      
      printf("\n\n");
      
      double end1;
      clock_t start1= clock();
      quickSort(&a);
      end1= (((double)clock() - start1) / CLOCKS_PER_SEC);
       printf("Tiempo en Ordenar Metodo quickSort : %f seg",end1);
      
       printf("\n\n");
       
       
       double end2;
       clock_t start2= clock();
       ordenarLista(raiz1);
      end2= (((double)clock() - start2) / CLOCKS_PER_SEC);
       printf("Tiempo en Ordenar Metodo Burbuja : %f seg",end2);
      
      // ordenarLista(raiz1);
       
       printf("\n\n");
       
        printf("SALIDA ORDENADA\n");
        printf("\n");
       printList(a);
       printf("\n\n");
       
       printf("SALIDA RECORRIDO ARBOL\n");
       printf("\n");
       vizualizar2(raiz);            
       
      fclose(flujo);
      printf("\n\n El archivo a sido leido correctamente.");

      //************************************************
      // final del archivo

     // return 0;

}







