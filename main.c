#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "./Headers/pedidos.h"
#include "./Headers/cliente.h"

/////////////////////////////////////////////CONSTANTES///////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////ESTRUCTURAS//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /////////////////////////////variables general
    int primerMenu = 0, opcionPrincipal = 0, opcionClientes = 0, opcionPedidos = 0;

    ////////////////////////////variables para clientes

    stCliente AuxC;
    int opcionCargaC = 0, intAuxC = 0, opcionAnularC = 0, validosListarC = 0;
    long int dniAux = 0;
    char auxApellido[dim];

    stCliente listarClientes[dim];
    stCliente insercionApellido[dim];
    stCliente listarClientes10[dim];

    ///////////////////////////variables para pedidos

    int intAuxP = 0, opcionCargaP = 0, idPedido = 0, opcionAnularP = 0, validosListarP = 0, idAuxPedidos = 0;

    stPedido listarPedidos[dim];

    stPedido AuxP;

    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t B I E N V E N I D O \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t");
    system("Pause");

    do
    {

        system("cls");
        printf("\n\n\n\n\t\t\t\tIngrese el numero de menu al que desea ingresar:\n\n\n");
        printf("\n\n\t\t\t 1 - Clientes\n\n\t\t\t 2 - Pedidos\n\n\t\t\t");
        scanf("%i", &primerMenu);

        switch (primerMenu)
        {
        case 1:

            do
            {

                system("cls");
                printf("\n\n\n\n\t\t\t\tIngrese que opcion desea realizar:\n\n");
                printf("\n\n\t\t\t 1 - Alta de nuevo Cliente");
                printf("\n\n\t\t\t 2 - Dar de baja Cliente");
                printf("\n\n\t\t\t 3 - Modificar Cliente Activo");
                printf("\n\n\t\t\t 4 - Listar clientes");
                printf("\n\n\t\t\t 5 - Consultar un cliente\n\n\t\t\t");
                scanf("%i", &opcionClientes);

                switch (opcionClientes)
                {
                case 1:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 1 - Alta de nuevo Cliente:\n\n\n");

                    do
                    {
                        intAuxC = altaDeCliente(AuxC);
                        opcionCargaC = 0;

                        if (intAuxC == 0)
                        {
                            printf("\n\n\t\tEl cliente se cargo correctamente.\n\n\n\t\t");
                        }

                        printf("\n\t\tSi desea ingresar otro cliente ingrese 1 o cualquier tecla para salir.\n\n\n\t\t");
                        fflush(stdin);
                        scanf("%i", &opcionCargaC);
                    } while (opcionCargaC == 1);

                    system("pause");

                    break;

                case 2:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 2 - Dar de baja Cliente:\n\n\n");

                    do
                    {
                        dniAux = 0, intAuxC = 0, opcionAnularC = 0;
                        printf("\n\n\t\tIngrese el DNI del cliente que desea dar de baja:\n\n\n\t\t");
                        scanf("%lu", &dniAux);
                        intAuxC = darBajarCliente(dniAux);

                        if (intAuxC == -1)
                        {
                            printf("\n\n\t\tEl nro ingresado no corresponde al DNI de un cliente.\n\n\t\tIngrese 1 para volver a ingresar el ID del pedido o cualquier tecla para volver al menu:\n\n\t\t");
                            fflush(stdin);
                            scanf("%i", &opcionAnularC);
                        }
                        else
                        {
                            printf("\n\n\t\tEl cliente fue dado de baja.\n\n\n\t\t");
                            opcionAnularP = 0;
                        }
                    } while (opcionAnularP == 1);

                    break;

                case 3:

                    system("cls");
                    intAuxC = 0;
                    printf("\n\n\n\n\t\t\t\t 3 - Modificar Cliente:\n");
                    printf("\n\n\t\tIngrese el tipo de dato para buscar al cliente:\n");
                    printf("\n\n\t\t1 - Buscar por DNI ");
                    printf("\n\n\t\t2 - Buscar por Apellido\n\n\t\t");
                    scanf("%i", &intAuxC);

                    if (intAuxC == 1)
                    {
                        system("cls");
                        printf("\n\n\t\tIngrese el nro de DNI del cliente:\n\n\t\t");
                        scanf("%lu", &dniAux);
                        AuxC = modificacionClientePorDni(dniAux);
                        printf("\n\n\t\tLos nuevos datos del cliente son:\n\n\t\t");
                        mostarCliente(AuxC);
                    }
                    else
                    {

                        system("cls");
                        printf("\n\n\t\tIngrese el apellido del cliente:\n\n\t\t");
                        fflush(stdin);
                        gets(auxApellido);
                        AuxC = modificarClientePorApellido(auxApellido);
                        printf("\n\n\t\tLos nuevos datos del cliente son:\n\n\t\t");
                        mostarCliente(AuxC);
                    }

                    system("pause");
                    break;

                case 4:

                    system("cls");
                    intAuxC = 0, validosListarC = 0;
                    printf("\n\n\n\n\t\t\t\t 4 - Listar Clientes:\n\n\n");
                    printf("\n\n\t\tIngrese el tipo de dato para listar:\n");
                    printf("\n\n\t\t1 - Listar por Apellido");
                    printf("\n\n\t\t2 - Listar por ID \n\n\t\t");
                    scanf("%i", &intAuxC);

                    if (intAuxC == 1)
                    {
                        system("cls");
                        printf("\n\n\t\tLos clientes activos ordenados por apellido:\n\n");
                        validosListarC = listarClientesInsercion(insercionApellido);
                        mostrarArregloDeClientes(insercionApellido, validosListarC);
                        system("pause");
                    }
                    else
                    {

                        system("cls");
                        printf("\n\n\t\tLos clientes activos ordenados por numero de ID:\n\n");
                        validosListarC = listarClientesSeleccion(listarClientes);
                        mostrarArregloDeClientes(listarClientes, validosListarC);
                        system("pause");
                    }
                    printf("\n\n\t\t");
                    break;

                case 5:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 5 - Consultar un cliente:\n\n\n");

                    do
                    {
                        dniAux = 0, intAuxC = 0, opcionAnularC = 0;
                        printf("\n\n\t\tIngrese el DNI del cliente que desea ver:\n\n\n\t\t");
                        scanf("%lu", &dniAux);
                        intAuxC = buscarClientePorDNI(dniAux);

                        if (intAuxC == -1)
                        {
                            printf("\n\n\t\tEl nro ingresado no corresponde al DNI de un cliente.\n\n\t\tIngrese 1 para volver a ingresar el DNI del cliente o cualquier tecla para volver al menu:\n\n\t\t");
                            fflush(stdin);
                            scanf("%i", &opcionAnularC);
                        }
                        else
                        {

                            printf("\n\n\t\tEl cliente con DNI %lu es:\n\n\n\t\t", dniAux);
                            AuxC = retornaClientePorPos(intAuxC);
                            mostarCliente(AuxC);
                            system("pause");
                        }
                    } while (opcionAnularP == 1);

                    break;

                default:

                    system("cls");
                    printf("\n\n\t\tLa opcion ingresada es erronea.\n\n\n\t\t");
                    system("pause");
                    break;
                }

                system("cls");
                printf("\n\n\t\tPara volver al MENU DE CLIENTES ingrese 1 o cualquier tecla para salir:\n\n\t\t");
                fflush(stdin);
                scanf("%i", &opcionClientes);
            } while (opcionClientes == 1);

            break;

        case 2:

            do
            {

                system("cls");
                printf("\n\n\n\n\t\t\t\tIngrese que opcion desea realizar:\n\n\n\n");
                printf("\n\n\t\t 1 - Alta de nuevo Pedido");
                printf("\n\n\t\t 2 - Dar de baja Pedido");
                printf("\n\n\t\t 3 - Modificar Pedido Activo");
                printf("\n\n\t\t 4 - Listados y Estadisticas");
                printf("\n\n\t\t 5 - Consultar un pedido\n\n\t\t");
                scanf("%i", &opcionPedidos);

                switch (opcionPedidos)
                {
                case 1:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 1 - Alta de nuevo Pedido:\n\n");

                    do
                    {
                        opcionCargaP = 0;
                        AuxP = cargarPedido();
                        printf("\n\n\t\tDatos del pedido ingresado:\n\n");
                        mostrarUnPedido(AuxP);

                        printf("\n\n\t\tEl pedido se cargo correctamente.\n\n\t\tSi desea ingresar otro pedido ingrese 1 o cualquier tecla para salir.\n\n\t\t");
                        fflush(stdin);
                        scanf("%i", &opcionCargaP);
                    } while (opcionCargaP == 1);

                    system("pause");

                    break;

                case 2:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 2 - Dar de baja Pedido:\n\n\n");

                    do
                    {
                        printf("\n\n\t\tIngrese el ID del pedido que desea anular:\n\n\t\t");
                        scanf("%i", &idPedido);
                        intAuxP = anularPedido(idPedido);

                        if (intAuxP == -1)
                        {
                            printf("\n\n\t\tEl nro ingresado no corresponde a un pedido.\n\n\t\tIngrese 1 para volver a ingresar el ID del pedido o cualquier tecla para volver al menu:\n\n\t\t");
                            scanf("%i", &opcionAnularP);
                        }
                        else
                        {
                            printf("\n\n\t\tEl pedido fue anulado.\n\n\t\t");
                            opcionAnularP = 0;
                        }
                    } while (opcionAnularP == 1);
                    system("pause");

                    break;

                case 3:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 3 - Modificar Pedido Activo\n");

                    do
                    {
                        intAuxP = 0;
                        idAuxPedidos = 0;

                        system("cls");
                        printf("\n\n\t\tIngrese el ID del pedido a buscar:\n\n\t\t");
                        scanf("%i", &idAuxPedidos);

                        if ((buscarIdPedido(idAuxPedidos)) != -1)
                        {
                            modificarPedidoPorId(idAuxPedidos);
                            printf("\n\n\t\tEl pedido fue modificado.");
                            system("pause");
                        }
                        else
                        {
                            printf("\n\n\t\tEl nro ingresado no corresponde a un pedido.");
                            system("pause");
                        }

                        printf("\n\n\t\tPara modificar otro pedido ingrese 1 o cualquier tecla para volver al menu\n\n\t\t");
                        scanf("%i", &intAuxP);
                    } while (intAuxP == 1);

                    break;

                case 4:

                    system("cls");
                    intAuxP = 0;
                    printf("\n\n\n\n\t\t\t\t Listados y Estadisticas\n");
                    printf("\n\n\t\tIndique la opcion a ejecutar:\n\n\t\t");
                    printf("\n\n\t\t 1 - Listar pedidos por orden de fecha");
                    printf("\n\n\t\t 2 - Listar pedidos por cliente");
                    printf("\n\n\t\t 3 - Listar TOP TEN mejores clientes");
                    printf("\n\n\t\t 4 - Busqueda del peor cliente\n\n\t\t");
                    scanf("%i", &intAuxP);

                    switch (intAuxP)
                    {

                    case 1:

                        printf("\n\n\n\n\t\t\t\t  1 - Listar pedidos por orden de fecha\n");
                        printf("\n\n\t\t A continuacion la lista de pedidos ordenada por fecha (del mas antiguo al mas reciente):\n");
                        validosListarP = listarPedidosPorFecha(listarPedidos);
                        mostrarArregloPedidos(listarPedidos, validosListarP);
                        printf("\n\n\t\t");
                        system("pause");
                        break;

                    case 2:

                        system("cls");
                        printf("\n\n\n\n\t\t\t\t  2 - Listar pedidos por cliente\n");

                        do
                        {
                            idAuxPedidos = 0;
                            intAuxP = 0;

                            printf("\n\n\t\t Ingrese el numero de ID del cliente a buscar:\n\n\t\t");
                            scanf("%i", &idAuxPedidos);

                            if ((buscarClientePorID(idAuxPedidos)) != -1)
                            {
                                printf("\n\n\t\tLos pedidos realizados por el cliente ID: %i  son:\n\n", idAuxPedidos);
                                mostrarPedidosPorCliente(idAuxPedidos);
                            }
                            else
                            {

                                printf("\n\n\t\tEl ID ingresado no crresponde a un cliente.\n\n\t\t");
                            }

                            system("pause");
                            printf("\n\n\t\tPara listar los pedidos de otro cliente ingrese 1 o cualquier tecla para volver al menu\n\n\t\t");
                            scanf("%i", &intAuxP);
                        } while (intAuxP == 1);

                        printf("\n\n\t\t");
                        system("pause");
                        break;

                    case 3:

                        printf("\n\n\n\n\t\t\t\t  3 - Listar TOP TEN mejores clientes\n\n");
                        printf("\n\n\t\tA continuacion los mejores 10 clientes:\n\n");
                        topTenMejoresClientes(listarClientes10);
                        mostrarArregloDeClientes(listarClientes10, 10);
                        printf("\n\n\t\t");
                        system("pause");
                        break;

                    case 4:

                        printf("\n\n\n\n\t\t\t\t  4 - Busqueda del peor cliente\n\n");
                        printf("\n\n\t\tEl cliente con menos compras a la fecha es:\n\n\t\t");
                        AuxC = peorCliente();
                        mostarCliente(AuxC);
                        printf("\n\n\t\t");
                        system("pause");
                        break;

                    default:

                        system("cls");
                        printf("\n\n\n\n\t\t\t\t La opcion ingresada es incorrecta.\n\n\n\n\t\t\t\t ");
                        system("pause");
                        break;
                    }
                    printf("\n\n\t\t");
                    break;

                case 5:

                    system("cls");
                    printf("\n\n\n\n\t\t\t\t 5 - Consultar un pedido:\n\n\n");

                    do
                    {
                        idPedido = 0, intAuxP = 0, opcionAnularP = 0;
                        printf("\n\n\t\tIngrese el ID del pedido que desea ver:\n\n\n\t\t");
                        scanf("%i", &idPedido);
                        intAuxP = buscarIdPedido(idPedido);

                        if (intAuxC == -1)
                        {
                            printf("\n\n\t\tEl nro ingresado no corresponde al ID de un pedido.\n\n\t\tIngrese 1 para volver a ingresar el ID del pedido o cualquier tecla para volver al menu:\n\n\t\t");
                            fflush(stdin);
                            scanf("%i", &opcionAnularP);
                        }
                        else
                        {

                            printf("\n\n\t\tEl pedido con ID %i es:\n\n\n\t\t", idPedido);
                            AuxP = retornaPedidoPorPos(intAuxP);
                            mostrarUnPedido(AuxP);
                            ;
                            system("pause");
                        }
                    } while (opcionAnularP == 1);

                    break;

                default:

                    system("cls");
                    printf("\n\n\t\tLa opcion ingresada es erronea.\n\n\t\t");
                    break;
                }

                system("cls");
                printf("\n\n\n\n\t\tPara volver al MENU DE PEDIDOS ingrese 1 o cualquier tecla para salir:\n\n\t\t");
                fflush(stdin);
                scanf("%i", &opcionPedidos);

            } while (opcionPedidos == 1);

        default:

            printf("\n\n\t\tLa opcion ingresada es erronea.\n\n\t\t");
            system("pause");
            break;
        }
        system("cls");
        printf("\n\n\n\n\t\tPara volver al MENU PRINCIPAL ingrese 1 o cualquier tecla para salir:\n\n\t\t");
        fflush(stdin);
        scanf("%i", &opcionPrincipal);

    } while (opcionPrincipal == 1);

    return 0;
}

///////////////////////////////////////LISTADOS Y ESTADISTICAS////////////////////////////////////////////////////////////////

///////////////////////////////////////////LISTADOS PEDIDOS//////////////////////////////////////////////////////////////////
