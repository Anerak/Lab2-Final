#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Headers/fecha.h"
#include "./Headers/pedidos.h"
#include "./Headers/arbol.h"

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
        printf("\n\n\t\t          Ingrese el anio:\n\t\t\t\t");
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

stPedido generarPedido() // carga un pedido, llama a las funciones anteriores
{
    stPedido A;
    stProducto P;
    stFecha F;
    stCliente C;
    stProducto arregloProd[30];

    int i = 0, idPedido = 0, validarIDcliente = 0, opcionCliente=1;
    float costo = 0;
    char opcion = 's';
    char validarNumero[dim];

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
                printf("\n\n\t\tEl numero ingresado no corresponde a un cliente guardado.");
                printf("\n\t\tSi desea volver a ingresar el numero ingrese 1.");
                printf("\n\t\tPara cargar un nuevo cliente ingrese 2.\n\n\t\t");
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

void mostrarDetalleProducto(stProducto A)
{
    printf("\n\n\t\t     Descripcion del pedido:\n");
    printf("\t\t             Producto:  %s \n", A.Producto);
    printf("\t\t             Modelo:    %s \n", A.Modelo);
    printf("\t\t             Cantidad:  %i \n", A.cantidad);
    printf("\t\t             Precio:  $ %.2f \n", A.precio);
}


void mostrarUnPedido(stPedido A)
{
    printf("-----------ID: %i | DNI: -----------%i\n", A.idPedido, A.dniCliente);
    mostrarFecha(A.fecha);
    return;
    printf("\n\n\t\t--------------------------------------------\n");
    printf("\n\t\t    ID de Pedido:     %i ", A.idPedido);
    printf("\n\t\t    ID de Cliente:    %i ", A.idCliente);
    printf("\n\t\t    DNI de Cliente:   %i ", A.dniCliente);
    printf("\n\t\t    Fecha del pedido: ");
    mostrarFecha(A.fecha);
    mostrarArregloProducto(A.arregloDePedidos, A.cantidadProductos);
    printf("\n\t\t    Costo de pedido: $ %i \n", A.costoPedido);
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


///////////////////////////////////////LISTADOS Y ESTADISTICAS////////////////////////////////////////////////////////////////

/////////////////////////////////////////MODIFICAR PEDIDOS////////////////////////////////////////////////////////////////////

void modificarPedidoPorId(nodoArbolCliente * arbolito, int idpedido) // Modificar pedido por ID
{
    stPedido auxPedido;
    nodoPedido* modificado=NULL;
    char opcion = 's';

    if (arbolito)
    {
        modificado = buscarPedidoSinDni(arbolito,idpedido);

        if (modificado)
        {
            if (modificado.estadoDelPedido == 1)
            {
                modificarUnpedido(auxPedido); // retorna el pedido leido, ya modificado por la funcion
            }
            else
            {

                printf("\n\n\t\t El pedido se encuentra en estado anulado\n");
            }
    }
}

stFecha modificarFechaPedido(nodoPedido * pedido) // Auxiliar - Modifica fecha
{
    char seguir = 's';
    int opcion=0;
    char auxNumero[10];

    do{

        printf("\n\n              Modificar Fecha  \n\n");
        printf("\t\tIngrese:");
        printf("\n\t\t\t1 - Para modificar el dia");
        printf("\n\t\t\t2 - Para modificar el mes");
        printf("\n\t\t\t3 - Para modificar el anio");
        scanf("%i",&opcion);

        if(opcion ==1)
        {
            do
            {
                printf("\n\n\t\tIngrese el dia:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            pedido.fecha.dia = atoi(auxNumero);

        }else if (opcion==2){

            do
            {
                printf("\n\n\t\tIngrese mes:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            pedido.fecha.Mes = atoi(auxNumero);

        }else if(opcion ==3){

            do
            {
                printf("\n\n\t\tIngrese el anio:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
            pedido.fecha.anio = atoi(auxNumero);
        }

        printf("Si desea modificar otro dato de la fecha ingrese s o cualquier tecla para finalizar la modificacion:\n\t\t");
        fflush(stdin);
        gets(seguir);
    }while (seguir=='s');

        return pedido.fecha;
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

nodoPedido* modificarUnpedido(nodoPedido* pedido)
{
    int auxIdcliente = pedido.idCliente, i = 0;
    float costo = 0;
    char seguir = 's', opcion = 's';
    char auxPalabra[40], auxNumero[10];

    stProducto P;

    printf("\n\n\t\tIngrese S para editar id cliente, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        float costoP = pedido.costoPedido; // esta funcion descuenta la compra de el id que ya cargo y quiere cambiar
        costoP = costoP * (-1);
        cargarTotalGastadoYcompra(costoP, pedido.idCliente, -1);

        do
        {
            do
            {
                printf("\n\n\t\tIngrese el ID del cliente:\n\t\t");
                fflush(stdin);
                gets(auxNumero);
            } while ((validarNumero(auxNumero)) != 0);
        } while ((validarCliente(atoi(auxNumero))) != -1);
        pedido.idCliente = atoi(auxNumero);
    }

    printf("\n\n\t\tPara resetear todos los productos y cargar nuevos ingrese S, u otra letra para cancelar.\n\t\t");
    fflush(stdin);
    scanf("%c", &seguir);

    if (seguir == 's' || seguir == 'S')
    {
        if (auxIdcliente == pedido.idCliente) // mismo cliente mismo idcliente
        {
            float costoP = pedido.costoPedido; // esta funcion descuenta la compra que ahora se quiere modificar
            costoP = costoP * (-1);
            cargarTotalGastadoYcompra(costoP, pedido.idCliente, -1 /* representa e*/);
        }

        while (opcion == 's' && i < 30)
        {
            P = cargarDetalleProducto(P);
            pedido.arregloDePedidos[i] = P;
            i++;
            costo += P.precioFinal;

            printf("\n\n\t\tDesea agregar otro producto al pedido? \n\t\t (S para adicionar otro producto, n para salir)\n\t\t");
            fflush(stdin);
            scanf("%c", &opcion);
        }

        pedido.cantidadProductos = i;
        pedido.costoPedido = costo;
        pedido.estadoDelPedido = 1;
        pedido.detalleEstado = 's';
        cargarTotalGastadoYcompra(costo, pedido.idCliente, 1);
    }
    else // si anteriormente modifico reseteo los pedidos no entra en este campo ya fue modificado en el if anterior
    {
        printf("\n\n\t\tPara modificar los productos del arreglo ingrese S, u otra letra para cancelar:\n\t\t");
        fflush(stdin);
        scanf("%c", &seguir);
        if (seguir == 's' || seguir == 'S')
        {
            if (auxIdcliente == pedido.idCliente) // mismo cliente mismo idcliente
            {
                float costoP = pedido.costoPedido; // esta funcion descuenta la compra que ahora se quiere modificar
                costoP = costoP * (-1);
                cargarTotalGastadoYcompra(costoP, pedido.idCliente, -1 /* representa e*/);
            }

            float nuevoCosto = modificarArregloProductos(pedido.arregloDePedidos, pedido.cantidadProductos);
            pedido.costoPedido = nuevoCosto;
            cargarTotalGastadoYcompra(nuevoCosto, pedido.idCliente, 1);
        }
        else
        {
            if (pedido.idCliente != auxIdcliente)
            {
                cargarTotalGastadoYcompra(pedido.costoPedido, pedido.idCliente, 1);
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
