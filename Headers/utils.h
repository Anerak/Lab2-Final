#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define dim 300

#define ArchivoClientes "Archivo de Clientes"
#define ArchivoPedidos "Archivo de Pedidos"
///////////////////////////////////////////FUNCIONES GENERALES////////////////////////////////////////////////////////////////

///////////////////////////////////////////////VALIDACIONES///////////////////////////////////////////////////////////////////

int validarNumero(char numeros[]);  // retorna 0 si el nro esta ok 1 si ingreso otro caracter
int validarPalabra(char palabra[]); // retorna 0 si la palabra esta ok 1 si ingreso otro caracter
int buscarClientePorID(int IDcliente);
int escribeMailCorrecto(char palabra[]); // retorna mail correcto
int validarMailCliente(char palabra[]);  // valida que no halla espacios
int validarfinalMail(char palabra[]);    // valida que tenga @ y .com
int validarCliente(int idCliente);
int cantidadDeDatosEnArchivo(char nombreArchivo[], int tamanioArchivo); // retorna cant de datos que hay en un archivo seleccionado indicando nombre y tama�o, o -1 si el archivo no existe

#endif