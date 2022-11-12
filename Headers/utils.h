#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "fecha.h"
#define dim 300

#define ArchivoClientes "clientes.dat"
#define ArchivoPedidos "pedidos.dat"
///////////////////////////////////////////FUNCIONES GENERALES////////////////////////////////////////////////////////////////

///////////////////////////////////////////////VALIDACIONES///////////////////////////////////////////////////////////////////

// retorna 0 si el nro esta ok 1 si ingreso otro caracter
int validarNumero(char numeros[]);
// retorna 0 si la palabra esta ok 1 si ingreso otro caracter
int validarPalabra(char palabra[]);

int buscarClientePorID(int IDcliente);

// retorna mail correcto
int escribeMailCorrecto(char palabra[]);

// valida que no halla espacios
int validarMailCliente(char palabra[]);

// valida que tenga @ y .com
int validarfinalMail(char palabra[]);

int validarCliente(int idCliente);

// retorna cant de datos que hay en un archivo seleccionado indicando nombre y tama�o, o -1 si el archivo no existe
int cantidadDeDatosEnArchivo(char nombreArchivo[], int tamanioArchivo);

/// 0 si son iguales
/// 1 si A es más reciente que B
/// -1 si B es más reciente que A
int compararFecha(stFecha a, stFecha b);

#endif