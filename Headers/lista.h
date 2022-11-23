#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "pedidos.h"

typedef struct _nodoPedido
{
    struct _nodoPedido *siguiente;
    stPedido dato;
    int modificado;
} nodoPedido;

nodoPedido *inicLista();
nodoPedido *crearNodo(stPedido dato);
nodoPedido *agregarPrincipio(nodoPedido *l, nodoPedido *n);
void mostrarLista(nodoPedido *n);
void mostrarListaAcotada(nodoPedido *l);
nodoPedido *nodoFinal(nodoPedido *l, nodoPedido *n);
nodoPedido *agregarFinal(nodoPedido *l, nodoPedido *n);
nodoPedido *buscarUltimo(nodoPedido *l);
int verificarIDpedido(nodoPedido *l, stPedido dato);
nodoPedido *buscarPedidoID(nodoPedido *lista, int idPedido);
nodoPedido *borrarNodoPedido(nodoPedido *lista, int idPedido);
nodoPedido *insertarPedido(nodoPedido *l, nodoPedido *n);

///////////// ANULAR :

void anularPedido(nodoPedido *pedido);

////////// MODIFICAR:
void modificarNodoPedido(nodoPedido *lista, int idPedido);

/////////LIQUIDAR:
float gastoAnual(nodoPedido *l, int anio);
int comprasAnual(nodoPedido *l, int anio);
void liquidacionAnual(nodoPedido *l, int anio);

float gastoMensual(nodoPedido *l, int mes);
int comprasMensual(nodoPedido *l, int mes);
void liquidacionMensual(nodoPedido *l, int mes);

#endif
