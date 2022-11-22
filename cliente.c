#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./Headers/cliente.h"

///////////////////////////////////////////FUNCIONES DE CLIENTES////////////////////////////////////////////////////////////

///////////////////////////////////////////////////CARGA///////////////////////////////////////////////////////////////////

int validacionDeAlta(long int dni) // recorriendo el archivo y verifica si existe
{
    int flag = 0;
    stCliente aux;

    FILE *archi = fopen(ArchivoClientes, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stCliente), 1, archi) > 0 && flag == 0)
        {
            if (aux.dni == dni)
            {
                printf("\n\n\t\tEl cliente ya se encuentra cargado en el archivo.\n\n\t\t"); // si ya exite corta la busqueda con el flag si no el cliente se puede agregar a la lista.
                flag = 1;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo.\n\n\t\t");
    }

    return flag;
}

int ultimoIDCliente()
{
    stCliente Aux;
    int IDcliente = 0;

    FILE *buffer = fopen(ArchivoClientes, "rb");

    if (buffer != NULL)
    {
        fseek(buffer, sizeof(stCliente) * (-1), 2);
        if ((fread(&Aux, sizeof(stCliente), 1, buffer)) > 0)
        {
            if (Aux.idCliente > IDcliente)
            {
                IDcliente = Aux.idCliente;
            }
        }
        fclose(buffer);
    }

    return IDcliente;
}

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

