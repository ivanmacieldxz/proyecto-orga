
#include "headers.h"
#include <stdlib.h>

int cant_hijos(TNodo n);

TColaCP crear_cola_cp(int (*f) (TEntrada, TEntrada)) {
    TColaCP cp = (TColaCP) malloc(sizeof(struct cola_con_prioridad));

    //Inicializa cola vac�a
    cp->cantidad_elementos = 0; //Cantidad de elementos cero
    cp->comparador = f; //Comparador funci�n f
    cp->raiz = NULL; //No hay nodo raiz

    return cp;
}

int cp_insertar(TColaCP cola, TEntrada entrada) {
    //asumo que no se pudo insertar
    int retornar = FALSE;

    //si la entrada no es nula
    if (entrada != NULL) {
        //creo el nodo e inicializo sus campos
        TNodo n = (TNodo) malloc(sizeof(struct nodo));
        n->entrada = entrada;
        n->padre = NULL;
        n->hijo_derecho = NULL;
        n->hijo_izquierdo = NULL;

        

        //si está vacía
        if (cola->cantidad_elementos == 0) {
            cola->raiz = n;//Agrega nodo como raiz de la cola
            cola->cantidad_elementos = 1; //incrementa a uno la cantidad de elementos

            retornar = TRUE;
        } else {
            //encuentro la posición que le corresponde e inserto en la cola
            insertar_al_final(cola, n);
        }
    }

    return retornar;
}

void insertar_al_final(TColaCP cola, TNodo n) {
    TNodo actual = cola->raiz;

    //mientras el nodo actual tenga dos hijos
    while (TRUE) {
        
    }
}

int cant_hijos(TNodo n) {
    int cant = 0;

    if (n->hijo_derecho != NULL) {
        cant = 2;
    } else if (n->hijo_izquierdo != NULL) {
        cant = 1;
    }

    return cant;
}