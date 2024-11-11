#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 6

typedef struct Nodo {
    int valor;
    struct Nodo* siguiente;
} Nodo;

typedef struct _TablaHash {
    Nodo** datos; // Cambiado a un puntero doble para listas de colisiones
    int tamano, carga;
} TablaHash;

int funcionHash(TablaHash* t, int valor) {
    return valor % t->tamano;
}

TablaHash* crearTablaHash() {
    TablaHash* t = malloc(sizeof(TablaHash));
    if (t == NULL) {
        printf("Error al asignar memoria para la tabla hash\n");
        return NULL;
    }
    t->tamano = TAM_INICIAL;
    t->datos = malloc(sizeof(Nodo*) * t->tamano);
    if (t->datos == NULL) {
        printf("Error al asignar memoria para los datos\n");
        free(t);
        return NULL;
    }

    for (int i = 0; i < TAM_INICIAL; i++) {
        t->datos[i] = NULL;
    }

    t->carga = 0;
    return t;
}

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = malloc(sizeof(Nodo));
    if (nuevo != NULL) {
        nuevo->valor = valor;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

// Inserción con encadenamiento
void insertarElemento(TablaHash* t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    int indice = funcionHash(t, valor);
    Nodo* nuevo = crearNodo(valor);
    if (nuevo == NULL) return;

    // Insertamos al inicio de la lista en el índice hash
    nuevo->siguiente = t->datos[indice];
    t->datos[indice] = nuevo;
    t->carga++;
}

// Búsqueda con encadenamiento
int buscarElemento(TablaHash* t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return 0;
    }

    int indice = funcionHash(t, valor);
    Nodo* actual = t->datos[indice];

    // Recorrer la lista en el índice hash
    while (actual != NULL) {
        if (actual->valor == valor) {
            return 1;  // Elemento encontrado
        }
        actual = actual->siguiente;
    }
    return 0;  // No se encontró el elemento
}

// Eliminación con encadenamiento
void eliminarElemento(TablaHash* t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    int indice = funcionHash(t, valor);
    Nodo* actual = t->datos[indice];
    Nodo* previo = NULL;

    while (actual != NULL) {
        if (actual->valor == valor) {
            if (previo == NULL) {
                t->datos[indice] = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            free(actual);
            t->carga--;
            printf("Elemento %d eliminado\n", valor);
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }

    printf("El elemento no se encontró\n");
}

// Imprimir la tabla hash
void imprimirTablaHash(TablaHash* tabla) {
    if (tabla == NULL || tabla->datos == NULL) {
        printf("Tabla inválida\n");
        return;
    }

    for (int i = 0; i < tabla->tamano; i++) {
        printf("%d: ", i);
        Nodo* actual = tabla->datos[i];
        while (actual != NULL) {
            printf("%d -> ", actual->valor);
            actual = actual->siguiente;
        }
        printf("NULL\n");
    }
}

void eliminarTabla(TablaHash* t) {
    if (t != NULL) {
        for (int i = 0; i < t->tamano; i++) {
            Nodo* actual = t->datos[i];
            while (actual != NULL) {
                Nodo* siguiente = actual->siguiente;
                free(actual);
                actual = siguiente;
            }
        }
        free(t->datos);
        free(t);
    }
}

int main() {
    TablaHash* tabla = crearTablaHash();
    if (tabla == NULL) {
        return 1;  // Terminar si falla la creación
    }

    insertarElemento(tabla, 5);
    insertarElemento(tabla, 11);
    insertarElemento(tabla, 17);
    insertarElemento(tabla, 23);
    insertarElemento(tabla, 29);

    printf("La tabla hash actual es:\n");
    imprimirTablaHash(tabla);


    eliminarTabla(tabla);
    return 0;
}