int altaDeCliente(stCliente clientenuevo) //
{
    stDomicilio domicilio;
    int flag = -1, id = 0;
    long int DniAux = 0;

    char validarNum[dim];
    char validarString[dim];

    FILE *archi = fopen(ArchivoClientes, "ab");

    if (archi != NULL)
    {
        printf("\n\n\t\tIngrese el DNI:\n\t\t");
        fflush(stdin);
        scanf("%li", &DniAux);

        flag = validacionDeAlta(DniAux);

        if (flag == 0)
        {
            clientenuevo.dni = DniAux;

            id = ultimoIDCliente();
            clientenuevo.idCliente = id + 1;
            printf("\n\n\t\tID Cliente: 0000%i \n\n", clientenuevo.idCliente);

            do
            {
                printf("\n\n\t\tIngrese el nombre  del cliente:\n\t\t");
                fflush(stdin);
                gets(validarString);
            } while ((validarPalabra(validarString)) != 0);
            strcpy(clientenuevo.Nombre, validarString);

            do
            {
                printf("\n\n\t\tIngrese el apellido del cliente:\n\t\t");
                fflush(stdin);
                gets(validarString);
            } while ((validarPalabra(validarString)) != 0);
            strcpy(clientenuevo.Apellido, validarString);

            domicilio = cargarDomicilio(domicilio);
            clientenuevo.domicilio = domicilio;

            do
            {
                printf("\n\n\t\tIngrese el numero de telefono del cliente:\n\t\t");
                fflush(stdin);
                scanf("%s", validarNum);
            } while ((validarNumero(validarNum)) != 0);
            clientenuevo.telefono = (atoi(validarNum));

            do
            {
                printf("\n\n\t\tIngrese el mail del cliente:\n\t\t"); // se puede usar el @?
                fflush(stdin);
                gets(validarString);
            } while ((escribeMailCorrecto(validarString)) != 2);
            strcpy(clientenuevo.Mail, validarString);

            clientenuevo.bajaCliente = 'a';
            clientenuevo.totalGastado = 0;
            clientenuevo.totalCompras = 0;

            fwrite(&clientenuevo, sizeof(stCliente), 1, archi);

            fclose(archi);
        }
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir.\n\n\t\t");
    }

    return flag; // si el cliente ya existe retorna 1
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
    printf("ID: %i | DNI: %i | %s %s\n", c.idCliente, c.dni, c.Nombre, c.Apellido);
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

////////////////////////////////////////BUSQUEDA CLIENTES//////////////////////////////////////////////////////////////

int buscarClientePorDNI(long int dni) // retorna la poscion en el archivo, si no lo encuentra -1
{
    int flag = -1;
    stCliente aux;

    FILE *archi = fopen(ArchivoClientes, "rb");

    if (archi != NULL)
    {
        while (flag == -1 && fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if (aux.dni == dni)
            {
                flag = (ftell(archi)) / (sizeof(stCliente)); // da la posicion.
                flag = flag - 1;                             // la posicion queda lista para buscar en fseek
            }
        }
        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }

    return flag;
}

int buscarClientePorID(int IDcliente) // retorna la posicion si lo encuentra, o -1 si no esta
{
    int flag = -1;
    stCliente A;

    FILE *buffer = fopen(ArchivoClientes, "rb");

    if (buffer != NULL)
    {
        while (flag == -1 && fread(&A, sizeof(stCliente), 1, buffer) > 0)
        {
            if (A.idCliente == IDcliente)
            {
                flag = (ftell(buffer)) / (sizeof(stCliente)); // da la posicion.
                flag = flag - 1;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }
    return flag;
}

stCliente retornaClientePorPos(int pos)
{
    FILE *buffer = fopen(ArchivoClientes, "rb");
    stCliente A;
    stCliente Aux;

    if (buffer != NULL)
    {
        fseek(buffer, ((sizeof(stCliente)) * (pos)), 0);
        fread(&A, sizeof(stCliente), 1, buffer);
        Aux = A;
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }

    return Aux;
}

///////////////////////////////////////////MODIFICAR CLIENTES////////////////////////////////////////////////////////////////

stCliente modificacionClientePorDni(long int dniCliente) // modificacion por DNI cliente
{
    stCliente auxCliente;
    int pos = -1;

    FILE *buff = fopen(ArchivoClientes, "r+b");

    if (buff != NULL)
    {
        pos = buscarClientePorDNI(dniCliente);

        if (pos >= 0)
        {
            fseek(buff, sizeof(stCliente) * (pos), SEEK_SET);
            fread(&auxCliente, sizeof(stCliente), 1, buff);
            modificarCliente(&auxCliente);
            fseek(buff, sizeof(stCliente) * (-1), SEEK_CUR);

            fwrite(&auxCliente, sizeof(stCliente), 1, buff);
            fclose(buff);
        }
        else
        {
            printf("\n\n\t\tEl cliente que desea modificar no existe, ingrese otro DNI o verifique el numero.\n\n\t\t");
        }
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo \n\n\t\t");
    }

    return auxCliente;
}
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

    printf("\n\n\t\tIngrese S para editar el ID del cliente, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese el nuevo ID del cliente:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
            cambios++;
        } while ((validarNumero(auxNumero) != 0));
        modificarCliente->idCliente = atoi(auxNumero);
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

    printf("\n\n\t\tIngrese S para editar el DNI cliente, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\n\t\tIngrese el nuevo DNI:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente->dni = atoi(auxNumero);
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

///////////////////////////////////////////LISTADOS CLIENTES//////////////////////////////////////////////////////////////////

int pasarActivosArreglo(stCliente clientes[]) // pasar los clientes activos
{
    int i = 0;
    stCliente aux;
    FILE *archi = fopen(ArchivoClientes, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stCliente), 1, archi) > 0 && i < dim)
        {
            if (aux.bajaCliente == 0)
            {
                clientes[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\t\t");
    }

    return i;
}

void insertarClienteNombre(stCliente clientes[], int i, stCliente nuevo) // inserccion por nombre
{

    while (i >= 0 && strcmpi(clientes[i].Apellido, nuevo.Apellido) == 0 && strcmpi(clientes[i].Nombre, nuevo.Nombre) == 1) // cambie esta linea
    {
        clientes[i + 1] = clientes[i];
        i--;
    }
    clientes[i + 1] = nuevo;
}

void insertarClienteApellido(stCliente clientes[], int i, stCliente nuevo)
{

    while (i >= 0 && strcmpi(clientes[i].Apellido, nuevo.Apellido) == 1) // cambie esta linea
    {
        clientes[i + 1] = clientes[i];
        i--;
    }
    clientes[i + 1] = nuevo;
}

void ordenacionInsercion(stCliente clientes[], int validos) // ordenar por insercion nombre y apellido
{
    int i = 0;

    while (i < validos - 1)
    {
        insertarClienteApellido(clientes, i, clientes[i + 1]);
        i++;
    }
    i = 0;

    while (i < validos - 1)
    {
        insertarClienteNombre(clientes, i, clientes[i + 1]);
        i++;
    }
}

int listarClientesInsercion(stCliente clientes[dim])
{
    int validos = 0;

    validos = pasarActivosArreglo(clientes);
    ordenacionInsercion(clientes, validos);

    return validos;
}

int posicionMenor(stCliente clientes[], int pos, int validos) // por id
{
    int menor = clientes[pos].idCliente;
    int posmenor = pos;
    int i = pos + 1;

    while (i < validos)
    {
        if (menor > clientes[i].idCliente)
        {
            menor = clientes[i].idCliente;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void ordenamientoSeleccion(stCliente clientes[], int validos) // ordena el arreglo
{
    int posmenor;
    stCliente aux;
    int i = 0;

    while (i < validos - 1)
    {
        posmenor = posicionMenor(clientes, i, validos);
        aux = clientes[posmenor];
        clientes[posmenor] = clientes[i];
        clientes[i] = aux;
        i++;
    }
}

int listarClientesSeleccion(stCliente arregloClientes[dim])
{
    int validos = 0;

    validos = pasarActivosArreglo(arregloClientes);
    ordenamientoSeleccion(arregloClientes, validos);

    return validos;
}

void insertarClientesPorMonto(stCliente arrClientes[], int pos, stCliente auxCliente) // Auxiliar - Inserte del mejor al peor cliente por compras
{

    while (pos >= 0 && arrClientes[pos].totalGastado < auxCliente.totalGastado)
    {
        arrClientes[pos + 1] = arrClientes[pos];
        pos--;
    }
    arrClientes[pos + 1] = auxCliente;
}

void insertarClientesPorCompras(stCliente arrClientes[], int pos, stCliente auxCliente) // Auxiliar - Inserte del mejor al peor cliente por compras
{

    while (pos >= 0 && arrClientes[pos].totalCompras < auxCliente.totalCompras)
    {
        arrClientes[pos + 1] = arrClientes[pos];
        pos--;
    }
    arrClientes[pos + 1] = auxCliente;
}

int topTenMejoresClientes(stCliente clientes[dim]) // Top TEN Mejores clientes
{

    int i = 0;
    int validos = pasarActivosArreglo(clientes);

    while (i < validos)
    {
        insertarClientesPorMonto(clientes, i, clientes[i + 1]);
        i++;
    }

    i = 0;
    while (i < validos)
    {
        insertarClientesPorCompras(clientes, i, clientes[i + 1]);
        i++;
    }

    return validos;
}

stCliente peorCliente() // Retorna el peor cliente
{
    stCliente auxC, PCliente;
    int menorCompra;

    FILE *buff = fopen(ArchivoClientes, "rb");

    if (buff != NULL)
    {
        fread(&auxC, sizeof(stCliente), 1, buff);
        menorCompra = auxC.totalCompras;

        while ((fread(&auxC, sizeof(stCliente), 1, buff)) > 0)
        {
            if (auxC.totalCompras < menorCompra)
            {
                menorCompra = auxC.totalCompras;
                PCliente = auxC;
                mostrarCliente(PCliente);
            }
        }
        fclose(buff);
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo\n\n\t\t");
    }

    return PCliente;
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

    FILE *a = fopen(ArchivoClientes, "w+b");

    stCliente aux;

    int r = 0;

    if (a)
    {
        while (fread(&aux, sizeof(stCliente), 1, a) > 0)
        {
            if (aux.dni == c->dni)
            {
                fseek(a, sizeof(stCliente) * (-1), SEEK_CUR);
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
        while (fread(&aux, sizeof(stCliente), 1, a) > 0)
        {
            if (aux.dni == c.dni)
            {
                fseek(a, sizeof(stCliente) * (-1), SEEK_CUR);
                fwrite(&c, sizeof(stCliente), 1, a);
                r = 1;
                break;
            }
        }

        fclose(a);
    }
    return r;
}