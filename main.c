#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

int solicitar_opcion();
void cargar_ccp(TColaCP *cola);

int main(int argc, char *argv[])
{


    boolean ejecutar;
    int opcion;
    TColaCP cola;

    ejecutar = true;

    //en caso de que se haya ejecutado el programa con más o menos parámetros de los requeridos
    if (argc != 2)
    {
        //muestro el mensaje de error y finalizo
        printf("Ejecución del programa con número inválido de argumentos.\n\n");
        return NUM_ARGS_INV;
    }
    else
    {
        printf("¡Bienvenido a la aplicación de planificación de viajes!");
        while (ejecutar)
        {
            opcion = solicitar_opcion();

            if (opcion == 1)
            {
                cargar_ccp();

                //comportamiento específico de la opción
            }
            else if (opcion == 2)
            {
                cargar_ccp();

                //comportamiento específico de la opción
            }
            else if (opcion == 3)
            {
                cargar_ccp();

                //comportamiento específico de la opción
            }
            else if (opcion == 4)
            {
                liberar_memoria();

                //comportamiento específico de la opción
                ejecutar = false;
            }
            else
            {
                return OPC_INV;
            }
        }
    }

    //si se llegó a este punto en el programa, solo se puede deber a una ejecución exitosa
    return 0;
}

int solicitar_opcion()
{
    int opcion;

    printf("Ingrese el número correspondiente de acuerdo a lo que desee hacer: \n");
    printf("1. Mostrar ascendente. \n");
    printf("2. Mostrar descendente. \n");
    printf("3. Reducir horas manejo. \n");
    printf("4. Salir. \n")

    scanf("%d", opcion);

    return opcion;
}

void cargar_ccp(TColaCP *cola)
{

}
