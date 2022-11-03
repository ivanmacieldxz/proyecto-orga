
#define FALSE 0
#define TRUE 1
#define CCP_NO_INI 2  //intento de acceso invalido sobre cola CP sin inicializar
#define POS_NULA NULL
#define ELE_NULO NULL


typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct cola_con_prioridad {
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;

TColaCP crear_cola_cp(int (*f) (TEntrada, TEntrada));
TEntrada cp_eliminar(TColaCP cola);
int cp_cantidad(TColaCP cola);
void cp_destruir(TColaCP cola, void (*fEliminar) (TEntrada));
int cp_insertar(TColaCP cola, TEntrada entr);

