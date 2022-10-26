#ifndef DOMICILIO_H_INCLUDED
#define DOMICILIO_H_INCLUDED
typedef struct
{

    char provincia[15];
    char localidad[15];
    char Calle[30];
    int altura;
    int piso;
    char dpto;

} stDomicilio;
#endif