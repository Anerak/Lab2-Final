#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/fecha.h"
#include "./Headers/pedidos.h"
///////////////////////////////////////////FUNCIONES DE PEDIDOS////////////////////////////////////////////////////////////

///////////////////////////////////////////////////CARGA///////////////////////////////////////////////////////////////////

stFecha cargarFecha(stFecha A) // cargar estructura fecha
{
    char validarNum[dim];
    char validarString[dim];

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
        printf("\n\n\t\t          Ingrese el a�o:\n\t\t\t\t");
        fflush(stdin);
        scanf("%s", validarNum);
    } while ((validarNumero(validarNum)) != 0 && atoi(validarNum) < 2000 && atoi(validarNum) > 2050);
    A.anio = (atoi(validarNum));

    return A;
}

stProducto cargarDetalleProducto(stProducto A) // cargar detalle de pedido
{
    char validarNum1[dim];
    char validarString[dim];

    do
    {
        printf("\n\n\t\t          Ingrese el nombre del producto:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(A.Producto, validarString);

    do
    {
        printf("\n\n\t\t          Ingrese el modelo del producto:\n\t\t");
        fflush(stdin);
        gets(validarString);
    } while ((validarPalabra(validarString)) != 0);
    strcpy(A.Modelo, validarString);

    do
    {
        printf("\n\n\t\t           Cuantos productos de este modelo?:\n\t\t");
        fflush(stdin);
        scanf("%s", validarNum1);
    } while ((validarNumero(validarNum1)) != 0);
    A.cantidad = (atoi(validarNum1));

    printf("\n\n\t\t          Ingrese el precio del producto:\n\t\t");
    scanf("%f", &A.precio);

    A.precioFinal = (A.precio * A.cantidad);

    return A;
}

int ultimoIdPedido() // Abre el archivo y busca el ID del ultimo pedido y lo retorna
{
    stPedido A;
    int IDpedido = 0;

    FILE *buffer = fopen(ArchivoPedidos, "rb");

    if (buffer != NULL)
    {
        fseek(buffer, sizeof(stPedido) * (-1), 2);
        if ((fread(&A, sizeof(stPedido), 1, buffer)) > 0)
        {
            IDpedido = A.idPedido;
        }
        fclose(buffer);
    }

    return IDpedido;
}

stPedido cargarPedido() // carga un pedido, llama a las funciones anteriores
{
    stPedido A;
    stProducto P;
    stFecha F;
    stCliente C;
    stProducto arregloProd[30];

    int i = 0, idPedido = 0, validarIDcliente = 0, opcionCliente;
    float costo = 0;
    char opcion = 's';
    char validarNumero[dim];

    FILE *buffer = fopen(ArchivoPedidos, "ab");

    if (buffer != NULL)
    {
        idPedido = ultimoIdPedido();
        A.idPedido = idPedido + 1;
        printf("\n\n\t\tID Pedido: 0000%i \n\n", A.idPedido);

        do
        {
            opcionCliente = 0;
            printf("\n\n\t\tIngrese el ID del Cliente:\n\t\t");
            fflush(stdin);
            scanf("%i", &validarIDcliente);

            if ((validarCliente(validarIDcliente)) != -1)
            {
                A.idCliente = validarIDcliente;
            }
            else
            {
                printf("\n\n\t\tEl numero ingresado no corresponde a un cliente guardado.\n\t\tSi desea volver a ingresar el numero ingrese 1.\n\t\tPara cargar un nuevo cliente ingrese 2.\n\n\t\t");
                scanf("%i", &opcionCliente);
            }
        } while (opcionCliente == 1);

        if (opcionCliente == 2)
        {
            altaDeCliente(C);
            A.idCliente = C.idCliente;
        }

        printf("\n\n\t\t Fecha del pedido:\n\t\t");
        F = cargarFecha(F);
        A.fecha = F;

        printf("\n\n\t\tDescripcion del pedido:\n\t\t");
        while (opcion == 's' && i < 10)
        {
            P = cargarDetalleProducto(P);
            A.arregloDePedidos[i] = P;
            i++;
            costo += P.precioFinal;
            printf("\n\n\t\tDesea agregar otro producto al pedido? \n\t\t(s para adicionar otro producto, n para salir)\n\t\t");
            fflush(stdin);
            scanf("%c", &opcion);
        }

        A.cantidadProductos = i;

        printf("\n\n\t\tEl costo final del pedido es: $%.2f\n\t\t", costo);
        A.costoPedido = costo;

        A.estadoDelPedido = 1;
        A.detalleEstado = 's';

        cargarTotalGastadoYcompra(costo, validarIDcliente, 1);

        fwrite(&A, sizeof(stPedido), 1, buffer);
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo de pedidos, vuelva a intentarlo.\n\t\t");
    }

    return A;
}

int cargarArregloDePedidos(stPedido nombreArreglo[dim]) // retorna los validos cargados al arreglo
{

    FILE *buffer = fopen(ArchivoPedidos, "rb");

    stPedido A;
    int i = 0;

    if (buffer != NULL)
    {
        while (((fread(&A, sizeof(stPedido), 1, buffer)) > 0) && i < dim)
        {
            nombreArreglo[i] = A;
            i++;
        }
        fclose(buffer);
    }

    return i;
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

void mostrarDetalleProducto(stProducto A)
{
    printf("\n\n\t\t     Descripcion del pedido:\n");
    printf("\t\t             Producto: %s \n", A.Producto);
    printf("t\t              Modelo:   %s \n", A.Modelo);
    printf("\t\t             Cantidad: %i \n", A.cantidad);
    printf("\t\t             Precio: $ %.2f \n", A.precio);
}

void mostrarArregloProducto(stProducto A[], int validos)
{
    int i = 0;

    while (i < validos)
    {
        mostrarDetalleProducto(A[i]);
        i++;
    }
}
void mostrarUnPedido(stPedido A)
{
    printf("\n\n\t\t--------------------------------------------\n");
    printf("\n\t\t    ID de Pedido:     %i ", A.idPedido);
    printf("\n\t\t    ID de Cliente:    %i ", A.idCliente);
    printf("\n\t\t    Fecha del pedido: ");
    mostrarFecha(A.fecha);
    mostrarArregloProducto(A.arregloDePedidos, A.cantidadProductos);
    printf("\t\t    Costo de pedido: $ %i \n", A.costoPedido);
    if (A.estadoDelPedido == 1)
    {
        printf("\t\t   ESTADO DEL PEDIDO:     ACTIVO\n");

        if (A.detalleEstado == 's')
        {
            printf("\t\t                              Procesando solicitud\n");
        }
        else if (A.detalleEstado == 'p')
        {
            printf("\t\t                               En preparacion\n");
        }
        else
        {
            printf("\t\t                               Enviado\n");
        }
    }
    else
    {
        printf("\n\t\t   ESTADO DEL PEDIDO:     ANULADO\n");
    }

    printf("\t\t--------------------------------------------\n");
}

void mostrarArchivoPedidos()
{
    FILE *buffer = fopen(ArchivoPedidos, "rb");
    stPedido A;

    if (buffer != NULL)
    {
        while ((fread(&A, sizeof(stPedido), 1, buffer)) > 0)
        {
            mostrarUnPedido(A);
        }
    }
    else
    {

        printf("\n\n\t\tEl archivo no pudo ser abierto, vuelve a intentarlo o consulte con su adiministrador.\n\n\t\t");
    }

    fclose(buffer);
}

void mostrarArregloPedidos(stPedido nomArreglo[], int validos)
{
    int i = 0;

    while (i < validos)
    {
        mostrarUnPedido(nomArreglo[i]);
        i++;
    }
}

///////////////////////////////////////////////////BUSCAR///////////////////////////////////////////////////////////////////

int buscarIdPedido(int nroPedido) // retorno la poscion en el archivo o -1 si no esta
{
    int flag = -1;
    stPedido A;

    FILE *buffer = fopen(ArchivoPedidos, "rb");

    if (buffer != NULL)
    {
        while (flag == -1 && fread(&A, sizeof(stPedido), 1, buffer) > 0)
        {
            if (A.idPedido == nroPedido)
            {
                flag = (ftell(buffer)) / (sizeof(stPedido)); // da la posicion.
                flag = flag - 1;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir.\n\n\t\t");
    }

    return flag;
}

stPedido retornaPedidoPorPos(int pos)
{
    FILE *buffer = fopen(ArchivoPedidos, "rb");
    stPedido A;
    stPedido Aux;

    if (buffer != NULL)
    {
        fseek(buffer, ((sizeof(stPedido)) * (pos)), 0);
        fread(&A, sizeof(stPedido), 1, buffer);
        Aux = A;
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tEl archivo no se pudo abrir\n\n\t\t");
    }

    return Aux;
}

///////////////////////////////////////////////////ANULAR//////////////////////////////////////////////////////////////////

int anularPedido(int nroPedido) // devuelve  la posicion del pedido o -1 si no encontro el pedido
{
    FILE *buffer = fopen(ArchivoPedidos, "r+b");
    stPedido A;
    int flag = -1, costoP = 0;

    if (buffer != NULL)
    {
        flag = buscarIdPedido(nroPedido); // nos da la posicion del cliente en el archivo
        if (flag != -1)
        {
            fseek(buffer, (sizeof(stPedido) * flag), 0); // ubicar en la pocision del cliente
            fread(&A, sizeof(stPedido), 1, buffer);      // lee el cliente

            if (A.estadoDelPedido == 1)
            {
                A.estadoDelPedido = 0;
                costoP = A.costoPedido;
                A.costoPedido = 0;

                cargarTotalGastadoYcompra((costoP * -1), A.idCliente, -1); // realiza el descuetento de la compra anulada al totalgastado por el cliente
                fseek(buffer, (sizeof(stPedido) * flag), 0);
                fwrite(&A, sizeof(stPedido), 1, buffer);
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo de pedidos. Vuelva a intentarlo.\n\n\t\t");
    }
    return flag;
}

stPedido verificarPedidoAnulado(stPedido auxPedido, int *estadoPedido) // verifica si el pedido esta anulado
{
    int opcion = 0;

    // estado en 0 estaba inactivo y no cambio ---> no entra en modificaciones
    // estdo en 1 ya estaba activo ---> no se modifica la compra
    // estado en 2 estaba inactivo y se activo ---> se realiza la activacion de la compra y puede acceder a modificaciones si lo desa

    if (auxPedido.estadoDelPedido == 0)
    {
        printf("\a\n\n\t\tEl pedido se encuentra inactivo.\n\n\t\tPara modificarlo debe activarlo\n\n\t\t");
        printf("\n\n\t\tDesea activar o salir?\nIngrese 1 para confirmar u otro numero para cancelar y salir\n\n\t\t");
        scanf("%i", &opcion);
        if (opcion == 1)
        {
            *estadoPedido += 2;
            auxPedido.estadoDelPedido = 1;
            cargarTotalGastadoYcompra(auxPedido.costoPedido, auxPedido.idCliente, 1);

        } // si entro al if por estar en 0 y no lo activa el estado estara en 0 inactivo y no entrara a modifcaciones
    }
    else if (auxPedido.estadoDelPedido == 1) // si estaba activo entra aca puede entrar a modificaciones
    {
        *estadoPedido += 1;
    }

    return auxPedido;
}

///////////////////////////////////////LISTADOS Y ESTADISTICAS////////////////////////////////////////////////////////////////

/////////////////////////////////////////MODIFICAR PEDIDOS////////////////////////////////////////////////////////////////////

void modificarPedidoPorId(int idpedido) // Modificar pedido por ID
{
    stPedido auxPedido;
    int pos = -1;
    int estado = 0;
    char opcion = 's';

    FILE *buff = fopen(ArchivoPedidos, "r+b");

    if (buff != NULL)
    {
        pos = buscarIdPedido(idpedido);

        if (pos >= 0)
        {
            fseek(buff, sizeof(stPedido) * (pos), SEEK_SET);
            fread(&auxPedido, sizeof(stPedido), 1, buff);
            auxPedido = verificarPedidoAnulado(auxPedido, &estado); // retorna el pedido si lo modifica a activo o no

            if (estado == 1)
            {
                auxPedido = modificarUnpedido(auxPedido); // retorna el pedido leido, ya modificado por la funcion
                fseek(buff, sizeof(stPedido) * (-1), SEEK_CUR);
                fwrite(&auxPedido, sizeof(stPedido), 1, buff); // sobreescre el pedido en el archivo
            }
            else if (estado == 2)
            {

                printf("\n\n\t\tEl pedido ahora esta activo desea realizar modificaciones?\nIngrese s para confirmar, otra letra para cancelar\n\n\t\t");
                fflush(stdin);
                scanf("%c", &opcion);

                if (opcion == 's')
                {
                    auxPedido = modificarUnpedido(auxPedido);
                }

                fseek(buff, sizeof(stPedido) * (-1), SEEK_CUR);
                fwrite(&auxPedido, sizeof(stPedido), 1, buff); // sobreescre el pedido en el archivo
            }
            fclose(buff);
        }
        else
        {
            printf("\n\n\t\tEl pedido que desea modificar no existe, ingrese otro id o verifique el mismo.\n\t\t");
        }
    }
    else
    {
        printf("\n\n\t\tNo pudo abrirse el archivo \n\n\t\t");
    }
}

stFecha modificarFechaPedido(stPedido auxPedido) // Auxiliar - Modifica fecha
{
    char seguir = 's';
    char auxNumero[10];

    printf("\n\n\t\tIngrese s para editar dia, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese el dia:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
        } while ((validarNumero(auxNumero)) != 0);
        auxPedido.fecha.dia = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese S para editar mes, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        do
        {
            printf("\n\n\t\tIngrese mes:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
        } while ((validarNumero(auxNumero)) != 0);
        auxPedido.fecha.Mes = atoi(auxNumero);
    }

    printf("\n\n\t\tIngrese S para editar anio, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\n\t\tIngrese el anio:\n\t\t");
            fflush(stdin);
            gets(auxNumero);
        } while ((validarNumero(auxNumero)) != 0);
        auxPedido.fecha.anio = atoi(auxNumero);
    }
    return auxPedido.fecha;
}

float modificarArregloProductos(stProducto arrProductos[], int validos) // Auxiliar - recorre y modifica arreglo de productos
{
    int i = 0;
    float costo = 0;

    while (i < validos)
    {
        printf("\n\n\n\t\t----------------PRODUCTO N %i----------------------------\n", i + 1);
        arrProductos[i] = modificarUnProducto(arrProductos[i]);
        costo += arrProductos[i].precioFinal;
        i++;
    }
    return costo;
}

stProducto modificarUnProducto(stProducto auxProducto) // Modicia un Producto existente
{
    char auxNumero[10], auxPalabra[40];
    char seguir = 's';

    printf("\n\n\t\tIngrese S para editar nombre producto, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\n\t\tIngrese Nombre producto:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);

        } while ((validarPalabra(auxPalabra)) != 0);

        strcpy(auxProducto.Producto, auxPalabra);
    }
    printf("\n\n\t\tIngrese S para editar Modelo, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\n\t\tIngrese Modelo:\n\t\t");
            fflush(stdin);
            gets(auxPalabra);

        } while ((validarPalabra(auxPalabra)) != 0);

        strcpy(auxProducto.Modelo, auxPalabra);
    }
    printf("\n\n\t\tIngrese S para editar cantidad, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {

        do
        {
            printf("\n\t\tIngrese la cantidad de productos de este modelo:\n\t\t");
            fflush(stdin);
            gets(auxNumero);

        } while ((validarNumero(auxNumero)) != 0);

        auxProducto.cantidad = atoi(auxNumero);
    }
    printf("\n\n\t\tIngrese S para editar precio, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's' || seguir == 'S')
    {

        printf("\n\n\t\tIngrese precio producto:\n\t\t");
        scanf("%f", &auxProducto.precio);
    }
    auxProducto.precioFinal = (float)((auxProducto.precio) * (auxProducto.cantidad));

    return auxProducto;
}

stPedido modificarUnpedido(stPedido auxPedido)
{
    int auxIdcliente = auxPedido.idCliente, i = 0;
    float costo = 0;
    char seguir = 's', opcion = 's';
    char auxPalabra[40], auxNumero[10];

    stProducto P;

    printf("\n\n\t\tIngrese S para editar id cliente, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        float costoP = auxPedido.costoPedido; // esta funcion descuenta la compra de el id que ya cargo y quiere cambiar
        costoP = costoP * (-1);
        cargarTotalGastadoYcompra(costoP, auxPedido.idCliente, -1);

        do
        {
            do
            {
                printf("\n\n\t\tIngrese el ID del cliente:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
        } while ((validarCliente(atoi(auxNumero))) != -1);
        auxPedido.idCliente = atoi(auxNumero);
    }

    printf("\n\n\t\tPara resetear todos los productos y cargar nuevos ingrese S, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        if (auxIdcliente == auxPedido.idCliente) // mismo cliente mismo idcliente
        {
            float costoP = auxPedido.costoPedido; // esta funcion descuenta la compra que ahora se quiere modificar
            costoP = costoP * (-1);
            cargarTotalGastadoYcompra(costoP, auxPedido.idCliente, -1 /* representa e*/);
        }

        while (opcion == 's' && i < 30)
        {
            P = cargarDetalleProducto(P);
            auxPedido.arregloDePedidos[i] = P;
            i++;
            costo += P.precioFinal;

            printf("\n\n\t\tDesea agregar otro producto al pedido? \n\t\t (S para adicionar otro producto, n para salir)\n\t\t");
            fflush(stdin);
            scanf("%c", &opcion);
        }

        auxPedido.cantidadProductos = i;
        auxPedido.costoPedido = costo;
        auxPedido.estadoDelPedido = 1;
        auxPedido.detalleEstado = 's';
        cargarTotalGastadoYcompra(costo, auxPedido.idCliente, 1);
    }
    else // si anteriormente modifico reseteo los pedidos no entra en este campo ya fue modificado en el if anterior
    {
        printf("\n\n\t\tPara modificar los productos del arreglo ingrese S, u otra letra para cancelar:\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);
        if (seguir == 's' || seguir == 'S')
        {
            if (auxIdcliente == auxPedido.idCliente) // mismo cliente mismo idcliente
            {
                float costoP = auxPedido.costoPedido; // esta funcion descuenta la compra que ahora se quiere modificar
                costoP = costoP * (-1);
                cargarTotalGastadoYcompra(costoP, auxPedido.idCliente, -1 /* representa e*/);
            }

            float nuevoCosto = modificarArregloProductos(auxPedido.arregloDePedidos, auxPedido.cantidadProductos);
            auxPedido.costoPedido = nuevoCosto;
            cargarTotalGastadoYcompra(nuevoCosto, auxPedido.idCliente, 1);
        }
        else
        {
            if (auxPedido.idCliente != auxIdcliente)
            {
                cargarTotalGastadoYcompra(auxPedido.costoPedido, auxPedido.idCliente, 1);
            }
        }

        printf("\n\n\t\tIngrese S para editar el detalle de estado, u otra letra para cancelar:\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);

        if (seguir == 's' || seguir == 'S')
        {
            printf("\n\n\t\tIngrese detalle de estado:\n\t\t");
            fflush(stdin);
            scanf("%c", &auxPedido.detalleEstado);
        }
    }

    printf("\n\n\t\tIngrese S para editar fecha, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        auxPedido.fecha = modificarFechaPedido(auxPedido);
    }

    return auxPedido;
}

void mostrarPedidosPorCliente(int idAuxCliente)
{
    stPedido arregloPedidos[dim];
    int validos = 0, i = 0;

    validos = cargarArregloDePedidos(arregloPedidos);

    while (i < validos)
    {
        if (arregloPedidos[i].idCliente == idAuxCliente)
        {
            mostrarUnPedido(arregloPedidos[i]);
        }
        i++;
    }
}

void insertarDiaArreglo(stPedido arregloPedidos[], int i, stPedido A)
{

    while (i >= 0 && arregloPedidos[i].fecha.dia > A.fecha.dia)
    {
        arregloPedidos[i + 1] = arregloPedidos[i];
        i--;
    }
    arregloPedidos[i + 1] = A;
}

void insertarMesArreglo(stPedido arregloPedidos[], int i, stPedido A)
{

    while (i >= 0 && arregloPedidos[i].fecha.Mes > A.fecha.Mes)
    {
        arregloPedidos[i + 1] = arregloPedidos[i];
        i--;
    }
    arregloPedidos[i + 1] = A;
}

void insertarAnioArreglo(stPedido arregloPedidos[], int i, stPedido A)
{

    while (i >= 0 && arregloPedidos[i].fecha.anio > A.fecha.anio)
    {
        arregloPedidos[i + 1] = arregloPedidos[i];
        i--;
    }
    arregloPedidos[i + 1] = A;
}

void ordenamientoFechaInsercion(stPedido nomArreglo[], int validos)
{
    int i = 0;
    while (i < validos - 1)
    {
        insertarDiaArreglo(nomArreglo, i, nomArreglo[i + 1]);
        i++;
    }
    i = 0;
    while (i < validos - 1)
    {
        insertarMesArreglo(nomArreglo, i, nomArreglo[i + 1]);
        i++;
    }
    i = 0;
    while (i < validos - 1)
    {
        insertarAnioArreglo(nomArreglo, i, nomArreglo[i + 1]);
        i++;
    }
}

int listarPedidosPorFecha(stPedido nomArreglo[dim])
{
    int validos = 0;

    validos = cargarArregloDePedidos(nomArreglo);
    ordenamientoFechaInsercion(nomArreglo, validos);

    return validos;
}