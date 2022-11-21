#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include "./cliente.h"
#include "./lista.h"

typedef struct _nodoArbol
{
    stCliente dato;
    struct _nodoArbol *izq;
    struct _nodoArbol *der;
    int modificado;
    nodoPedido *pedidos;
} nodoArbolCliente;

nodoArbolCliente *inicArbol();
nodoArbolCliente *crearNodoArbol(stCliente);
nodoArbolCliente *agregarNodo(nodoArbolCliente *, stCliente);
nodoArbolCliente *agregarNodoPorDni(nodoArbolCliente *, stCliente);
void preOrden(nodoArbolCliente *);
void inOrden(nodoArbolCliente *);
void postOrden(nodoArbolCliente *);
nodoArbolCliente *buscarNodoArbol(nodoArbolCliente *, int);
nodoArbolCliente *buscarNodoArbolPorDni(nodoArbolCliente *, int);
nodoArbolCliente *buscarNodoArbolPorNombre(nodoArbolCliente *t, char n[]);
nodoArbolCliente *NMD(nodoArbolCliente *t);
nodoArbolCliente *NMI(nodoArbolCliente *t);

nodoArbolCliente *altaClienteArbol(nodoArbolCliente *t, int id);

///////////// BUSCAR PEDIDOSS//////////////////////
nodoPedido *buscarIdPedidoConDni(nodoArbolCliente *arbolito, int dni, int nroPedido); // retorno la poscion en el archivo o -1 si no esta
nodoPedido *buscarPedidoSinDni(nodoArbolCliente *t, int idPedido);

void modificarPedidoPorId(nodoArbolCliente *arbolito, int idpedido); // Modificar pedido por ID

#endif
