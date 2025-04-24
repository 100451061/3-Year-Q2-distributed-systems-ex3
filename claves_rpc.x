struct Coord {
   int x;
   int y;
};

struct ret_get_value {
   int status;
   string value1<256>;
   int N_value2;
   double V_value2<32>;
   Coord value3;
};

struct arg_send_values {
   int key;
   string value1<256>;
   int N_value2;
   double V_value2<32>;
   Coord value3;
};

program CLAVESRPC {
   version CLAVESRPC {
       int rpc_destroy(void) = 1;
       int rpc_set_value(arg_send_values) = 2;
       ret_get_value rpc_get_value(int) = 3;
       int rpc_modify_value(arg_send_values) = 4;
       int rpc_delete_key(int) = 5;
       int rpc_exist(int) = 6;
   } = 1;
} = 100456709;