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

int ultimoIdcliente()
{
    stCliente Aux;
    int IDcliente = 0;

    FILE *buffer = fopen(ArchivoClientes, "rb");

    if (buffer != NULL)
    {
        fseek(buffer, sizeof(stCliente) * (-1), 2);
        if ((fread(&Aux, sizeof(stCliente), 1, buffer)) > 0)

        {
            IDcliente = Aux.idCliente;
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

            id = ultimoIdcliente();
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

void cargarTotalGastadoYcompra(float costoPedido, int idCliente, int compra) // funcion para sumar el costo pedido al total gastado cliente
{
    stCliente auxCliente;
    int pos = -1;

    FILE *buffer = fopen(ArchivoClientes, "r+b");

    if (buffer != NULL)
    {
        pos = buscarClientePorID(idCliente);

        if (pos > -1)
        {
            fseek(buffer, sizeof(stCliente) * (pos), SEEK_SET);
            fread(&auxCliente, sizeof(stCliente), 1, buffer);

            auxCliente.totalGastado += costoPedido;
            auxCliente.totalCompras += compra;

            fseek(buffer, sizeof(stCliente) * (pos), SEEK_SET);
            fwrite(&auxCliente, sizeof(stCliente), 1, buffer);
        }

        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo.\n\n\t\t");
    }
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

void mostarCliente(stCliente cliente)
{
    printf("\n\n\t\t---------------------CLIENTE-----------------------\n");
    printf("\t\t    ID de Cliente:     %i \n", cliente.idCliente);
    printf("\t\t    DNI:               %i \n", cliente.dni);
    printf("\t\t    Nombre:            %s \n", cliente.Nombre);
    printf("\t\t    Apellido:          %s \n", cliente.Apellido);
    printf("\n\t\t DATOS DEL DOMICILIO:\n");
    printf("\t\t    Provincia:         %s \n", cliente.domicilio.provincia);
    printf("\t\t    Localidad:         %s \n", cliente.domicilio.localidad);
    printf("\t\t    Calle:             %s \n", cliente.domicilio.Calle);
    printf("\t\t    Altura:            %i \n", cliente.domicilio.altura);
    printf("\t\t      Piso:            %i \n", cliente.domicilio.piso);
    printf("\t\t      Dpto:            %c \n", cliente.domicilio.dpto);
    printf("\n\t\t DATOS DE CONTACTO:\n");
    printf("\t\t    Telefono:          %lu \n", cliente.telefono);
    printf("\t\t    Mail:              %s \n", cliente.Mail);
    printf("\n\t\t ESTADO DEL CLIENTE:  \n");
    if (cliente.bajaCliente == 'a')
    {
        printf("\t\t                      Activo \n");
        printf("\t\t     Total gastado:    $ %.2f \n", cliente.totalGastado);
        printf("\t\tCompras efectuadas:    %i  \n", cliente.totalCompras);
    }
    else if (cliente.bajaCliente == 'i')
    {
        printf("\t\t                      Inactivo \n");
    }
    else
    {
        printf("\t\t                      -  \n");
    }

    printf("\n\n\t\t--------------------------------------------\n");
}

void mostrarArchivoClientes()
{
    FILE *archi = fopen(ArchivoClientes, "rb");
    stCliente aux;

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            mostarCliente(aux);
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
        mostarCliente(arrClientes[i]);
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

int buscarClientePorApellido(char apellido[]) // retorno la poscion en el archivo y si no lo encuntra -1
{
    int i = 0, opcion = 0, pos = -1, u = 0;
    stCliente auxCliente;
    int dimension = cantidadDeDatosEnArchivo(ArchivoClientes, sizeof(stCliente));
    stCliente *arrClientes = (stCliente *)malloc(sizeof(stCliente) * dimension);
    int *arrPosiciones = (int *)malloc(sizeof(int) * dimension);

    FILE *archi = fopen(ArchivoClientes, "rb");

    if (archi != NULL)
    {
        while (fread(&auxCliente, sizeof(stCliente), 1, archi) > 0)
        {
            if (strcmpi(auxCliente.Apellido, apellido) == 0)
            {
                // fseek(archi,sizeof(stCliente)(-1),SEEK_CUR);
                arrClientes[i] = auxCliente;
                arrPosiciones[i] = (ftell(archi)) / (sizeof(stCliente)); // da la posicion actual
                                                                         //  la posicion queda lista para buscar en fseek

                i++;
            }
        }

        if (i > 1)
        {
            printf("\n\n\t\tVarios clientes tinenen el mismo apellido, se enumeran a continuacion:\n\n\t\t");
            while (u < i)
            {
                printf("\n\n\t\t------------------- Cliente %u -------------------\n\n", u);
                mostarCliente(arrClientes[u]);
                u++;
            }
            printf("\n\n\t\tSeleccione el numero de cliente que desea modificar\n\n\t\t");
            scanf("%i", &opcion);
            pos = arrPosiciones[opcion - 1];
            pos = pos - 1;
        }
        else if (i == 1)
        {
            pos = arrPosiciones[0];
            pos = pos - 1;
        }

        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }

    return pos;
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

////////////////////////////////////////////////BAJA DE CLIENTE/////////////////////////////////////////////////////////////

stCliente pasaraInactivo(stCliente clientebaja)
{
    clientebaja.bajaCliente = 'i';

    return clientebaja;
}

int darBajarCliente(long int dniaux) // retorna la posicion del cliente anulado o -1 si no lo encontro
{
    FILE *archi = fopen(ArchivoClientes, "r+b"); // para leer y escribir en el archivo
    int flag = -1;
    stCliente aux;

    if (archi != NULL)
    {
        flag = buscarClientePorDNI(dniaux); // nos da la posicion del cliente en el archivo
        if (flag != -1)
        {
            fseek(archi, (sizeof(stCliente) * flag), 0); // ubicar en la pocision del cliente
            fread(&aux, sizeof(stCliente), 1, archi);    // lee el cliente
            aux = pasaraInactivo(aux);                   // pasa a estar inactivo
            fseek(archi, (sizeof(stCliente) * flag), 0);
            fwrite(&aux, sizeof(stCliente), 1, archi);
        }
        else
        {
            printf("\n\n\t\tNo se encontro el cliente\n\n\t\t");
        }
        fclose(archi);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }

    return flag;
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
            auxCliente = modificarCamposDeCliente(auxCliente);
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

stCliente modificarClientePorApellido(char apellido[]) // modificacion por apellido - retorna el cliente modificado
{
    stCliente auxCliente;
    int pos = -1;

    FILE *buff = fopen(ArchivoClientes, "r+b");

    if (buff != NULL)
    {
        pos = buscarClientePorApellido(apellido);

        if (pos >= 0)
        {
            fseek(buff, sizeof(stCliente) * (pos), SEEK_SET);
            fread(&auxCliente, sizeof(stCliente), 1, buff);
            auxCliente = modificarCamposDeCliente(auxCliente); // se llama funcion para modificar los campos de el cliente y retornar las modificaciones
            fseek(buff, sizeof(stCliente) * (-1), SEEK_CUR);
            fwrite(&auxCliente, sizeof(stCliente), 1, buff); // sobreescribe los datos actualizados en el archivo

            fclose(buff);
        }
        else
        {
            printf("\n\n\t\tEl cliente que desea modificar no existe, ingrese otro dni o verifique el numero.\n\n\t\t");
        }
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo.\n\n\t\t");
    }

    return auxCliente;
}

stCliente modificarCamposDeCliente(stCliente modificarCliente)
{

    char seguir = 's';
    char auxPalabra[40], auxNumero[10];

    if (modificarCliente.bajaCliente == 'i')
    {
        printf("\n\n\t\tEl cliente se encuentra INACTVIO desea activarlo nuevamente? \n\t\tIngrese S para confirmar, otra para cancelar.\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);

        if (seguir == 's' || seguir == 'S')
        {
            modificarCliente.bajaCliente = 'a';
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
        } while ((validarNumero(auxNumero) != 0));
        modificarCliente.idCliente = atoi(auxNumero);
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
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente.Nombre, auxPalabra);
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
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente.Apellido, auxPalabra);
    }

    printf("\n\n\t\tIngrese S para editar domicilio, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        modificarCliente.domicilio = modificarCamposDomicilio(modificarCliente);
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
        modificarCliente.dni = atoi(auxNumero);
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
        modificarCliente.telefono = atoi(auxNumero);
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
        strcpy(modificarCliente.Mail, auxPalabra);
    }

    printf("\n\n\t\tIngrese S para editar el total gastado, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tCorrija el saldo:\n\t\t");
        scanf("%f", &modificarCliente.totalGastado);
    }

    return modificarCliente;
}

stDomicilio modificarCamposDomicilio(stCliente modificarCliente)
{

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
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente.domicilio.Calle, auxPalabra);
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
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente.domicilio.altura = atoi(auxNumero);
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
        } while ((validarNumero(auxNumero)) != 0);
        modificarCliente.domicilio.piso = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese s para editar dpto, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        printf("\n\n\t\tIngrese el departamento:\n\t\t");
        fflush(stdin);
        scanf("%c", &modificarCliente.domicilio.dpto);
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
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente.domicilio.localidad, auxPalabra);
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
        } while ((validarPalabra(auxPalabra) != 0));
        strcpy(modificarCliente.domicilio.provincia, auxPalabra);
    }
    return modificarCliente.domicilio;
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
            if (aux.bajaCliente == 'a')
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
                mostarCliente(PCliente);
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
