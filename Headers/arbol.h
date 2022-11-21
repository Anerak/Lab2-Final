#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include "./cliente.h"
#include "./lista.h"

typedef struct _nodoArbolCliente
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

#endif
