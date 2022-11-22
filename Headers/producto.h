#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
#include "utils.h"

typedef struct
{
    char Producto[60];
    char Modelo[30];
    int cantidad;
    float precio;
    float precioFinal;
} stProducto;


stProducto cargarDetalleProducto();
void mostrarDetalleProducto(stProducto A);
void mostrarArregloProducto (stProducto arreglo [],int validos);

float modificarArregloProductos(stProducto arrProductos[], int validos); // recorre y modifica arreglo de productos
void modificarNombreProducto (char nombre []);
void modificarModeloProducto (char modelo []);
int modificarCantidadProductos (int cantidad);
float modificarPrecioProducto (float precio);
stProducto modificarUnProducto(stProducto auxProducto);                  // Modifica un Producto existente


#endif
