#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED
#include "fecha.h"
#include "producto.h"
#include "cliente.h"

typedef struct _stPedido
{
    int idPedido;
    int idCliente;
    stFecha fecha;
    stProducto arregloDePedidos[10];
    int costoPedido;
    int cantidadProductos;
    int estadoDelPedido; // 1: activo 0:anulado
    char detalleEstado;
    long int dniCliente;
} stPedido;

///////////////////////////////////////////FUNCIONES PEDIDOS////////////////////////////////////////////////////////////////////

///////////// CARGAR :
stPedido generarPedido();

///////////// MOSTRAR :
void mostrarUnPedido(stPedido A);
void mostrarUnPedidoAcotado(stPedido A);

///////////// PEDIDOS :
stPedido modificarUnpedido(stPedido auxPedido); // Modifica un pedido completo
void modificarArchivoPedido(stPedido pedido);

#endif
