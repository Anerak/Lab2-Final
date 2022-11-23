#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./Headers/cliente.h"

///////////////////////////////////////////FUNCIONES DE CLIENTES////////////////////////////////////////////////////////////

stDomicilio cargarDomicilio(stDomicilio domicilio)
{
    int depto = 0;
    char validarNum[dim];
    char validarString[dim];
    char validarChar;

    printf("\n\n\t\tCarga del domicilio del cliente ingrese:\n");
    printf("\n\n\t\t  0 - Si es un departamento\n\n\t\t  1 - Si es una casa:\n\n\t\t");
    fflush(stdin);
    scanf("%d", &depto);

    do
    {
        printf("\n\n\t\tIngrese la provincia:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(domicilio.provincia, validarString);

    do
    {
        printf("\n\n\t\tIngrese la localidad:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(domicilio.localidad, validarString);

    do
    {
        printf("\n\n\t\tIngrese el nombre de la calle:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(domicilio.Calle, validarString);

    do
    {
        printf("\n\n\t\tIngrese la altura\n\t\t");
        fflush(stdin);
        scanf("%s", validarNum);
    } while ((validarNumero(validarNum)) != 0);
    domicilio.altura = (atoi(validarNum));

    if (depto == 0) /// coloca el usuario todos los datos del depto
    {
        do
        {
            printf("\n\n\t\tIngrese el piso:\n\t\t");
            fflush(stdin);
            scanf("%s", validarNum);
        } while ((validarNumero(validarNum)) != 0);
        domicilio.piso = (atoi(validarNum));

        do
        {
            printf("\n\n\t\tIngrese el departamento:\n\t\t");
            fflush(stdin);
            scanf("%c", &validarChar);
        } while ((isalpha(validarChar)) == 0);
        domicilio.dpto = validarChar;
    }
    else // si es casa - se agrega un 0 y una o en piso y depto.
    {
        domicilio.piso = 0;
        domicilio.dpto = 'o';
    }

    return domicilio;
}

int cargarArregloDeClientes(stCliente nombreArreglo[dim]) // retorna los validos cargados al arreglo
{
    FILE *buffer = fopen(ArchivoClientes, "rb");

    stCliente A;
    int i = 0;

    if (buffer != NULL)
    {
        while (((fread(&A, sizeof(stCliente), 1, buffer)) > 0) && i < dim)
        {
            nombreArreglo[i] = A;
            i++;
        }
        fclose(buffer);
    }

    return i;
}

///////////////////////////////////////////////////MOSTRAR///////////////////////////////////////////////////////////////////

void mostrarClienteResumido(stCliente c)
{
    printf("DNI: %i | %s %s\n", c.dni, c.Nombre, c.Apellido);
    return;
}

void mostrarCliente(stCliente cliente)
{
    printf("\n\n\t\t----------------------CLIENTE----------------------\n");
    printf("\t\t\t    ID de Cliente:     %i \n", cliente.idCliente);
    printf("\t\t\t    DNI:               %i \n", cliente.dni);
    printf("\t\t\t    Nombre:            %s \n", cliente.Nombre);
    printf("\t\t\t    Apellido:          %s \n", cliente.Apellido);
    printf("\n\t\t\t DATOS DEL DOMICILIO:\n");
    printf("\t\t\t    Provincia:         %s \n", cliente.domicilio.provincia);
    printf("\t\t\t    Localidad:         %s \n", cliente.domicilio.localidad);
    printf("\t\t\t    Calle:             %s \n", cliente.domicilio.Calle);
    printf("\t\t\t    Altura:            %i \n", cliente.domicilio.altura);
    printf("\t\t\t      Piso:            %i \n", cliente.domicilio.piso);
    printf("\t\t\t      Dpto:            %c \n", cliente.domicilio.dpto);
    printf("\n\t\t\t DATOS DE CONTACTO:\n");
    printf("\t\t\t    Telefono:          %lu \n", cliente.telefono);
    printf("\t\t\t    Mail:              %s \n", cliente.Mail);
    printf("\n\t\t\t ESTADO DEL CLIENTE:  \n");
    if (cliente.bajaCliente == 0)
    {
        printf("\t\t\t                      Activo \n");
        printf("\t\t\t     Total gastado:    $ %.2f \n", cliente.totalGastado);
        printf("\t\t\tCompras efectuadas:    %i  \n", cliente.totalCompras);
    }
    else if (cliente.bajaCliente == 1)
    {
        printf("\t\t\t                      Inactivo \n");
    }
    else
    {
        printf("\t\t\t                      -  \n");
    }

    printf("\n\n\t\t--------------------------------------------------------------------------\n");
}

void mostrarArchivoClientes()
{
    FILE *archi = fopen(ArchivoClientes, "rb");
    stCliente aux;

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            mostrarCliente(aux);
        }
        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }
}

void mostrarArregloDeClientes(stCliente arrClientes[], int validos)
{
    int i = 0;

    while (i < validos)
    {
        mostrarCliente(arrClientes[i]);
        i++;
    }
}

///////////////////////////////////////////MODIFICAR CLIENTES////////////////////////////////////////////////////////////////
// TODO: Something
int modificarCliente(stCliente *modificarCliente)
{

    int cambios = 0;
    char seguir = 's';
    char auxPalabra[40], auxNumero[10];

    if (modificarCliente->bajaCliente == 1)
    {
        printf("\n\n\t\tEl cliente se encuentra INACTIVO desea activarlo nuevamente? \n\t\tIngrese S para confirmar, otra para cancelar.\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);

        if (seguir == 's' || seguir == 'S')
        {
            modificarCliente->bajaCliente = 0;
            cambios++;
        }
    }

    printf("\n\n\t\tIngrese S para editar nombre, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese el nombre nuevo:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
            cambios++;
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente->Nombre, auxPalabra);
    }

    printf("\n\n\t\tIngrese S para editar apellido, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese el apellido nuevo:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
            cambios++;
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente->Apellido, auxPalabra);
    }

    printf("\n\n\t\tIngrese S para editar domicilio, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        modificarCamposDomicilio(modificarCliente);
    }

    printf("\n\n\t\tIngrese S para editar telefono, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese el nuevo numero tel:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente->telefono = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese S para editar mail, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\n\t\tIngrese mail:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
        } while ((escribeMailCorrecto(auxPalabra) != 2));
        strcpy(modificarCliente->Mail, auxPalabra);
    }

    return cambios;
}

int modificarCamposDomicilio(stCliente *modificarCliente)
{
    int cambios = 0;
    char seguir = 's';
    char auxPalabra[40], auxNumero[10];

    printf("\n\n\t\t s para editar calle, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese la calle:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
            cambios++;
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente->domicilio.Calle, auxPalabra);
    }

    printf("\n\n\t\tIngrese s para editar altura, u otra letra para cancelar\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese la altura:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
            cambios++;
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente->domicilio.altura = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese s para editar piso, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tngrese el numero del piso:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
            cambios++;
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente->domicilio.piso = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese s para editar dpto, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tIngrese el departamento:\n\t\t");
        fflush(stdin);
        scanf("%c", &modificarCliente->domicilio.dpto);
        cambios++;
    }

    printf("\n\n\t\tIngrese s para editar localidad, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese la localidad:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
            cambios++;
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente->domicilio.localidad, auxPalabra);
    }

    printf("\n\n\t\tIngrese s para editar provincia, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese la provincia:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);
            cambios++;
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente->domicilio.provincia, auxPalabra);
    }
    return cambios;
}

