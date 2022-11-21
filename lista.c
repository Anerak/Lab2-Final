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

nodoPedido * nodoFinal(nodoPedido *l, nodoPedido *n)
{
    if (l == NULL)
    {
        l = n;
    }

    if (l->siguiente != NULL)
    {
        l->siguiente = nodoFinal(l->siguiente, n);
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

nodoPedido *buscarUltimo(nodoPedido *l)
{
    nodoPedido *seg = l;
    while (seg->siguiente != NULL)
    {
        seg = seg->siguiente;
    }

    return seg;
}

int verificarIDpedido (nodoPedido *l, stPedido dato)
{
    int resultado = 0;
    if (l != NULL)
    {
        nodoPedido *seg = l;

        while (seg && resultado ==0)
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

nodoPedido* buscarPedidoID (nodoPedido *lista, int idPedido)
{
    nodoPedido*buscado = NULL;

    if (lista)
    {
        nodoPedido *seg = lista;

        while (seg && buscado==NULL)
        {
            if (seg->dato.idPedido == idPedido)
            {
                buscado=seg;
            }
            seg = seg->siguiente;
        }
    }

    return buscado;
}

nodoPedido * borrarNodoPedido (nodoPedido *lista, int idPedido)
{
   nodoPedido * aBorrar = NULL;

    if (lista)
    {
        if (lista->dato.idPedido == idPedido)
        {
            aBorrar = lista;
            lista = lista->siguiente;
            free(aBorrar);
        }
        else
        {
            lista->siguiente = borrarNodoPedido(lista->siguiente, idPedido);
        }
    }

    return lista;

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

    if (pedido)
    {
            if (pedido->dato.estadoDelPedido == 1)
            {
                pedido->dato.estadoDelPedido =0;
                pedido->dato.costoPedido = 0;
                pedido->modificado=1;
            }
    }
}


////////////////////// MODIFICAR

void modificarNodoPedido (nodoPedido * lista, int idPedido)
{
    nodoPedido * modificado = buscarPedidoID(lista,idPedido);

    if(modificado)
    {
         if (modificado->dato.estadoDelPedido == 1)
            {
                modificado->dato=modificarUnpedido(modificado->dato); // retorna el pedido leido, ya modificado por la funcion
                modificado->modificado= 1;
                printf("\n\n\t\tEl pedido fue modificado\n\n");
            }
            else
            {

                printf("\n\n\t\t El pedido se encuentra en estado anulado\n");
            }
    }


}
