//Basico
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

int isEmpty(TablaHash *t) {
    return t->carga == 0;
}

int buscarElemento(TablaHash *t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return 0;
    }
    
    int indice = funcionHash(t, valor);
    int intentos = 0;

    // Sondeo lineal
    while (intentos < t->tamano) {
        if (t->datos[indice] == valor) {
            return 1;  // Elemento encontrado
        }
        if (t->datos[indice] == -1) {
            return 0;  // Llegamos a una celda vacía
        }
        indice = (indice + 1) % t->tamano;
        intentos++;
    }

    return 0;  // No se encontró el elemento
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
    int intentos = 0;

    // Sondeo lineal para encontrar una posición libre
    while (intentos < t->tamano) {
        if (t->datos[indice] == -1) {
            t->datos[indice] = valor;
            t->carga++;
            return;  // Salimos después de insertar
        } else if (t->datos[indice] == valor) {
            printf("El elemento ya está en la tabla\n");
            return;
        }
        indice = (indice + 1) % t->tamano;
        intentos++;
    }
}

void eliminarElemento(TablaHash *t, int valor) {
    if (t == NULL || t->datos == NULL) {
        return;
    }

    int indice = funcionHash(t, valor);
    int intentos = 0;

    // Sondeo lineal para encontrar el elemento
    while (intentos < t->tamano) {
        if (t->datos[indice] == valor) {
            t->datos[indice] = -1;  // Marcamos como eliminado
            t->carga--;
            printf("Elemento %d eliminado\n", valor);
            return;  // Salimos después de eliminar
        }
        indice = (indice + 1) % t->tamano;
        intentos++;
    }

    printf("El elemento no se encontró\n");  // No se encontró el elemento
}

void imprimirTablaHash(TablaHash *tabla) {
    if (tabla == NULL || tabla->datos == NULL) {
        printf("Tabla inválida\n");
        return;
    }

    // Imprimir los índices
    for (int i = 0; i < tabla->tamano; i++) {
        printf("%-4d", i);  // %-4d alinea a la izquierda con 4 espacios
    }
    printf("\n");

    // Imprimir una línea separadora
    for (int i = 0; i < tabla->tamano; i++) {
        printf("----");
    }
    printf("\n");

    // Imprimir los valores
    for (int i = 0; i < tabla->tamano; i++) {
        if (tabla->datos[i] == -1) {
            printf("-   ");  // Tres espacios después del guion
        } else {
            printf("%-4d", tabla->datos[i]);
        }
    }
    printf("\n\n");
}

int main() {
    TablaHash *tabla = crearTablaHash();
    if (tabla == NULL) {
        return 1;  // Terminar si falla la creación
    }

    insertarElemento(tabla, 5);
    insertarElemento(tabla, 15);
    insertarElemento(tabla, 25);
    insertarElemento(tabla, 3);
    insertarElemento(tabla, 7);

    printf("La tabla hash actual es:\n");
    imprimirTablaHash(tabla);

    eliminarElemento(tabla, 7);
    eliminarElemento(tabla, 15);
    eliminarElemento(tabla, 3);

    printf("Tabla después de eliminar 15:\n");
    imprimirTablaHash(tabla);

    printf("Se enontro el elemento: %d", buscarElemento(tabla, 25));

    eliminarTabla(tabla);
    return 0;
}
