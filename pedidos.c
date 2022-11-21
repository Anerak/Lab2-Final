#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/fecha.h"
#include "./Headers/pedidos.h"
#include "./Headers/arbol.h"
#include "./Headers/producto.h"


///////////////////////////////////////////FUNCIONES DE PEDIDOS////////////////////////////////////////////////////////////

///////////////////////////////////////////////////CARGA///////////////////////////////////////////////////////////////////

stPedido generarPedido() // carga un pedido, llama a las funciones anteriores
{
    stPedido A;
    stProducto arregloProd[30];

    int i = 0;
    float costo = 0;
    char opcion = 's';
    char validarNumero[dim];

    printf("\n\n\t\t Fecha del pedido:\n\t\t");
    A.fecha = cargarFecha();

    printf("\n\n\t\tDescripcion del pedido:\n\t\t");
    while (opcion == 's' && i < 10)
    {
        A.arregloDePedidos[i] = cargarDetalleProducto();
        costo = costo + A.arregloDePedidos[i].precioFinal;
        i++;
        printf("\n\n\t\tDesea agregar otro producto al pedido? \n\t\t(s para adicionar otro producto, n para salir)\n\t\t");
        fflush(stdin);
        scanf("%c", &opcion);
    }

    A.cantidadProductos = i;

    printf("\n\n\t\tEl costo final del pedido es: $%.2f\n\t\t", costo);
    A.costoPedido = costo;

    A.estadoDelPedido = 1;
    A.detalleEstado = 's';

    return A;
}

///////////////////////////////////////////////////MOSTRAR///////////////////////////////////////////////////////////////////

void mostrarUnPedido(stPedido A)
{
    printf("\n\t\t    ID de Pedido:     %i ", A.idPedido);
    printf("\n\t\t    ID de Cliente:    %i ", A.idCliente);
    printf("\n\t\t    DNI de Cliente:   %i ", A.dniCliente);
    printf("\n\t\t    Fecha del pedido: ");
    mostrarFecha(A.fecha);
    mostrarArregloProducto(A.arregloDePedidos, A.cantidadProductos);
    printf("\n\t\t    Costo de pedido: $ %i \n", A.costoPedido);
    if (A.estadoDelPedido == 1)
    {
        printf("\t\t   ESTADO DEL PEDIDO:     ACTIVO\n");

        if (A.detalleEstado == 's')
        {
            printf("\t\t                              Procesando solicitud\n");
        }
        else if (A.detalleEstado == 'p')
        {
            printf("\t\t                               En preparacion\n");
        }
        else
        {
            printf("\t\t                               Enviado\n");
        }
    }
    else
    {
        printf("\n\t\t   ESTADO DEL PEDIDO:     ANULADO\n");
    }

    printf("\t\t..........................................................\n");
}

/////////////////////////////////////////MODIFICAR PEDIDOS////////////////////////////////////////////////////////////////////

stPedido modificarUnpedido(stPedido pedido)
{
    int i = 0;
    float costo = 0;
    char seguir = 's', opcion = 's';
    char auxPalabra[40], auxNumero[10];

    stProducto P;

    printf("\n\n\t\tPara modificar la fecha del producto ingrese s o cualquier letra para continuar:\n\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        pedido.fecha = modificarFechaPedido(pedido.fecha);
    }

    printf("\n\n\t\tPara modificar los productos del arreglo ingrese S, u otra letra para cancelar:\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        float nuevoCosto = modificarArregloProductos(pedido.arregloDePedidos, pedido.cantidadProductos);
        pedido.costoPedido = nuevoCosto;
    }

    printf("\n\n\t\tIngrese S para editar el detalle de estado, u otra letra para cancelar:\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tIngrese detalle de estado:\n\t\t");
        fflush(stdin);
        scanf("%c", &pedido.detalleEstado);
    }

    return pedido;
}
