
#include "headers.h"
#include <stdlib.h>
#include <math.h>

void insertar_recursivamente(TColaCP cola, TNodo origen, TNodo nuevo);
void acomodar_por_insercion(TColaCP cola, TNodo actual);
void acomodar_por_eliminacion(TColaCP cola, TNodo actual);
int cant_hijos(TNodo n);
int cant_descendientes(TNodo nodo);

TColaCP crear_cola_cp(int (*f) (TEntrada, TEntrada)) {
    TColaCP cp = (TColaCP) malloc(sizeof(struct cola_con_prioridad));

    //Inicializa cola vac�a
    cp->cantidad_elementos = 0; //Cantidad de elementos cero
    cp->comparador = f; //Comparador funci�n f
    cp->raiz = NULL; //No hay nodo raiz

    return cp;
}

int cp_insertar(TColaCP cola, TEntrada entrada) {
    int insertado = FALSE;

    if (entrada != NULL) {
        //creo el nodo
        TNodo n = (TNodo) malloc(sizeof(struct nodo));
        n->entrada = entrada;
        n->padre = n->hijo_derecho = n->hijo_izquierdo = NULL;

        if (cola->raiz == NULL) {
            cola->raiz = n;
        } else {
            //inserto donde corresponda en la cola, desde la raíz al nuevo nodo n creado, indicando que es la primer iteración (0)
            insertar_recursivamente(cola, cola->raiz, n);
        }

        //incremento la cantidad de elementos de la estructura
        cola->cantidad_elementos++;

        insertado = TRUE;

    }

    return insertado;
}

void intercambiar(TNodo n, TNodo m) {
    TEntrada temp = n->entrada;
    n->entrada = m->entrada;
    m->entrada = temp;
}

/* Elimina y retorna la entrada con mayor prioridad (menor clave) de la cola. Reacomoda la estructura heap de forma consistente.
Si la cola es vacía, retorna ELE_NULO*/
TEntrada cp_eliminar(TColaCP cola) {
    if (cola == NULL || cola->raiz == NULL)
        return ELE_NULO;

    //auxiliares propias de la eliminación
    TEntrada ent;
    TNodo actual;
    int cant_desc, niveles_completos, nodos_por_niveles_completos, nodos_ocupados, nodos_posibles;

    ent = cola->raiz->entrada;

    //desde la raíz
    actual = cola->raiz;

    //1. Obtengo la cantidad de descendientes de la raíz
    cant_desc = cant_descendientes(actual);

    //2. Obtengo la cantidad de niveles completos
    niveles_completos = (int) floor(log2(cant_desc + 1));

    //3. Calculo la cantidad de nodos ocupan los niveles completos y posibles
    nodos_por_niveles_completos = (int) pow(2, niveles_completos) - 1;
    nodos_posibles = nodos_por_niveles_completos + 1;

    //4. Calculo la cantidad de nodos ocupados del siguiente nivel
    nodos_ocupados = cant_desc - nodos_por_niveles_completos;

    //5. Encuentro al nodo que será la nueva raíz
    while (actual != NULL && cant_desc > 1) {
        if (nodos_ocupados != 0 && (nodos_ocupados <= nodos_posibles / 2))   //si la cantidad de nodos ocupados del siguiente nivel es menor o igual que la mitad de nodos posibles, voy a izquierda
            actual = actual->hijo_izquierdo;
        else                                        //sino, voy a derecha
            actual = actual->hijo_derecho;

        //en cualquier caso:
        //actualizo la cantidad de descendientes según la del nodo actual
        cant_desc = cant_descendientes(actual);

        //como pasé al siguiente nivel, actualizo la cantidad de niveles completos:
        niveles_completos--;

        //y actualizo los demás valores que dependían del mismo de forma acorde
        nodos_por_niveles_completos = (int) pow(2, niveles_completos) - 1;
        nodos_posibles = nodos_por_niveles_completos + 1;
        nodos_ocupados = cant_desc - nodos_por_niveles_completos;
    }

    //6. Actualizo la entrada asociada a la raíz
    cola->raiz->entrada = actual->entrada;
    actual->entrada = NULL;

    cola->cantidad_elementos--;

    //7. Acomodar el heap desde la raíz
    acomodar_por_eliminacion(cola, cola->raiz);

    //TODO: liberar el espacio ocupado por la raíz

    return ent;
}

int cp_cantidad(TColaCP cola) {
    return cola->cantidad_elementos;
}

