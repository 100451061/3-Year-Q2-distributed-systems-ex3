## Para compilar el makefile 
make -f Makefile.claves_rpc

## Para limpiar el makefile
make clean -f Makefile.claves_rpc


## para que rpc genere funciones mas modernas y claras (con el flag -C, importante)
rpcgen -C claves_rpc.x


## por si acaso, para borrar todos los archivos definitivos
rm -f claves_rpc_clnt.c claves_rpc_svc.c claves_rpc_xdr.c claves_rpc.h

## en claves_rpc.h, hay que comentar el #define CLAVESRPC 1