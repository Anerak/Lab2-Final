#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED
#include "./fecha.h"
#include "./producto.h"
#include "./cliente.h"

typedef struct
{
    int idPedido;
    int idCliente;
    stFecha fecha;
    stProducto arregloDePedidos[10];
    int costoPedido;
    int cantidadProductos;
    int estadoDelPedido;
    char detalleEstado;
} stPedido;

///////////////////////////////////////////FUNCIONES PEDIDOS////////////////////////////////////////////////////////////////////

///////////// CARGAR :
stFecha cargarFecha(stFecha);
stProducto cargarDetalleProducto(stProducto);
int ultimoIdPedido();
stPedido cargarPedido();
int cargarArregloDePedidos(stPedido nombreArreglo[]);

///////////// MOSTRAR :
void mostrarMes(stFecha A);
void mostrarFecha(stFecha A);
void mostrarDetalleProducto(stProducto A);
void mostrarArregloProducto(stProducto A[], int validos);
void mostrarUnPedido(stPedido A);
void mostrarArchivoPedidos();
void mostrarArregloPedidos(stPedido nomArreglo[], int validos);

///////////// BUSCAR :
int buscarIdPedido(int); // retorno la poscion en el archivo o -1 si no esta
stPedido retornaPedidoPorPos(int pos);

///////////// ANULAR :
int anularPedido(int nroPedido);
stPedido verificarPedidoAnulado(stPedido auxPedido, int *estadoPedido);

//// PEDIDOS :

void modificarPedidoPorId(int idpedido);                                 // Modifica pedido por ID
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