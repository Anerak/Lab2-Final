#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/producto.h"

//////////////////////////////////////// CARGAR //////////////////////////////////////////////////////////////////

stProducto cargarDetalleProducto() // cargar detalle de pedido
{
    char validarNum1[dim];
    char validarString[dim];
    stProducto A;

    do
    {
        printf("\n\n\t\t          Ingrese el nombre del producto:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(A.Producto, validarString);

    do
    {
        printf("\n\n\t\t          Ingrese el modelo del producto:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(A.Modelo, validarString);

    printf("\n\n\t\t           Cuantos productos de este modelo?:\n\t\t");
    fflush(stdin);
    scanf("%i", &A.cantidad);


    printf("\n\n\t\t          Ingrese el precio del producto:\n\t\t");
    scanf("%f", &A.precio);

    A.precioFinal = (float)(A.precio * A.cantidad);

    return A;
}

//////////////////////////////////////// MOSTRAR //////////////////////////////////////////////////////////////////

void mostrarDetalleProducto(stProducto A)
{
    printf("\n\n\t\t     Descripcion del pedido:\n");
    printf("\t\t             Producto:  %s \n", A.Producto);
    printf("\t\t             Modelo:    %s \n", A.Modelo);
    printf("\t\t             Cantidad:  %i \n", A.cantidad);
    printf("\t\t             Precio:  $ %.2f \n", A.precio);
}

void mostrarArregloProducto(stProducto arreglo[], int validos)
{
    int i = 0;

    while (i < validos)
    {
        mostrarDetalleProducto(arreglo[i]);
        i++;
    }
}

//////////////////////////////////////// MODIFICAR //////////////////////////////////////////////////////////////////

float modificarArregloProductos(stProducto arrProductos[], int validos) // Auxiliar - recorre y modifica arreglo de productos
{
    int i = 0;
    float costo = 0;

    while (i < validos)
    {
        printf("\n\n\n\t\t----------------PRODUCTO N %i----------------------------\n", i + 1);
        arrProductos[i] = modificarUnProducto(arrProductos[i]);
        costo += arrProductos[i].precioFinal;
        i++;
    }
    return costo;
}

void modificarNombreProducto(char nombre[])
{
    char seguir = 's';
    printf("\n\n\t\tIngrese S para editar nombre producto, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tIngrese Nombre producto:\n\t\t");
        fflush(stdin);
        gets(nombre);
    }
}

void modificarModeloProducto(char modelo[])
{
    char seguir = 's';
    printf("\n\n\t\tIngrese S para editar Modelo, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tIngrese Modelo:\n\t\t");
        fflush(stdin);
        gets(modelo);
    }
}

int modificarCantidadProductos(int cantidad)
{
    char seguir = 's';
    printf("\n\n\t\tIngrese S para editar cantidad, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\t\tIngrese la cantidad de productos de este modelo:\n\t\t");
        scanf("%i", &cantidad);
    }
    return cantidad;
}

float modificarPrecioProducto(float precio)
{
    char seguir = 's';
    printf("\n\n\t\tIngrese S para editar precio, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {

        printf("\n\n\t\tIngrese precio producto:\n\t\t");
        scanf("%f", &precio);
    }
    return precio;
}

stProducto modificarUnProducto(stProducto producto) // Modifica un Producto existente
{
    modificarNombreProducto(producto.Producto);
    modificarModeloProducto(producto.Modelo);
    producto.cantidad = modificarCantidadProductos(producto.precio);
    producto.precio = modificarPrecioProducto(producto.precio);

    producto.precioFinal = (float)((producto.precio) * (producto.cantidad));

    return producto;
}
