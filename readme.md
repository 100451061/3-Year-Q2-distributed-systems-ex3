## Para compilar el makefile 
make -f Makefile.claves_rpc

## Para limpiar el makefile
make clean -f Makefile.claves_rpc


## para que rpc genere funciones mas modernas y claras (con el flag -C, importante)
rpcgen -N -M claves_rpc.x


## por si acaso, para borrar todos los archivos definitivos
rm -f claves_rpc_clnt.c claves_rpc_svc.c claves_rpc_xdr.c claves_rpc.h

## en claves_rpc.h, hay que comentar el #define CLAVESRPC 1



## Para el servidor Primero, asegúrate de que rpcbind está instalado y ejecutándose:
sudo apt-get update
sudo apt-get install rpcbind

sudo rpcbind

sudo service rpcbind start

## Pasos para Ejecutar el Proyecto RPC
make clean -f Makefile.claves_rpc
make -f Makefile.claves_rpc
./claves_rpc_server
## en otra terminal
### primeor verifoco que el servicio este registrado
rpcinfo -p | grep 100456709

export IP_TUPLAS=localhost
./claves_rpc_client