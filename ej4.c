#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 6

typedef struct _TablaHash {
    int *datos;
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

    if (t->datos == NULL) {
        printf("Error al asignar memoria para los datos\n");
        free(t);
        return NULL;
    }

    for (int i = 0; i < TAM_INICIAL; i++) {
        t->datos[i] = -1;
    }

    t->carga = 0;
    return t;
}

void eliminarTabla(TablaHash *t) {
    if (t != NULL) {
        free(t->datos);
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

    // Buscar el siguiente índice libre usando linear probing
    while (t->datos[indice] != -1) {
        indice = (indice + 1) % t->tamano;
    }

    t->datos[indice] = valor;
    t->carga++;
}

void eliminarElemento(TablaHash *t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    int indice = funcionHash(t, valor);

    // Buscar el valor usando linear probing
    while (t->datos[indice] != -1) {
        if (t->datos[indice] == valor) {
            t->datos[indice] = -1; // Eliminar el elemento
            t->carga--;
            printf("Elemento %d eliminado\n", valor);
            return;
        }
        indice = (indice + 1) % t->tamano;
    }

    printf("El elemento %d no se encontró\n", valor);
}

void imprimirTablaHash(TablaHash *tabla) {
    if (tabla == NULL || tabla->datos == NULL) {
        printf("Tabla inválida\n");
        return;
    }

    printf("Indice\tDato\n");
    for (int i = 0; i < tabla->tamano; i++) {
        printf("%d\t%d\n", i, tabla->datos[i]);
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

    eliminarElemento(tabla, 11);
    
    imprimirTablaHash(tabla);
    eliminarTabla(tabla);
    return 0;
}
