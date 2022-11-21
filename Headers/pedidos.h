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
    int estadoDelPedido;
    char detalleEstado;
    long int dniCliente;
} stPedido;
///////////////////////////////////////////FUNCIONES PEDIDOS////////////////////////////////////////////////////////////////////

///////////// CARGAR :
stFecha cargarFecha(stFecha);
stProducto cargarDetalleProducto(stProducto);
stPedido generarPedido();

///////////// MOSTRAR :
void mostrarMes(stFecha A);
void mostrarFecha(stFecha A);
void mostrarDetalleProducto(stProducto A);

void mostrarUnPedido(stPedido A);

//// PEDIDOS :

stFecha modificarFechaPedido(stPedido auxPedido);                        // Modifica fecha
float modificarArregloProductos(stProducto arrProductos[], int validos); // recorre y modifica arreglo de productos
stProducto modificarUnProducto(stProducto auxProducto);                  // Modifica un Producto existente
stPedido modificarUnpedido(stPedido auxPedido);                          // Modifica un pedido completo

/////////////////////////////////////////LISTADOS Y ESTADISTICAS//////////////////////////////////////////////////////////////

//// PEDIDOS:

void insertarDiaArreglo(stPedido arregloPedidos[], int i, stPedido A);
void insertarMesArreglo(stPedido arregloPedidos[], int i, stPedido A);
void insertarAnioArreglo(stPedido arregloPedidos[], int i, stPedido A);
void ordenamientoFechaInsercion(stPedido nomArreglo[], int validos);
int listarPedidosPorFecha(stPedido nomArreglo[]);
void mostrarPedidosPorCliente(int idAuxCliente);

#endif
