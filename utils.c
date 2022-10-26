#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Headers/utils.h"
#include "./Headers/pedidos.h"

////////////////////////////////////////////////VALIDACION////////////////////////////////////////////////////////////////

int validarNumero(char numeros[]) // retorna 0 si el nro esta ok 1 si ingreso otro caracter
{
    int i = 0;
    int flag = 0;

    while (i < strlen(numeros) && flag == 0)
    {
        if ((isdigit(numeros[i])) != 0)
        {
            i++;
        }
        else
        {
            printf("\n\n\t\tUn dato ingresado no es un numero.Vuelva a ingresar el dato:\n\n\t\t");
            flag = 1;
        }
    }

    return flag;
}

int validarPalabra(char palabra[]) // retorna 0 si la palabra esta ok 1 si ingreso otro caracter
{
    int i = 0;
    int flag = 0;

    while (i < strlen(palabra) && flag == 0)
    {
        if ((isalpha(palabra[i])) != 0 || (isspace(palabra[i]) != 0))
        {
            i++;
        }
        else
        {
            printf("\n\n\t\tIngreso un caracter erroneo. Solo ingrese letras: \n\n\t\t");
            flag = 1;
        }
    }

    return flag;
}

int escribeMailCorrecto(char palabra[]) // devuelve 2 si las dos verificaciones estan correctas
{
    int flag = 0;

    flag = validarMailCliente(palabra);
    flag += validarfinalMail(palabra);

    system("cls");

    return flag;
}

int validarMailCliente(char palabra[]) // Auxiliar verifica que no haya espacios en el mail
{
    int i = 0;
    int flag = 1;

    while (i < strlen(palabra) && flag != 0)
    {
        if (((isspace(palabra[i]) == 0)))
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }

        i++;
    }

    return flag;
}

int validarfinalMail(char palabra[]) // Auxiliar verifica que haya ingresado .com y @
{
    int flag = 0;

    if (strstr(palabra, "@") != NULL && (strstr(palabra, ".com") != NULL))
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

int validarCliente(int idCliente) // Retorna 1 si existe o -1 si no existe
{
    int flag = -1;
    stCliente auxCliente;

    FILE *buff = fopen(ArchivoClientes, "rb");

    if (buff != NULL)
    {

        while ((fread(&auxCliente, sizeof(stCliente), 1, buff)) > 0 && flag == -1)
        {
            if (auxCliente.idCliente == idCliente)
            {
                flag = 1;
            }
        }
        fclose(buff);
    }
    else
    {
        printf("\n\n\t\tNo fue posible abrir el archivo de clientes\n\n\t\t");
    }

    return flag;
}

int cantidadDeDatosEnArchivo(char nombreArchivo[], int tamanioArchivo) // retorna cantidad de datos que hay en un archivo seleccionado indicando nombre y tama�o, o -1 si el archivo no existe
{
    int cant = -1;
    FILE *buff = fopen(nombreArchivo, "rb");
    if (buff != NULL)
    {

        fseek(buff, 0, SEEK_END); /// posicionamos el cursor al final

        cant = (ftell(buff)) / (tamanioArchivo);

        fclose(buff);
    }

    return cant;
}
