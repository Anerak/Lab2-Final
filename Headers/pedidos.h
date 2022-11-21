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
stFecha cargarFecha();
stProducto cargarDetalleProducto();
stPedido generarPedido();

///////////// MOSTRAR :
void mostrarMes(stFecha A);
void mostrarFecha(stFecha A);
void mostrarDetalleProducto(stProducto A);
void mostrarArregloProducto (stProducto arreglo [],int validos);
void mostrarUnPedido(stPedido A);

///////////// PEDIDOS :

stFecha modificarFechaPedido(stPedido auxPedido);                        // Modifica fecha
float modificarArregloProductos(stProducto arrProductos[], int validos); // recorre y modifica arreglo de productos
void modificarNombreProducto (char nombre []);
void modificarModeloProducto (char modelo []);
int modificarCantidadProductos (int cantidad);
float modificarPrecioProducto (float precio);

stProducto modificarUnProducto(stProducto auxProducto);                  // Modifica un Producto existente
stPedido modificarUnpedido(stPedido auxPedido);                          // Modifica un pedido completo



#endif
