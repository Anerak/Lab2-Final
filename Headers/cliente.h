#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "./utils.h"
#include "./domicilio.h"

typedef struct
{

    long int dni;
    int idCliente;
    char Nombre[30];
    char Apellido[30];
    stDomicilio domicilio;
    unsigned long telefono;
    char Mail[40];
    char bajaCliente;
    int totalCompras;
    float totalGastado;

} stCliente;

///////////////////////////////////////////FUNCIONES CLIENTES////////////////////////////////////////////////////////////////

///////////// CARGAR :
int validacionDeAlta(long int dni);
int ultimoIdCliente();
stDomicilio cargarDomicilio(stDomicilio domicilio);
int altaDeCliente(stCliente clientenuevo);
int cargarClientes(stCliente clientes[], int dimension);
void cargarTotalGastadoYcompra(float costoPedido, int idCliente, int compra); // funcion para sumar el costo pedido al total gastado cliente

///////////// MOSTRAR :
void mostarCliente(stCliente cliente);
void mostrarArchivoClientes();
void mostrarArregloDeClientes(stCliente arrClientes[], int validos);

///////////// BUSCAR :
int buscarClientePorDNI(long int dni);         // retorno la poscion en el archivo o -1 si no lo encontro
int buscarClientePorApellido(char apellido[]); // retorno la poscion en el archivo
int buscarClientePorID(int IDcliente);
stCliente retornaClientePorPos(int pos);

///////////// ANULAR :
stCliente pasaraInactivo(stCliente clientebaja);
int darBajarCliente(long int dniaux); // retorna la posicion del cliente anulado o -1 si no lo encontro

////////////////////////////////////////////////MODIFACCIONES/////////////////////////////////////////////////////////////////

//// CLIENTES :

stCliente modificacionClientePorDni(long int dniCliente);           // modificacion por DNI cliente
stCliente modificarClientePorApellido(char apellido[]);             // modificacion por apellido
stCliente modificarCamposDeCliente(stCliente modificarCliente);     // funcion que recibe cliente para devolverlo modificado
stDomicilio modificarCamposDomicilio(stCliente stdomicilioCliente); // modifica domicilio

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

#endif