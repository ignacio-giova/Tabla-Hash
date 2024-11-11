#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 6

typedef struct _TablaHash {
    int *datos;
    int *indiceEnlace;
    int tamano, carga;
} TablaHash;

int funcionHash(TablaHash *t, int valor) {
    return valor % t->tamano;
}

TablaHash *crearTablaHash() {
    TablaHash *t = malloc(sizeof(TablaHash));
    if (t == NULL) {
        printf("Error al asignar memoria para la tabla hash\n");
        return NULL;
    }
    t->tamano = TAM_INICIAL;
    t->datos = malloc(sizeof(int) * t->tamano);
    t->indiceEnlace = malloc(sizeof(int) * t->tamano);

    if (t->datos == NULL || t->indiceEnlace == NULL) {
        printf("Error al asignar memoria para los datos\n");
        free(t);
        return NULL;
    }

    for (int i = 0; i < TAM_INICIAL; i++) {
        t->datos[i] = -1;
        t->indiceEnlace[i] = -1;
    }

    t->carga = 0;
    return t;
}

void eliminarTabla(TablaHash *t) {
    if (t != NULL) {
        free(t->datos);
        free(t->indiceEnlace);
        free(t);
    }
}

void insertarElemento(TablaHash *t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    if (t->carga >= t->tamano) {
        printf("No se pudo agregar. Tabla llena\n");
        return;
    }

    int indice = funcionHash(t, valor);

    // Si la posición está libre, insertamos el valor directamente
    if (t->datos[indice] == -1) {
        t->datos[indice] = valor;
        t->carga++;
    } else {
        // Encontrar el último nodo en la lista de colisiones
        int actual = indice;
        while (t->indiceEnlace[actual] != -1) {
            actual = t->indiceEnlace[actual];
        }

        // Buscar una posición libre para enlazar
        int nuevaPos = (indice + 1) % t->tamano;
        while (t->datos[nuevaPos] != -1) {
            nuevaPos = (nuevaPos + 1) % t->tamano;
        }

        t->datos[nuevaPos] = valor;
        t->indiceEnlace[actual] = nuevaPos;
        t->indiceEnlace[nuevaPos] = -1;
        t->carga++;
    }
}

void eliminarElemento(TablaHash *t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    int indice = funcionHash(t, valor);
    int anterior = -1;
    int actual = indice;

    // Buscar el valor en la lista de colisiones
    while (actual != -1 && t->datos[actual] != valor) {
        anterior = actual;
        actual = t->indiceEnlace[actual];
    }

    if (actual == -1) {
        printf("El elemento %d no se encontró\n", valor);
        return;
    }

    // Si el valor está en la posición inicial y no tiene enlace
    if (anterior == -1) {
        if (t->indiceEnlace[actual] == -1) {
            t->datos[actual] = -1; // Eliminar directamente
        } else {
            // Reemplazar con el siguiente de la lista
            int siguiente = t->indiceEnlace[actual];
            t->datos[actual] = t->datos[siguiente];
            t->indiceEnlace[actual] = t->indiceEnlace[siguiente];
            t->datos[siguiente] = -1;
            t->indiceEnlace[siguiente] = -1;
        }
    } else {
        // Actualizar el enlace del anterior para saltar el nodo actual
        t->indiceEnlace[anterior] = t->indiceEnlace[actual];
        t->datos[actual] = -1;
        t->indiceEnlace[actual] = -1;
    }

    t->carga--;
    printf("Elemento %d eliminado\n", valor);
}

void imprimirTablaHash(TablaHash *tabla) {
    if (tabla == NULL || tabla->datos == NULL) {
        printf("Tabla inválida\n");
        return;
    }

    printf("Indice\tDato\tEnlace\n");
    for (int i = 0; i < tabla->tamano; i++) {
        printf("%d\t%d\t%d\n", i, tabla->datos[i], tabla->indiceEnlace[i]);
    }
    printf("\n");
}

int main() {
    TablaHash *tabla = crearTablaHash();
    if (tabla == NULL) {
        return 1;  // Terminar si falla la creación
    }

    insertarElemento(tabla, 5);
    insertarElemento(tabla, 11);
    insertarElemento(tabla, 17);
    insertarElemento(tabla, 0);
    insertarElemento(tabla, 6);

    eliminarElemento(tabla, 2);
    
    imprimirTablaHash(tabla);
    eliminarTabla(tabla);
    return 0;
}
