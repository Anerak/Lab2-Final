#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/arbol.h"

nodoArbolCliente *inicArbol()
{
    return NULL;
}

nodoArbolCliente *crearNodoArbol(stCliente dato)
{
    nodoArbolCliente *n = (nodoArbolCliente *)malloc(sizeof(nodoArbolCliente));
    n->pedidos = inicLista();
    n->dato = dato;
    n->izq = NULL;
    n->der = NULL;
}

nodoArbolCliente *agregarNodo(nodoArbolCliente *t, stCliente dato)
{
    if (t == NULL)
    {
        t = crearNodoArbol(dato);
    }
    else
    {

        if (t->dato.idCliente < dato.idCliente)
        {
            t->der = agregarNodo(t->der, dato);
        }
        else
        {
            t->izq = agregarNodo(t->izq, dato);
        }
    }

    return t;
}

nodoArbolCliente *agregarNodoPorDni(nodoArbolCliente *t, stCliente dato)
{
    if (t == NULL)
    {
        t = crearNodoArbol(dato);
    }
    else
    {
        if (t->dato.dni < dato.dni)
        {
            t->der = agregarNodoPorDni(t->der, dato);
        }
        else
        {
            t->izq = agregarNodoPorDni(t->izq, dato);
        }
    }

    return t;
}

void preOrden(nodoArbolCliente *t)
{
    if (t)
    {
        mostrarCliente(t->dato);
        printf("\n- - - - - - - - Pedidos para el cliente %s %s - - - - - - - -\n", t->dato.Nombre, t->dato.Apellido);
        mostrarLista(t->pedidos);
        preOrden(t->izq);
        preOrden(t->der);
    }
}

void inOrden(nodoArbolCliente *t)
{
    if (t)
    {
        inOrden(t->izq);
        mostrarCliente(t->dato);
        inOrden(t->der);
    }
}

void postOrden(nodoArbolCliente *t)
{
    if (t)
    {
        postOrden(t->izq);
        postOrden(t->der);
        mostrarCliente(t->dato);
    }
}

nodoArbolCliente *buscarNodoArbol(nodoArbolCliente *t, int id)
{
    nodoArbolCliente *n = NULL;

    if (t->dato.idCliente == id)
    {
        n = t;
    }
    else
    {
        if (id > t->dato.idCliente)
        {
            n = buscarNodoArbol(t->der, id);
        }
        else
        {
            n = buscarNodoArbol(t->izq, id);
        }
    }

    return n;
}

nodoArbolCliente *buscarNodoArbolPorDni(nodoArbolCliente *t, int dni)
{
    nodoArbolCliente *n = NULL;

    if (t->dato.dni == dni)
    {
        n = t;
    }
    else
    {
        if (dni > t->dato.dni)
        {
            n = buscarNodoArbolPorDni(t->der, dni);
        }
        else
        {
            n = buscarNodoArbolPorDni(t->izq, dni);
        }
    }

    return n;
}

nodoArbolCliente *buscarNodoArbolPorNombre(nodoArbolCliente *t, char n[])
{
    nodoArbolCliente *arbol = NULL;

    if (strcmpi(t->dato.Nombre, n) == 0)
    {
        arbol = t;
    }
    else
    {
        arbol = buscarNodoArbolPorNombre(t->der, n);
        if (arbol == NULL)
        {
            arbol = buscarNodoArbolPorNombre(t->izq, n);
        }
    }

    return arbol;
}

void altaClienteArbol(nodoArbolCliente *t)
{
    stCliente c;
    printf("Ingrese DNI: ");
    scanf("%i", &c.dni);
    nodoArbolCliente *busqueda = buscarNodoArbolPorDni(t, c.dni);
    if (busqueda)
    {
        printf("Cliente ya existe!\n");
        return;
    }
}
