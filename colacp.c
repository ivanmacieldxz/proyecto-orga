
#include "headers.h"
#include <stdlib.h>
#include <math.h>

void insertar_recursivamente(TNodo origen, TNodo nuevo);

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
            insertar_recursivamente(cola->raiz, n);
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
    while (actual != NULL && cant_descendientes(actual) > 0) {
        if (nodos_ocupados <= nodos_posibles / 2)
            actual = actual->hijo_izquierdo;
        else
            actual = actual->hijo_derecho;
    }

    //6. Actualizo la entrada asociada a la raíz
    cola->raiz ->entrada = actual->entrada;
    actual->entrada = NULL;

    //7. Acomodo el heap
    
    
    cola->cantidad_elementos--;

    //TODO: liberar el espacio ocupado por la raíz

    return ent;
}

int cp_cantidad(TColaCP cola) {
    return cola->cantidad_elementos;
}

void insertar_recursivamente(TNodo origen, TNodo nuevo) {
    TNodo actual;

    int niveles_completos, nodos_por_niveles_completos, nodos_posibles, nodos_ocupados;
    int descendientes = cant_descendientes(origen);

    //Caso base: el nodo origen no tiene hijos --> inserto a la izquierda
    if (descendientes == 0) {
        origen->hijo_izquierdo = nuevo;
        origen->hijo_izquierdo->padre = origen;
        //TODO: acomodar como corresponda
    } 
    //Caso base: el nodo origen tiene 1 hijo --> inserto a la derecha
    else if (descendientes == 1) {
        origen->hijo_derecho = nuevo;
        origen->hijo_derecho->padre = origen;
        //TODO: acomodar como corresponda
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
        insertar_recursivamente(actual, nuevo);

    }


}

int cant_descendientes(TNodo nodo) {
    int cantidad = 0;
    
    if (nodo != NULL) {
        cantidad = cant_descendientes(nodo->hijo_izquierdo) + cant_descendientes(nodo->hijo_derecho) + 1;
    }
    
    return cantidad;
}