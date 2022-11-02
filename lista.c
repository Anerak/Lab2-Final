#include ".\Headers\lista.h"
#include ".\Headers\pedidos.h"

struct nodoPedido *inicLista()
{
    return NULL;
}

nodoPedido *crearNodo(stPedido dato)
{
    nodoPedido *n = (nodoPedido *)malloc(sizeof(nodoPedido));
    n->dato = dato;
    n->siguiente = NULL;

    return n;
}

nodoPedido *agregarPrincipio(nodoPedido *l, nodoPedido *n)
{
    n->siguiente = l;
    return n;
    // if (l == NULL)
    // {
    //     l = n;
    // }
    // else
    // {
    //     n->siguiente = l;
    //     l = n;
    // }

    // return l;
}

nodoPedido *agregarFinal(nodoPedido *l, nodoPedido *n)
{
    if (l == NULL)
    {
        l = n;
    }
    else
    {
        nodoPedido *seg = l;
        while (seg && seg->siguiente)
        {
            seg = seg->siguiente;
        }

        seg->siguiente = n;
    }

    return l;
}

nodoPedido * final(nodoPedido *l, nodoPedido *n)
{
    if (l == NULL)
    {
        l = n;
    }

    if (l->siguiente != NULL)
    {
        l->siguiente = final(l->siguiente, n);
    }
    else
    {
        l->siguiente = n;
    }

    return l;
}

void mostrarLista(nodoPedido *l)
{
    nodoPedido *seg = l;

    while (seg != NULL)
    {
        mostrarUnPedido(seg->dato);
        seg = seg->siguiente;
    }
}

nodoPedido *leerDatos(nodoPedido *l)
{
    FILE *a = fopen("./datos.dat", "r+b");
    stPedido p;
    if (a == NULL)
        return l;

    while (fread(&p, sizeof(stPedido), 1, a) > 0)
    {
        l = agregarFinal(l, crearNodo(p));
    }

    fclose(a);
    return l;
}

nodoPedido *buscarUltimo(nodoPedido *l)
{
    nodoPedido *seg = l;
    while (seg->siguiente != NULL)
    {
        seg = seg->siguiente;
    }

    return seg;
}

int buscarElemento(nodoPedido *l, stPedido dato)
{
    int resultado = 0;
    if (l != NULL)
    {
        nodoPedido *seg = l;

        while (seg->siguiente != NULL)
        {
            if (seg->dato.idPedido == dato.idPedido)
            {
                resultado = 1;
                mostrarUnPedido(seg->dato);
                break;
            }
            seg = seg->siguiente;
        }
    }

    return resultado;
}