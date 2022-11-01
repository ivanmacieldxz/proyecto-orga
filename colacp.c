
#include "headers.h"
#include <stdlib.h>
#include <math.h>

void insertar_recursivamente(TColaCP cola, TNodo origen, int camino, TNodo nuevo);
void intercambiar(TNodo n, TNodo m);
TEntrada eliminar_recursivamente(TColaCP cola, TNodo origen, int camino);
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

        } else {
            //incremento el tamaño
            cola->cantidad_elementos++;
            // Encuentro la posición de inserción mediante la representación binaria del tamaño
            int camino = 1 << (int) (floor(log2(cola->cantidad_elementos)) - 1);

            insertar_recursivamente(cola, cola->raiz, camino, n);

        }

        retornar = TRUE;
    }

    return retornar;
}

void insertar_recursivamente(TColaCP cola, TNodo origen, int camino, TNodo nuevo) {
    int lado = cola->cantidad_elementos & camino;

    TNodo pasado;

    // si el cómputo del lado no es cero (1), voy a derecha en el árbol
    if (lado > 0) {
        //si llegué al bit más significativo, estoy en la posición a ocupar
        if (camino == 1)
            origen->hijo_derecho = nuevo;

        //actualizo al nodo pasado según corresponda (pasé por el hijo derecho, insertado o no)
        pasado = origen->hijo_derecho;
    } else {    //a izquierda
        //idem arriba
        if (camino == 1)
            origen->hijo_izquierdo = nuevo;

        //actualizo para que se corresponda con el hijo izquierdo (insertado nuevo o no)
        pasado = origen->hijo_izquierdo;
    }

    //si no estoy en el bit más significativo, sigo buscando la posición de inserción con recursión, con el nodo al que acabo de pasar y el camino sin el bit más significativo (ya pasé por el nodo asociado)
    if (camino > 1)
        insertar_recursivamente(cola, pasado, camino >> 1, nuevo);

    //si la prioridad del nodo insertado es mayor que la de su padre ()
    if (cola->comparador(nuevo->entrada, pasado->entrada) > 0)
        //intercambio los nodos
        intercambiar(nuevo, pasado);

}

void intercambiar(TNodo n, TNodo m) {
    TEntrada temp = n->entrada;
    n->entrada = m->entrada;
    m->entrada = temp;
}

/* Elimmina y retorna la entrada con mayor prioridad (menor clave) de la cola. Reacomoda la estructura heap de forma consistente.
Si la cola es vacía, retorna ELE_NULO*/
TEntrada cp_eliminar(TColaCP cola) {
    if (cola == NULL || (cola != NULL && cola->cantidad_elementos == 0))
        return ELE_NULO;

    TEntrada eliminada = cola->raiz->entrada;
    TNodo n;

    if (cola->cantidad_elementos == 1) {
        //free(cola->raiz);
        cola->raiz == NULL;
    } else {
        // Encuentro la hoja a eliminar a partir de la representación binaria del tamaño  (lógica similar a la de insertar)
        cola->raiz->entrada = eliminar_recursivamente(cola, cola->raiz, 1 << (int) (floor(log2(cola->cantidad_elementos)) - 1));

        n = cola->raiz;

        //llevar a la raíz hacia abajo
        while (TRUE) {
            TNodo min = n;
            if (n->hijo_izquierdo != NULL && cola->comparador(n->hijo_izquierdo->entrada, min->entrada) == -1)
                min = n->hijo_izquierdo;
            if (n->hijo_derecho != NULL && cola->comparador(n->hijo_derecho->entrada, min->entrada) == -1)
                min = n->hijo_derecho;
            if (min == n) break;

            intercambiar(n, min);

            n = min;
        }

    }


    cola->cantidad_elementos--;

    return eliminada;
}

TEntrada eliminar_recursivamente(TColaCP cola, TNodo origen, int camino) {
    int lado = cola->cantidad_elementos & camino;
    TNodo pasado;

    //si el lado es mayor a 0 (1) voy a derecha
    if (lado > 0) {
        pasado = origen->hijo_derecho;

        //si camino = 1 estoy en el bit más significativo, por lo que llegué al nodo a eliminar
        if (camino == 1) {
            //libero el espacio y asigno nulo
            //free(origen->hijo_derecho);
            origen->hijo_derecho = NULL;
        }
    } else {    //sino, voy a izquierda
        pasado = origen->hijo_izquierdo;

        //idem anterior
        if (camino == 1) {
            //libero el espacio y asigno nulo
            //free(origen->hijo_izquierdo);
            origen->hijo_izquierdo = NULL;
        }
    }

    //si llegué al final del camino, retorno la entrada del nodo que acabo de pasar, sino la que es producto de seguir con la recursión desde el nodo que acabo de pasar y descartando el bit menos significativo del camino (correspondiente al nodo que pasé)
    return camino == 1 ? pasado->entrada : eliminar_recursivamente(cola, pasado, camino>>1);
}

int cp_cantidad(TColaCP cola) {
    return cola->cantidad_elementos;
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
