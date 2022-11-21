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
        printf("\n- - - - - - - - Pedidos para el cliente %s %s - - - - - - - -\n", t->dato.Nombre, t->dato.Apellido);
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
        printf("\n- - - - - - - - Pedidos para el cliente %s %s - - - - - - - -\n", t->dato.Nombre, t->dato.Apellido);
        mostrarLista(t->pedidos);
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
    else
    {
    }
}

int altaDeCliente2(stCliente clientenuevo) //
{
    stDomicilio domicilio;
    int flag = -1, id = 0;
    long int DniAux = 0;

    char validarNum[dim];
    char validarString[dim];

    FILE *archi = fopen(ArchivoClientes, "ab");

    if (archi != NULL)
    {
        printf("\n\n\t\tIngrese el DNI:\n\t\t");
        fflush(stdin);
        scanf("%li", &DniAux);

        flag = validacionDeAlta(DniAux);

        if (flag == 0)
        {
            clientenuevo.dni = DniAux;

            id = ultimoIDCliente();
            clientenuevo.idCliente = id + 1;
            printf("\n\n\t\tID Cliente: 0000%i \n\n", clientenuevo.idCliente);

            do
            {
                printf("\n\n\t\tIngrese el nombre  del cliente:\n\t\t");
                fflush(stdin);
                gets(validarString);
            } while ((validarPalabra(validarString)) != 0);
            strcpy(clientenuevo.Nombre, validarString);

            do
            {
                printf("\n\n\t\tIngrese el apellido del cliente:\n\t\t");
                fflush(stdin);
                gets(validarString);
            } while ((validarPalabra(validarString)) != 0);
            strcpy(clientenuevo.Apellido, validarString);

            domicilio = cargarDomicilio(domicilio);
            clientenuevo.domicilio = domicilio;

            do
            {
                printf("\n\n\t\tIngrese el numero de telefono del cliente:\n\t\t");
                fflush(stdin);
                scanf("%s", validarNum);
            } while ((validarNumero(validarNum)) != 0);
            clientenuevo.telefono = (atoi(validarNum));

            do
            {
                printf("\n\n\t\tIngrese el mail del cliente:\n\t\t"); // se puede usar el @?
                fflush(stdin);
                gets(validarString);
            } while ((escribeMailCorrecto(validarString)) != 2);
            strcpy(clientenuevo.Mail, validarString);

            clientenuevo.bajaCliente = 'a';
            clientenuevo.totalGastado = 0;
            clientenuevo.totalCompras = 0;

            fwrite(&clientenuevo, sizeof(stCliente), 1, archi);

            fclose(archi);
        }
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir.\n\n\t\t");
    }

    return flag; // si el cliente ya existe retorna 1
}



/////////////////////////////////////////// BUSCAR PEDIDOS /////////////////////////////////////////////////////////////////////

nodoPedido* buscarIdPedidoConDni ( nodoArbolCliente * arbolito, int dni, int nroPedido) // retorna el pedido
{
    nodoArbolCliente * c= NULL;
    nodoPedido* seg=NULL;
    nodoPedido* buscado=NULL;

    if (arbolito)
    {
        c= buscarNodoArbolPorDni(arbolito,dni);

        seg = c->pedidos;
        while (seg && buscado==NULL)
        {
            if ( seg->dato.idPedido == nroPedido)
            {
                buscado=seg;
            }
            seg=seg->siguiente;
        }
    }
    return buscado;
}

nodoPedido* buscarPedidoSinDni (nodoArbolCliente *t, int idPedido)
{
    nodoPedido *buscado = NULL;
    nodoPedido * seg= NULL;

    if(t){
        if (t->pedidos->dato.idPedido == idPedido)
        {
            buscado = t->pedidos;
        }else{

            seg = t->pedidos;
            while(seg && buscado==NULL)
            {
                if (t->pedidos->dato.idPedido == idPedido)
                    {
                        buscado = t->pedidos;
                    }
                seg=seg->siguiente;
            }
        }

        if(!buscado)
        {
               buscado=buscarPedidoSinDni(t->izq,idPedido);

                if(!buscado)
                {
                    buscado=buscarPedidoSinDni(t->der,idPedido);
                }
            }
    }

    return buscado;
}

////////////////////////////////////////// MODIFICAR PEDIDO

void modificarPedidoPorId(nodoArbolCliente * arbolito, int idpedido) // Modificar pedido por ID
{
    stPedido auxPedido;
    nodoPedido* auxiliar=NULL;
    char opcion = 's';

    if (arbolito)
    {
        auxiliar = buscarPedidoSinDni(arbolito,idpedido);

        if (auxiliar)
        {
            if (auxiliar->modificado == 1)
            {
                modificarUnpedido(auxPedido); // retorna el pedido leido, ya modificado por la funcion
            }
            else
            {

                printf("\n\n\t\t El pedido se encuentra en estado anulado\n");
            }
        }
    }
}
