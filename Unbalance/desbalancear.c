#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "desbalancear.h"

void desbalancear(Nodo **pa, Nodo **pult){
    // caso base
    if(*pa == NULL){
        *pult = NULL;
        return;
    }
    // creamos dos nodos, donde guardarémos la referencia del subárbol izq y der
    Nodo* izqa = (*pa) -> izq;
    Nodo* dera = (*pa) -> der;
    // creamos dos nodos que serán el último nodo del subárbol izq y der
    Nodo* ultizq = NULL;
    Nodo* ultder = NULL;
    // desbalanceamos ambos lados del árbol
    desbalancear(&izqa, &ultizq);
    desbalancear(&dera, &ultder);
    // desconectamos el nodo actual al subárbol izquierdo
    (*pa) -> izq = NULL;
    // si el subárbol derecho no es nulo, lo "conectamos"
    if(dera != NULL){
        (*pa)->der = dera; 
        *pult = ultder; 
    }else{ 
        *pult = *pa; 
    }
    // si el subárbol izquierdo no es nulo, lo "conectamos"
    if(izqa != NULL){
        ultizq -> der = *pa; 
        *pa = izqa;
    }else{
        return;
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    // caso base
    if(a == NULL){
        *pult = NULL;
        return NULL;
    }
    // creamos dos nodos, donde guardarémos la referencia del subárbol izq y der
    Nodo* izqa = a -> izq;
    Nodo* dera = a -> der;
    // creamos dos nodos que serán el último nodo del subárbol izq y der
    Nodo* ultizq = NULL;
    Nodo* ultder = NULL;
    // creamos dos nodos desbalanceados para los subárboles izquierdo y derecho
    Nodo* nodo_izq = desbalanceado(izqa, &ultizq);
    Nodo* nodo_der = desbalanceado(dera, &ultder);
    // creamos el nuevo nodo desbalanceado
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo -> hash = (a -> hash);
    nodo -> id = (a -> id);
    nodo -> izq = NULL;
    nodo -> der = nodo_der;
    // se ajusta el último nodo del subárbol derecho
    if(nodo_der != NULL){
        *pult = ultder;
    }else{
        *pult = nodo;
    }
    // si existe el subárbol izquierdo, conectamos el último nodo
    if(nodo_izq != NULL){
        (ultizq->der) = nodo;
        return nodo_izq;
    }else{
        return nodo;
    }
}
