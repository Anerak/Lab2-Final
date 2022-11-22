#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "utils.h"
#include "domicilio.h"

typedef struct
{
    long int dni;
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
stCliente crearCliente(int id, int dni);
void mostrarClienteResumido(stCliente c);
void mostrarCliente(stCliente cliente);
void mostrarClienteResumido(stCliente c);
int bajaCliente(stCliente *c);
int guardarCliente(stCliente c);

///////////// CARGAR :

int validacionDeAlta(long int dni);
int ultimoIDCliente();
stDomicilio cargarDomicilio(stDomicilio domicilio);
int altaDeCliente(stCliente clientenuevo);
int cargarClientes(stCliente clientes[], int dimension);

///////////// MOSTRAR :
void mostrarArchivoClientes();
void mostrarArregloDeClientes(stCliente arrClientes[], int validos);

///////////// BUSCAR :
int buscarClientePorDNI(long int dni); // retorno la poscion en el archivo o -1 si no lo encontro
int buscarClientePorID(int IDcliente);
stCliente retornaClientePorPos(int pos);

////////////////////////////////////////////////MODIFACCIONES/////////////////////////////////////////////////////////////////

//// CLIENTES :

stCliente modificacionClientePorDni(long int dniCliente);    // modificacion por DNI cliente
stCliente modificarClientePorApellido(char apellido[]);      // modificacion por apellido
int modificarCliente(stCliente *modificarCliente);           // funcion que recibe cliente para devolverlo modificado
int modificarCamposDomicilio(stCliente *stdomicilioCliente); // modifica domicilio

/////////////////////////////////////////LISTADOS Y ESTADISTICAS//////////////////////////////////////////////////////////////

//// CLIENTES :

int pasarActivosArreglo(stCliente clientes[]); // pasar los clientes activos
void insertarClienteNombre(stCliente clientes[], int i, stCliente nuevo);
void insertarClienteApellido(stCliente clientes[], int i, stCliente nuevo);
void ordenacionInsercion(stCliente clientes[], int validos);
int listarClientesInsercion(stCliente clientes[]);
int posicionMenor(stCliente clientes[], int pos, int validos); // por id
void ordenamientoSeleccion(stCliente clientes[], int validos); // ordena el arreglo
int listarClientesSeleccion(stCliente arregloClientes[]);

void insertarClientesPorMonto(stCliente arrClientes[], int pos, stCliente auxCliente);
void insertarClientesPorCompras(stCliente arrClientes[], int pos, stCliente auxCliente);
int topTenMejoresClientes(stCliente clientes[]);
stCliente peorCliente();

///////////////////////////////////////////////

// Arreglo Clientes:

void ordenarSeleccion(stCliente array[], int validos);
int buscarPosMenor(stCliente array[], int pos, int validos);

#endif
