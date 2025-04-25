CC = gcc
CFLAGS = -g -I/usr/include/tirpc -fPIC
LDLIBS = -lnsl -lpthread -ldl -ltirpc

# Regla para generar archivos RPC
rpc: claves_rpc.x
	rpcgen -C claves_rpc.x

# Biblioteca compartida
libclaves.so: claves.o
	$(CC) -shared -o libclaves.so claves.o

# Servidor
server: claves_rpc_svc.o server-rpc.o claves_rpc_xdr.o xdr_coord.o claves.o
	$(CC) $(CFLAGS) -o claves_rpc_server $^ $(LDLIBS)

# Cliente
client: claves_rpc_clnt.o proxy-rpc.o claves_rpc_xdr.o xdr_coord.o
	$(CC) $(CFLAGS) -o claves_rpc_client $^ $(LDLIBS)

# Regla para compilar archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $<

all: rpc libclaves.so server client

clean:
	rm -f *.o *.so claves_rpc_client claves_rpc_server
	rm -f claves_rpc_clnt.c claves_rpc_svc.c claves_rpc_xdr.c claves_rpc.h
