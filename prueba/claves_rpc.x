/* Incluir el archivo de cabecera claves.h */
%#include "claves.h"

/* Comentar o eliminar la definición de Coord aquí, ya que está en claves.h */
/*
struct Coord {
    double x;
    double y;
    double z;
};
*/

/* Definición de las estructuras para los argumentos y resultados */
struct arg_send_values {
    int key;
    string value1<256>;
    int N_value2;
    double V_value2<32>;
    struct Coord value3;
};

struct ret_get_value {
    int status;
    string value1<256>;
    int N_value2;
    double V_value2<32>;
    struct Coord value3;
};

/* Definición del programa RPC */
program CLAVESRPC {
    version CLAVESVERS {
        int rpc_destroy(void) = 1;
        int rpc_set_value(arg_send_values) = 2;
        ret_get_value rpc_get_value(int) = 3;
        int rpc_modify_value(arg_send_values) = 4;
        int rpc_delete_key(int) = 5;
        int rpc_exist(int) = 6;
    } = 1;
} = 100456709;
