#include ".\Headers\lista.h"
#include ".\Headers\pedidos.h"

nodoPedido *inicLista()
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

        while (seg->siguiente != NULL && resultado ==0)
        {
            if (seg->dato.idPedido == dato.idPedido)
            {
                resultado = 1;
                mostrarUnPedido(seg->dato);
            }
            seg = seg->siguiente;
        }
    }

    return resultado;
}

nodoPedido *insertarPedido(nodoPedido *l, nodoPedido *n)
{
    if (l == NULL)
    {
        l = n;
    }
    else
    {
        if (compararFecha(l->dato.fecha, n->dato.fecha) > 0)
        {
            n->siguiente = l;
            l = n;
        }
        else
        {
            l->siguiente = insertarPedido(l->siguiente, n);
        }
    }

    return l;
}


/////////////////////////// ANULAR

void anularPedido(nodoPedido* pedido) // devuelve  la posicion del pedido o -1 si no encontro el pedido
{
    stPedido A;
    int costoP = 0;

    if (pedido)
    {
            if (pedido->dato.estadoDelPedido == 1)
            {
                pedido->dato.estadoDelPedido =0;
                costoP = pedido->dato.costoPedido;
                pedido->dato.costoPedido = 0;

                cargarTotalGastadoYcompra((costoP * -1), pedido->dato.idCliente, -1); // realiza el descuetento de la compra anulada al totalgastado por el cliente
            }
    }
}

