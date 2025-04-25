#include "claves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 100

// Estructura para almacenar las tuplas
typedef struct Tuple {
    int key;
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    int used;
    struct Tuple* next;  // Puntero para lista enlazada
} Tuple;

// Lista enlazada de tuplas
static Tuple* head = NULL;
static int initialized = 0;

// Inicializar si es necesario
void init_if_needed() {
    if (!initialized) {
        head = NULL;
        initialized = 1;
    }
}

// Buscar una tupla por su clave
Tuple* find_tuple(int key) {
    init_if_needed();
    Tuple* current = head;
    while (current != NULL) {
        if (current->used && current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Implementación de las funciones de la API
int destroy(void) {
    init_if_needed();
    while (head != NULL) {
        Tuple* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    init_if_needed();
    
    // Comprobar si la clave ya existe
    if (find_tuple(key) != NULL) {
        return -1;
    }
    
    // Comprobar si N_value2 está en rango
    if (N_value2 < 1 || N_value2 > 32) {
        return -1;
    }
    
    // Crear nueva tupla
    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return -1;
    }
    
    // Inicializar la nueva tupla
    new_tuple->key = key;
    strncpy(new_tuple->value1, value1, 255);
    new_tuple->value1[255] = '\0';
    new_tuple->N_value2 = N_value2;
    memcpy(new_tuple->V_value2, V_value2, N_value2 * sizeof(double));
    new_tuple->value3 = value3;
    new_tuple->used = 1;
    
    // Insertar al inicio de la lista
    new_tuple->next = head;
    head = new_tuple;
    
    return 0;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3) {
    init_if_needed();
    
    Tuple* tuple = find_tuple(key);
    if (tuple == NULL) {
        return -1;  // Clave no encontrada
    }
    
    // Copiar los valores
    strcpy(value1, tuple->value1);
    *N_value2 = tuple->N_value2;
    
    for (int i = 0; i < tuple->N_value2; i++) {
        V_value2[i] = tuple->V_value2[i];
    }
    
    *value3 = tuple->value3;
    
    return 0;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    init_if_needed();
    
    // Comprobar si N_value2 está en rango
    if (N_value2 < 1 || N_value2 > 32) {
        return -1;
    }
    
    Tuple* tuple = find_tuple(key);
    if (tuple == NULL) {
        return -1;  // Clave no encontrada
    }
    
    // Actualizar los valores
    strncpy(tuple->value1, value1, 255);
    tuple->value1[255] = '\0';  // Asegurar terminación
    
    tuple->N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++) {
        tuple->V_value2[i] = V_value2[i];
    }
    
    tuple->value3 = value3;
    
    return 0;
}

int delete_key(int key) {
    init_if_needed();
    
    Tuple* current = head;
    Tuple* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    
    return -1;  // Clave no encontrada
}

int exist(int key) {
    init_if_needed();
    return (find_tuple(key) != NULL) ? 1 : 0;
}