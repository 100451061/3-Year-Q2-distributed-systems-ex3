#include "claves.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 100

// Estructura para almacenar las tuplas
typedef struct {
    int key;
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    int used;  // 1 si está en uso, 0 si está libre
} Tuple;

// Almacén de tuplas
static Tuple tuples[MAX_KEYS];
static int initialized = 0;

// Inicializar el almacén si no se ha hecho ya
void init_if_needed() {
    if (!initialized) {
        for (int i = 0; i < MAX_KEYS; i++) {
            tuples[i].used = 0;
        }
        initialized = 1;
    }
}

// Buscar una tupla por su clave
int find_tuple(int key) {
    init_if_needed();
    for (int i = 0; i < MAX_KEYS; i++) {
        if (tuples[i].used && tuples[i].key == key) {
            return i;
        }
    }
    return -1;  // No encontrado
}

// Encontrar un espacio libre
int find_free_slot() {
    init_if_needed();
    for (int i = 0; i < MAX_KEYS; i++) {
        if (!tuples[i].used) {
            return i;
        }
    }
    return -1;  // No hay espacio libre
}

// Implementación de las funciones de la API

int destroy(void) {
    init_if_needed();
    for (int i = 0; i < MAX_KEYS; i++) {
        tuples[i].used = 0;
    }
    return 0;
}

int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    init_if_needed();
    
    // Comprobar si la clave ya existe
    if (find_tuple(key) != -1) {
        return -1;
    }
    
    // Comprobar si N_value2 está en rango
    if (N_value2 < 1 || N_value2 > 32) {
        return -1;
    }
    
    // Buscar un espacio libre
    int slot = find_free_slot();
    if (slot == -1) {
        return -1;  // No hay espacio
    }
    
    // Guardar los valores
    tuples[slot].key = key;
    strncpy(tuples[slot].value1, value1, 255);
    tuples[slot].value1[255] = '\0';  // Asegurar terminación
    
    tuples[slot].N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++) {
        tuples[slot].V_value2[i] = V_value2[i];
    }
    
    tuples[slot].value3 = value3;
    tuples[slot].used = 1;
    
    return 0;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3) {
    init_if_needed();
    
    int idx = find_tuple(key);
    if (idx == -1) {
        return -1;  // Clave no encontrada
    }
    
    // Copiar los valores
    strcpy(value1, tuples[idx].value1);
    *N_value2 = tuples[idx].N_value2;
    
    for (int i = 0; i < tuples[idx].N_value2; i++) {
        V_value2[i] = tuples[idx].V_value2[i];
    }
    
    *value3 = tuples[idx].value3;
    
    return 0;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    init_if_needed();
    
    // Comprobar si N_value2 está en rango
    if (N_value2 < 1 || N_value2 > 32) {
        return -1;
    }
    
    int idx = find_tuple(key);
    if (idx == -1) {
        return -1;  // Clave no encontrada
    }
    
    // Actualizar los valores
    strncpy(tuples[idx].value1, value1, 255);
    tuples[idx].value1[255] = '\0';  // Asegurar terminación
    
    tuples[idx].N_value2 = N_value2;
    for (int i = 0; i < N_value2; i++) {
        tuples[idx].V_value2[i] = V_value2[i];
    }
    
    tuples[idx].value3 = value3;
    
    return 0;
}

int delete_key(int key) {
    init_if_needed();
    
    int idx = find_tuple(key);
    if (idx == -1) {
        return -1;  // Clave no encontrada
    }
    
    tuples[idx].used = 0;  // Marcar como no usado
    
    return 0;
}

int exist(int key) {
    init_if_needed();
    
    int idx = find_tuple(key);
    if (idx == -1) {
        return 0;  // No existe
    }
    
    return 1;  // Existe
}
