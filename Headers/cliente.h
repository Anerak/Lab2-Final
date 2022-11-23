#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "utils.h"
#include "domicilio.h"

typedef struct
{
    int dni;
    int idCliente;
    char Nombre[30];
    char Apellido[30];
    stDomicilio domicilio;
    unsigned long telefono;
    char Mail[40];
    int bajaCliente;
    int totalCompras;
    float totalGastado;

} stCliente;

///////////////////////////////////////////FUNCIONES CLIENTES////////////////////////////////////////////////////////////////

///////////// CARGAR :
stDomicilio cargarDomicilio(stDomicilio domicilio);

///////////// MOSTRAR :
void mostrarClienteResumido(stCliente c);
void mostrarCliente(stCliente cliente);
void mostrarArchivoClientes();
void mostrarArregloDeClientes(stCliente arrClientes[], int validos);

///////////// MODIFICAR:
int modificarCliente(stCliente *modificarCliente);           // funcion que recibe cliente para devolverlo modificado
int modificarCamposDomicilio(stCliente *stdomicilioCliente); // modifica domicilio

//////////// ARREGLO Clientes:
int buscarPosMenor(stCliente array[], int pos, int validos);
void ordenarSeleccion(stCliente array[], int validos);

//////////// ARBOLES
stCliente crearCliente(int id, int dni);
int bajaCliente(stCliente *c);
int guardarCliente(stCliente c);
void mostrarClientesInactivos();

///////////////////////////////////////////////

#endif
