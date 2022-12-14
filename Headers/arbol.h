#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include "./cliente.h"
#include "./lista.h"

typedef struct _nodoArbolCliente
{
    stCliente dato;
    struct _nodoArbolCliente *izq;
    struct _nodoArbolCliente *der;
    int modificado;
    nodoPedido *pedidos;
} nodoArbolCliente;

nodoArbolCliente *inicArbol();
nodoArbolCliente *crearNodoArbol(stCliente);
nodoArbolCliente *agregarNodo(nodoArbolCliente *, stCliente);
nodoArbolCliente *agregarNodoPorDni(nodoArbolCliente *, stCliente);
void preOrden(nodoArbolCliente *);
void inOrden(nodoArbolCliente *);
void mostrarClientesAcotado(nodoArbolCliente *t);
void postOrden(nodoArbolCliente *);
nodoArbolCliente *buscarNodoArbol(nodoArbolCliente *, int);
nodoArbolCliente *buscarNodoArbolPorDni(nodoArbolCliente *, int);
nodoArbolCliente *buscarNodoArbolPorNombre(nodoArbolCliente *t, char n[]);
nodoArbolCliente *NMD(nodoArbolCliente *t);
nodoArbolCliente *NMI(nodoArbolCliente *t);
nodoArbolCliente *borrarNodoArbol(nodoArbolCliente *t, int dni);
nodoArbolCliente *altaClienteArbol(nodoArbolCliente *t, int id);

void listadoClientesArbol(nodoArbolCliente *t);
void reporteCompletoArbol(nodoArbolCliente *t);
void guardarNodosModificadosArbol(nodoArbolCliente *t);

void agregarPedido(nodoArbolCliente *arbol, int dni, int idPedido);
void modificarPedido(nodoArbolCliente *arbolito);
void darBajaPedido (nodoArbolCliente *arbolito);
void verificarModificaciones(nodoArbolCliente *t);

#endif
