
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "colacp.h"

#define NUM_ARGS_INV 3
#define OPC_INV 4


const int str_max = 255;
const int long_max_nombre = 100;

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

int solicitar_opcion();
int comparadorMin(TEntrada e1, TEntrada e2);
int comparadorMax(TEntrada e1, TEntrada e2);
void liberar_entrada(TEntrada entrada);
TEntrada cargar_ccp_distancia(TColaCP cola, char *nombre_archivo);
float calcular_clave(TCiudad destino, TCiudad referencia);
float mostrar_entradas(TColaCP cola);

int main(int argc, char *argv[])
{

    int ejecutar;
    int opcion;
    TColaCP cola = crear_cola_cp(comparadorMin);

    ejecutar = TRUE;

    //en caso de que se haya ejecutado el programa con m�s o menos par�metros de los requeridos
    if (argc != 1) {            //TODO: CAMBIAR POR 2 PARA VERIFICAR CANTIDAD CORRECTA DE PARÁMETROS AL EJECUTAR POR CONSOLA
        //muestro el mensaje de error y finalizo
        printf("Ejecucion del programa con numero invalido de argumentos.");
        exit(NUM_ARGS_INV);
    } else {
        printf("Bienvenido a la aplicacion de planificacion de viajes!");
        while (ejecutar) {
            opcion = solicitar_opcion();

            if (opcion == 1) {

                cargar_ccp_distancia(cola, "viajes.txt");           //TODO: CAMBIAR POR argv[1] al entregar


                printf("\nMostrar ascendente: \n");
                mostrar_entradas(cola);
                printf("\n");

                //comportamiento espec�fico de la opci�n
            } else if (opcion == 2) {
                //cambio el comparador de la cola para que se corresponda con MaxHeap
                cola->comparador = comparadorMax;

                cargar_ccp_distancia(cola, "viajes.txt");           //TODO: CAMBIAR POR argv[1] al entregar


                printf("\nMostrar descendente: \n");
                mostrar_entradas(cola);
                printf("\n");

                //hago que se comporte de nuevo como MinHeap
                cola->comparador = comparadorMin;

                //comportamiento espec�fico de la opci�n
            } else if (opcion == 3) {

                printf("\nReducir horas manejo: \n");
                printf("Total recorrido: %f\n", mostrar_entradas(cola));
                printf("\n");

                //comportamiento espec�fico de la opci�n
            } else if (opcion == 4) {

                //comportamiento espec�fico de la opci�n
                ejecutar = FALSE;

                cp_destruir(cola, liberar_entrada);
            } else {
                exit(OPC_INV);
            }
        }
    }

    //si se lleg� a este punto en el programa, solo se puede deber a una ejecuci�n exitosa
    return 0;
}

int solicitar_opcion()
{
    int opcion;

    printf("Ingrese el numero correspondiente de acuerdo a lo que desee hacer: \n");
    printf("1. Mostrar ascendente. \n");
    printf("2. Mostrar descendente. \n");
    printf("3. Reducir horas manejo. \n");
    printf("4. Salir. \n");

    scanf("%d", &opcion);

    return opcion;
}

TEntrada cargar_ccp_distancia(TColaCP cola, char *nombre_archivo) {
    FILE *file;
    char * aux;
    TCiudad ciudad_usuario;
    TEntrada entrada_usuario;

    TCiudad ciudad_aux;
    TEntrada entrada_aux;

    float * clave;

    file = fopen(nombre_archivo, "r");
    aux = (char*) malloc(str_max * sizeof(char *));
    ciudad_usuario = (TCiudad) malloc(sizeof(struct ciudad));       //nueva ciudad para el usuario

    //primero guardo la posicion del usuario (a retornar)
    ciudad_usuario -> nombre = "usuario";

    //obtengo la primer línea del archivo --> se corresponde con su ubicación y asigno su x e y
    fgets(aux, str_max, file);

    ciudad_usuario->pos_x = atof(strtok(aux, ";"));
    ciudad_usuario->pos_y = atof(strtok(NULL, ";"));

    //creo la entrada a retornar que encapsula su ubicación
    entrada_usuario = (TEntrada) malloc(sizeof(struct entrada));

    entrada_usuario->valor = ciudad_usuario;
    entrada_usuario->clave = 0;

    //mientras haya líneas por leer, inserto las ciudades en la cola
    while (fgets(aux, str_max, file) != NULL) {
        //creo una nueva ciudad
        ciudad_aux = (TCiudad) malloc(sizeof(struct ciudad));

        //inicializo
        ciudad_aux->nombre = malloc(long_max_nombre * (sizeof(char *)));

        strcpy(ciudad_aux->nombre, strtok(aux, ";"));
        ciudad_aux->pos_x = atof(strtok(NULL, ";"));
        ciudad_aux->pos_y = atof(strtok(NULL, ";"));

        //creo la entrada que la va a contener
        entrada_aux = (TEntrada) malloc(sizeof(struct entrada));
        entrada_aux->valor = ciudad_aux;

        clave = (float *) malloc(sizeof(float *));
        *clave = calcular_clave(ciudad_aux, ciudad_usuario);

        //calculo la clave de esta ciudad respecto a la del usuario (distancia)
        entrada_aux->clave = clave;

        //inserto la entrada en la cola
        cp_insertar(cola, entrada_aux);
    }

    fclose(file);

    return entrada_usuario;
}

/** Retorna la distancia de la ciudad destino a la ciudad de referencia */
float calcular_clave(TCiudad destino, TCiudad referencia) {
    return fabs(destino->pos_x - referencia->pos_x) + fabs(destino->pos_y - referencia->pos_y);
}

void liberar_entrada(TEntrada entrada) {

    if (entrada != NULL) {
        TCiudad valor_entrada = entrada->valor;     //ciudad de la entrada
        free(valor_entrada->nombre);        //nombre
        free(entrada->valor);               //ciudad de la entrada
        free(entrada->clave);               //prioridad
        free(entrada);
    }

}

int comparadorMin(TEntrada e1, TEntrada e2) {
    int comparacion = 0;
    float *c1 = (float *) (e1->clave);
    float *c2 = (float *) (e2->clave);

    if (*c1 < *c2) {
        comparacion = 1;
    } else if (*c1 > *c2) {
        comparacion = -1;
    }

    return comparacion;

}

int comparadorMax(TEntrada e1, TEntrada e2) {
    return -1 * comparadorMin(e1, e2);
}

TEntrada obtener_entrada(int prio, char * valor) {
    TEntrada ent = malloc(sizeof(struct entrada));

    ent->clave = &prio;
    ent->valor = valor;

    return ent;
}

int* asignar_clave() {
    int * key = malloc(sizeof(int *));
    *key = rand() % 11;

    return key;
}

float mostrar_entradas(TColaCP cola) {
    int i;
    float recorrido;
    i = 1;
    recorrido = 0;

    while (cola->cantidad_elementos > 0) {
        TEntrada e = cp_eliminar(cola);
        printf("%d. %s.\n", i, ((TCiudad) e->valor)->nombre);
        i++;
        recorrido += *((float *) e->clave);
    }

    return recorrido;
}