//////////////////////////////////////////////////////////////////////////////////
//////// Arreglos Clientes

int buscarPosMenor(stCliente array[], int pos, int validos)
{
    stCliente menor;
    menor = array[pos];

    int posMenor = pos;

    int i = pos + 1;

    while (i < validos)
    {
        if (menor.dni > array[i].dni)
        {
            menor = array[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

void ordenarSeleccion(stCliente array[], int validos)
{
    int i = 0;
    int posMenor;

    stCliente aux;

    while (i < validos)
    {
        posMenor = buscarPosMenor(array, i, validos);
        aux = array[posMenor];
        array[posMenor] = array[i];
        array[i] = aux;
        i++;
    }
}

/////////////                        Arboles                        //////////////
//////////////////////////////////////////////////////////////////////////////////
stCliente crearCliente(int id, int dni)
{
    stCliente c;
    c.idCliente = id + 1;
    c.dni = dni;
    fflush(stdin);

    printf("Nombre: ");
    gets(c.Nombre);
    fflush(stdin);

    printf("Apellido: ");
    gets(c.Apellido);
    fflush(stdin);

    printf("Telefono: ");
    scanf("%d", &c.telefono);
    fflush(stdin);

    c.domicilio = cargarDomicilio(c.domicilio);

    fflush(stdin);

    printf("Email: ");
    gets(c.Mail);
    fflush(stdin);

    c.bajaCliente = 0;
    c.totalCompras = 0;
    c.totalGastado = 0;

    return c;
}

int bajaCliente(stCliente *c)
{

    FILE *a = fopen(ArchivoClientes, "r+b");

    stCliente aux;

    int r = 0;

    if (a)
    {
        while (fread(&aux, sizeof(stCliente), 1, a) > 0 && !r)
        {
            if (aux.dni == c->dni)
            {
                printf("%d\n", ftell(a) / sizeof(stCliente));
                fseek(a, (sizeof(stCliente)) * (-1), SEEK_CUR);
                printf("%d\n", ftell(a) / sizeof(stCliente));
                c->bajaCliente = 1;
                fwrite(c, sizeof(stCliente), 1, a);
                r = 1;
            }
        }
        fclose(a);
    }

    return r;
}

int guardarCliente(stCliente c)
{
    FILE *a = fopen(ArchivoClientes, "r+b");
    int r = 0;
    if (a)
    {
        stCliente aux;
        while (fread(&aux, sizeof(stCliente), 1, a) > 0 && !r)
        {
            if (aux.dni == c.dni)
            {
                printf("%d", ftell(a));
                fseek(a, (sizeof(stCliente) * 2) * (-1), SEEK_CUR);
                printf("%d", ftell(a));
                fwrite(&c, sizeof(stCliente), 1, a);
                r = 1;
            }
        }

        fclose(a);
    }
    return r;
}