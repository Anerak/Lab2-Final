#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include ".\pedidos.h"

typedef struct nodoPedido
{
    struct nodoPedido *siguiente;
    stPedido dato;
    int modificado;
} nodoPedido;

nodoPedido *inicLista();
nodoPedido *crearNodo(stPedido dato);
nodoPedido *agregarPrincipio(nodoPedido *l, nodoPedido *n);
void mostrarLista(nodoPedido *n);
nodoPedido * final(nodoPedido *l, nodoPedido *n);
nodoPedido *agregarFinal(nodoPedido *l, nodoPedido *n);
nodoPedido *leerDatos(nodoPedido *l);
nodoPedido *buscarUltimo(nodoPedido *l);
int buscarElemento(nodoPedido *l, stPedido dato);

#endif