void insertar_recursivamente(TColaCP cola, TNodo origen, TNodo nuevo) {
    TNodo actual;

    int niveles_completos, nodos_por_niveles_completos, nodos_posibles, nodos_ocupados;
    int descendientes = cant_descendientes(origen);

    //Caso base: el nodo origen no tiene hijos --> inserto a la izquierda
    if (descendientes == 1) {
        origen->hijo_izquierdo = nuevo;
        nuevo->padre = origen;

        //mantengo la estructura de heap
        acomodar_por_insercion(cola, nuevo);

    }
    //Caso base: el nodo origen tiene 1 hijo --> inserto a la derecha
    else if (descendientes == 2) {
        origen->hijo_derecho = nuevo;
        nuevo->padre = origen;

        //mantengo la estructura de heap
        acomodar_por_insercion(cola, nuevo);
    }
    //Caso recursivo: el nodo tiene 2 hijos --> se requiere un análisis más elaborado para determinar la posición de inserción
    else {
        //1. Calculo la cantidad de niveles completos

        /* los niveles completos se corresponden con el mayor h entero que verifica 2**h - 1 <= descendientes del nodo.
           equivalentemente: h = piso(log2(descendientes del nodo + 1))
           calcularlo de la forma anterior evita iterar (aproximación inicial)*/
        niveles_completos = (int) floor(log2(descendientes + 1));

        //2. Calculo la cantidad total de nodos del siguiente nivel (posibles nodos, no existentes)
        nodos_posibles = pow(2, niveles_completos);

        //3. Calculo la cantidad de nodos ocupan los niveles completos
        nodos_por_niveles_completos = nodos_posibles - 1;

        //4. Calculo la cantidad de nodos ocupados del siguiente nivel
        nodos_ocupados = descendientes - nodos_por_niveles_completos;

        //5. Me desplazo al nodo de la izquierda o derecha según corresponda
        if (nodos_ocupados < nodos_posibles / 2)
            actual = origen->hijo_izquierdo;
        else
            actual = origen->hijo_derecho;

        //6. Recursión con el nodo actual
        insertar_recursivamente(cola, actual, nuevo);

    }


}

int cant_descendientes(TNodo nodo) {
    int cantidad = 0;

    if (nodo != NULL && nodo->entrada != NULL) {
        cantidad = cant_descendientes(nodo->hijo_izquierdo) + cant_descendientes(nodo->hijo_derecho) + 1;
    }

    return cantidad;
}

void acomodar_por_insercion(TColaCP cola, TNodo actual) {

    int comparacion = cola->comparador(actual->entrada, actual->padre->entrada);

    //mientras el nodo actual tenga padre (no sea la raíz) y tenga mayor prioridad
    while (actual->padre != NULL && (comparacion = cola->comparador(actual->entrada, actual->padre->entrada)) == 1) {
        //intercambio y paso al nodo padre
        intercambiar(actual, actual->padre);
        actual = actual->padre;
    }

}

void acomodar_por_eliminacion(TColaCP cola, TNodo actual) {
    int hijos = cant_hijos(actual);

    //Caso base: el nodo no tiene hijos: fin
    //Caso base: el nodo tiene 1 hijo: si tiene mayor o igual prioridad que él, lo intercambio. fin
    if (hijos == 1) {
        if (cola->comparador(actual->hijo_izquierdo->entrada, actual->entrada) >= 0) {
            intercambiar(actual, actual->hijo_izquierdo);
        }
    }
    //Caso recursivo: el nodo tiene 2 hijos
    else if (hijos == 2) {
        //si el hijo izquierdo tiene mayor prioridad que el derecho
        if (cola->comparador(actual->hijo_izquierdo->entrada, actual->hijo_derecho->entrada) >= 0) {
            //si el padre tiene menor prioridad
            if (cola->comparador(actual->hijo_izquierdo->entrada, actual->entrada) >= 0) {

                intercambiar(actual, actual->hijo_izquierdo);
                acomodar_por_eliminacion(cola, actual->hijo_izquierdo);

            }
        } else {    //si el hijo derecho es el de mayor prioridad
            //si el padre tiene menor prioridad que él
            if (cola->comparador(actual->hijo_derecho->entrada, actual->entrada) >= 0) {

                intercambiar(actual, actual->hijo_derecho);
                acomodar_por_eliminacion(cola, actual->hijo_derecho);

            }
        }
    }
}

int cant_hijos(TNodo n) {
    int cantidad = 0;

    if (n->hijo_derecho != NULL && n->hijo_derecho->entrada != NULL) {
        cantidad = 2;
    } else if (n->hijo_izquierdo != NULL && n->hijo_izquierdo->entrada != NULL) {
        cantidad = 1;
    }

    return cantidad;
}
