
#define NUM_ARGS_INV 3
#define OPC_INV 4

typedef void * TClave;
typedef void * TValor;

typedef struct entrada
{
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo
{
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct cola_con_prioridad
{
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;
