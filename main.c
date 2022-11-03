#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

const int str_max = 255;

int solicitar_opcion();
void cargar_ccp(TColaCP *cola, char * nombre_archivo);
void liberar_memoria();
int comparadorMin(TEntrada e1, TEntrada e2);
int comparadorMax(TEntrada e1, TEntrada e2);
TEntrada obtener_entrada(int prio, char * valor);
int* asignar_clave();

int main(int argc, char *argv[])
{

    /*  CÓDIGO DEL PROGRAMA PRINCIPAL
    int ejecutar;
    int opcion;
    TColaCP cola;

    ejecutar = TRUE;

    //en caso de que se haya ejecutado el programa con m�s o menos par�metros de los requeridos
    if (argc != 2)
    {
        //muestro el mensaje de error y finalizo
        printf("Ejecuci�n del programa con n�mero inv�lido de argumentos.\n\n");
        return NUM_ARGS_INV;
    }
    else
    {
        printf("�Bienvenido a la aplicaci�n de planificaci�n de viajes!");
        while (ejecutar)
        {
            opcion = solicitar_opcion();

            if (opcion == 1)
            {
                cargar_ccp(NULL, argv[1]);

                //comportamiento espec�fico de la opci�n
            }
            else if (opcion == 2)
            {
                cargar_ccp(NULL, argv[1]);

                //comportamiento espec�fico de la opci�n
            }
            else if (opcion == 3)
            {
                cargar_ccp(NULL, argv[1]);

                //comportamiento espec�fico de la opci�n
            }
            else if (opcion == 4)
            {
                liberar_memoria();

                //comportamiento espec�fico de la opci�n
                ejecutar = FALSE;
            }
            else
            {
                return OPC_INV;
            }
        }
    }

    */

    TColaCP cola = crear_cola_cp(comparadorMin);

    int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
    c1 = 1;
    c2 = 3;
    c3 = 2;
    c4 = 5;
    c5 = 7;
    c6 = 6;
    c7 = 4;
    c8 = 7;
    c9 = 16;
    c10 = 16;

    TEntrada ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c10;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c4;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c7;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c5;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c2;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c6;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c1;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c8;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c9;

    cp_insertar(cola, ent);

    ent = (TEntrada) (malloc(sizeof(struct entrada)));

    ent->clave = &c3;

    cp_insertar(cola, ent);


    while (cola->cantidad_elementos > 0)
    {
        TEntrada e = cp_eliminar(cola);
        printf("\nPrio: %d", *((int *) e->clave));
    }

    //si se lleg� a este punto en el programa, solo se puede deber a una ejecuci�n exitosa
    return 0;
}

int solicitar_opcion()
{
    int opcion;

    printf("Ingrese el n�mero correspondiente de acuerdo a lo que desee hacer: \n");
    printf("1. Mostrar ascendente. \n");
    printf("2. Mostrar descendente. \n");
    printf("3. Reducir horas manejo. \n");
    printf("4. Salir. \n");

    scanf("%d", &opcion);

    return opcion;
}

void cargar_ccp(TColaCP *cola, char *nombre_archivo)
{
    FILE *file = fopen(nombre_archivo, "r");
    char * nombre_ciudad;
    int x, y;
    TCiudad ciudad_usuario;

    //primero guardo la posici�n del usuario
    ciudad_usuario -> nombre = "usuario";
    fscanf(file, "%f;", &(ciudad_usuario -> pos_x));     //posx
    fscanf(file, "%f", &(ciudad_usuario -> pos_y));    //poxy

    printf("Datos del usuario: \n%s, %f, %f", ciudad_usuario -> nombre,
           ciudad_usuario -> pos_x, ciudad_usuario -> pos_y);

    fclose(file);

}

void liberar_memoria()
{

}

int comparadorMin(TEntrada e1, TEntrada e2) {
    int comparacion = 0;
    int *c1 = (int *) (e1->clave);
    int *c2 = (int *) (e2->clave);

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
