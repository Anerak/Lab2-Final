#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/fecha.h"



///////////////////////////////////////////FUNCIONES DE FECHA////////////////////////////////////////////////////////////

///////////////////////////////////////////////////CARGA///////////////////////////////////////////////////////////////////

stFecha cargarFecha() // cargar estructura fecha
{
    char validarNum[dim];
    char validarString[dim];
    stFecha A;

    do
    {
        printf("\n\n\t\t          Ingrese el dia:\n\t\t\t\t");
        fflush(stdin);
        scanf("%s", validarNum);

    } while ((validarNumero(validarNum)) != 0);
    A.dia = (atoi(validarNum));

    do
    {
        printf("\n\n\t\t          Ingrese el mes: (numeros del 1 al 12)\n\t\t\t\t");
        fflush(stdin);
        scanf("%s", validarNum);
    } while (((validarNumero(validarNum)) != 0));
    A.Mes = (atoi(validarNum));

    do
    {
        printf("\n\n\t\t          Ingrese el anio:\n\t\t\t\t");
        fflush(stdin);
        scanf("%s", validarNum);
    } while ((validarNumero(validarNum)) != 0 && atoi(validarNum) < 2000 && atoi(validarNum) > 2050);
    A.anio = (atoi(validarNum));

    return A;
}


///////////////////////////////////////////////////MOSTRAR///////////////////////////////////////////////////////////////////

void mostrarMes(stFecha A)
{
    if (A.Mes == 1)
    {
        printf(" Enero", A.Mes);
    }
    else if (A.Mes == 2)
    {
        printf(" Febrero", A.Mes);
    }
    else if (A.Mes == 3)
    {
        printf(" Marzo", A.Mes);
    }
    else if (A.Mes == 4)
    {
        printf(" Abril", A.Mes);
    }
    else if (A.Mes == 5)
    {
        printf(" Mayo", A.Mes);
    }
    else if (A.Mes == 6)
    {
        printf(" Junio", A.Mes);
    }
    else if (A.Mes == 7)
    {
        printf(" Julio", A.Mes);
    }
    else if (A.Mes == 8)
    {
        printf(" Agosto", A.Mes);
    }
    else if (A.Mes == 9)
    {
        printf(" Septiembre", A.Mes);
    }
    else if (A.Mes == 10)
    {
        printf(" Octubre", A.Mes);
    }
    else if (A.Mes == 11)
    {
        printf(" Noviembre", A.Mes);
    }
    else
    {
        printf(" Diciembre", A.Mes);
    }
}

void mostrarFecha(stFecha A)
{
    printf(" %i  ", A.dia);
    mostrarMes(A);
    printf(" %i ", A.anio);
}

void mostrarFechaAcotada(stFecha A)
{
    printf(" %i / %i / %i  ", A.dia,A.Mes,A.anio);
}

/////////////////////////////////////////MODIFICAR FECHA////////////////////////////////////////////////////////////////////

stFecha modificarFechaPedido(stFecha fecha) // Auxiliar - Modifica fecha
{
    char seguir = 's';
    int opcion = 0;
    char auxNumero[10];

    do
    {

        printf("\n\n              Modificar Fecha  \n\n");
        printf("\t\tIngrese:");
        printf("\n\t\t\t1 - Para modificar el dia");
        printf("\n\t\t\t2 - Para modificar el mes");
        printf("\n\t\t\t3 - Para modificar el anio\n");
        scanf("%i", &opcion);

        if (opcion == 1)
        {
            do
            {
                printf("\n\n\t\tIngrese el dia:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            fecha.dia = atoi(auxNumero);
        }
        else if (opcion == 2)
        {

            do
            {
                printf("\n\n\t\tIngrese mes:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            fecha.Mes = atoi(auxNumero);
        }
        else if (opcion == 3)
        {

            do
            {
                printf("\n\n\t\tIngrese el anio:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            fecha.anio = atoi(auxNumero);
        }

        printf("Si desea modificar otro dato de la fecha ingrese s o cualquier tecla para finalizar la modificacion:\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);
    } while (seguir == 's');

    return fecha;
}

int compararFecha(stFecha a, stFecha b)
{
    int x = 0;

    // I'm definitely not proud of this spaghetti

    if (a.anio > b.anio)
    {
        x = 1;
    }
    else if (a.anio < b.anio)
    {
        x = -1;
    }
    else
    {
        if (a.Mes > b.Mes)
        {
            x = 1;
        }
        else if (a.Mes < b.Mes)
        {
            x = -1;
        }
        else
        {
            if (a.dia > b.dia)
            {
                x = 1;
            }
            else if (a.dia < b.dia)
            {
                x = -1;
            }
        }
    }

    return x;
}
