#include "claves_rpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clavesrpc_1(char *host)
{
    CLIENT *clnt;

    struct arg_send_values set_value_1_a1;
    struct arg_send_values modify_value_1_a2;
    struct ret_get_value *result_3;
    int get_value_1_key;
    int delete_key_1_key;
    int exist_1_key;

    int *result_1, *result_2, *result_4, *result_5, *result_6;

    // Crear cliente
    clnt = clnt_create(host, CLAVESRPC, CLAVESRPC, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    // =============== DESTROY ===============
    result_1 = rpc_destroy_1(clnt);
    if (result_1 == NULL) {
        clnt_perror(clnt, "rpc_destroy_1 call failed");
    } else {
        printf("Destroy result: %d\n", *result_1);
    }

    // =============== SET_VALUE ===============
    // Inicializa los datos de prueba
    set_value_1_a1.key = 42;
    set_value_1_a1.value1 = "Hola RPC";
    set_value_1_a1.N_value2 = 2;
    double temp_vals[2] = {3.14, 2.71};
    set_value_1_a1.V_value2.V_value2_len = 2;
    set_value_1_a1.V_value2.V_value2_val = temp_vals;
    set_value_1_a1.value3.x = 10;
    set_value_1_a1.value3.y = 20;

    result_2 = rpc_set_value_1(&set_value_1_a1, clnt);
    if (result_2 == NULL) {
        clnt_perror(clnt, "rpc_set_value_1 call failed");
    } else {
        printf("Set value result: %d\n", *result_2);
    }

    // =============== GET_VALUE ===============
    get_value_1_key = 42;
    result_3 = rpc_get_value_1(&get_value_1_key, clnt);
    if (result_3 == NULL) {
        clnt_perror(clnt, "rpc_get_value_1 call failed");
    } else {
        printf("Get value status: %d\n", result_3->status);
        printf("value1: %s\n", result_3->value1);
        printf("value3: (%d, %d)\n", result_3->value3.x, result_3->value3.y);
    }

    // =============== MODIFY_VALUE ===============
    modify_value_1_a2.key = 42;
    modify_value_1_a2.value1 = "Modificado";
    modify_value_1_a2.N_value2 = 1;
    double new_vals[1] = {6.28};
    modify_value_1_a2.V_value2.V_value2_len = 1;
    modify_value_1_a2.V_value2.V_value2_val = new_vals;
    modify_value_1_a2.value3.x = 99;
    modify_value_1_a2.value3.y = 77;

    result_4 = rpc_modify_value_1(&modify_value_1_a2, clnt);
    if (result_4 == NULL) {
        clnt_perror(clnt, "rpc_modify_value_1 call failed");
    } else {
        printf("Modify value result: %d\n", *result_4);
    }

    // =============== DELETE_KEY ===============
    delete_key_1_key = 42;
    result_5 = rpc_delete_key_1(&delete_key_1_key, clnt);
    if (result_5 == NULL) {
        clnt_perror(clnt, "rpc_delete_key_1 call failed");
    } else {
        printf("Delete key result: %d\n", *result_5);
    }

    // =============== EXIST ===============
    exist_1_key = 42;
    result_6 = rpc_exist_1(&exist_1_key, clnt);
    if (result_6 == NULL) {
        clnt_perror(clnt, "rpc_exist_1 call failed");
    } else {
        printf("Exist result: %d\n", *result_6);
    }

    clnt_destroy(clnt);
}

int main(int argc, char *argv[])
{
    char *host = getenv("IP_TUPLAS");

    if (host == NULL) {
        fprintf(stderr, "Falta la variable de entorno IP_TUPLAS\n");
        exit(1);
    }

    clavesrpc_1(host);
    return 0;
}