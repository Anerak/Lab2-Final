#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include "utils.h"

typedef struct stFecha
{
    int dia;
    int Mes;
    int anio;
} stFecha;

///////////////////////////////////////////FUNCIONES FECHA////////////////////////////////////////////////////////////////////

///////////// CARGAR :
stFecha cargarFecha();

///////////// MOSTRAR :
void mostrarMes(stFecha A);
void mostrarFecha(stFecha A);

//////////// MODIFICAR :
stFecha modificarFechaPedido(stFecha fecha);                        // Modifica fecha

/// 0 si son iguales
/// 1 si A es más reciente que B
/// -1 si B es más reciente que A
int compararFecha(stFecha a, stFecha b);

#endif
