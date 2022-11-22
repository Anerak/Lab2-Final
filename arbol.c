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
    n->modificado = 0;
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
        printf("\n\t\t...............Pedidos para el cliente %s %s...............\n", t->dato.Nombre, t->dato.Apellido);
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
        printf("\n\t\t...............Pedidos para el cliente %s %s...............\n", t->dato.Nombre, t->dato.Apellido);
        mostrarLista(t->pedidos);
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
        printf("\n\t\t...............Pedidos para el cliente %s %s...............\n", t->dato.Nombre, t->dato.Apellido);
        mostrarLista(t->pedidos);
    }
}

int esHoja(nodoArbolCliente *t)
{
    return t && !(t->der) && !(t->izq);
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

    if (t)
    {
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

nodoArbolCliente *altaClienteArbol(nodoArbolCliente *t, int id)
{
    stCliente c;

    printf("DNI: ");
    scanf("%d", &c.dni);
    fflush(stdin);

    while (buscarNodoArbolPorDni(t, c.dni))
    {
        printf("DNI ya existe. Ingrese un nuevo valor: \n");
        fflush(stdin);
        scanf("%d", &c.dni);
    }

    c = crearCliente(id, c.dni);

    t = agregarNodoPorDni(t, c);

    return t;
}

nodoArbolCliente *NMD(nodoArbolCliente *t)
{
    nodoArbolCliente *mostRight = NULL;
    if (t)
    {
        if (t->der)
        {
            mostRight = NMD(t->der);
        }
        else
        {
            mostRight = t;
        }
    }

    return mostRight;
}

nodoArbolCliente *NMI(nodoArbolCliente *t)
{
    nodoArbolCliente *mostLeft = NULL;
    if (t)
    {
        if (t->izq)
        {
            mostLeft = NMI(t->izq);
        }
        else
        {
            mostLeft = t;
        }
    }

    return mostLeft;
}

nodoArbolCliente *borrarClienteArbol(nodoArbolCliente *t, int dni)
{
    if (t)
    {
        t = borrarNodoArbol(t, dni);
    }
}

nodoArbolCliente *borrarNodoArbol(nodoArbolCliente *t, int dni)
{
    if (t)
    {
        if (t->dato.dni == dni)
        {
            if (t->izq != NULL)
            {
                nodoArbolCliente *mostRight = NMD(t->izq);
                t->dato = mostRight->dato;
                bajaCliente(&t->dato);
                t->pedidos = mostRight->pedidos;
                t->izq = borrarNodoArbol(t->izq, mostRight->dato.dni);
            }
            else if (t->der != NULL)
            {
                nodoArbolCliente *mostLeft = NMI(t->der);
                t->dato = mostLeft->dato;
                bajaCliente(&t->dato);
                t->pedidos = mostLeft->pedidos;
                t->der = borrarNodoArbol(t->der, mostLeft->dato.dni);
            }
            else
            {
                free(t);
                t = NULL;
            }
        }
        else if (dni > t->dato.dni)
        {
            t->der = borrarNodoArbol(t->der, dni);
        }
        else
        {
            t->izq = borrarNodoArbol(t->izq, dni);
        }
    }

    return t;
}

void listadoClientesArbol(nodoArbolCliente *t)
{
    if (t)
    {
        listadoClientesArbol(t->izq);
        mostrarClienteResumido(t->dato);
        listadoClientesArbol(t->der);
    }
}

void reporteCompletoArbol(nodoArbolCliente *t)
{
    if (t)
    {
        reporteCompletoArbol(t->izq);
        mostrarClienteResumido(t->dato);
        printf("\n\t\t...............Pedidos para el cliente %s %s...............\n", t->dato.Nombre, t->dato.Apellido);
        mostrarLista(t->pedidos);
        reporteCompletoArbol(t->der);
    }
}

void agregarPedido(nodoArbolCliente *arbol, int dni, int idPedido)
{
    nodoArbolCliente *cliente = buscarNodoArbolPorDni(arbol, dni);
    nodoPedido *pedido = NULL;

    if (cliente)
    {
        pedido = crearNodo(generarPedido());
        pedido->dato.idPedido = idPedido + 1;
        pedido->dato.dniCliente = dni;
        pedido->dato.idCliente = cliente->dato.idCliente;
        cliente->pedidos = insertarPedido(cliente->pedidos, pedido);
        cliente->modificado = 1;

        printf("\n\n\t\tEl pedido se adiciono al cliente.\n\n");
    }
}

void guardarNodosModificadosArbol(nodoArbolCliente *t)
{
    if (t)
    {
        guardarNodosModificadosArbol(t->izq);
        if (t->modificado)
        {
            if (guardarCliente(t->dato) == 1)
            {
                t->modificado = 0;
            }
        }
        guardarNodosModificadosArbol(t->der);
    }
}