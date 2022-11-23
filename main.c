#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include ".\Headers\arbol.h"

int IDPEDIDO = 0;
int IDCLIENTES = 0;

int leerArchivoClientes(stCliente array[], int dimension);
void leerArchivoPedidos(nodoArbolCliente *arbol);
nodoArbolCliente *array2arbol(stCliente array[], int base, int tope);
void frontModificarCliente(nodoArbolCliente *t);
void frontInit();
void frontMenuCliente();
void frontElegirCliente(nodoArbolCliente *t);
void mostrarModificados(nodoArbolCliente *t);
void frontEliminarCliente(nodoArbolCliente **t);
void frontPedidosInactivos (nodoArbolCliente *t);

int main()
{
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	nodoArbolCliente *arbolito = inicArbol();
	stCliente arregloClientes[500];
	int validos = 0;
	validos = leerArchivoClientes(arregloClientes, 500);
	ordenarSeleccion(arregloClientes, validos);
	arbolito = array2arbol(arregloClientes, 0, validos - 1);
	leerArchivoPedidos(arbolito);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - -


	/////////////////////////////variables general
    int primerMenu=0,opcionPrincipal=0,opcionClientes=0,opcionPedidos=0;
    int volverClientes=0, volverPedidos=0;

    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t B I E N V E N I D O \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t");
    system("Pause");

    do{

    system("cls");
    frontInit();
    scanf("%i",&primerMenu);

        switch(primerMenu)
        {
            case 1:

             do{

                frontMenuCliente();
                scanf("%i",&opcionClientes);

                switch(opcionClientes)
                    {
                        case 1:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Listado resumido:\n\n\n");
                            mostrarClientesAcotado(arbolito);
                            system("pause");
                            break;

                        case 2:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Listado completo :\n\n\n");
                            reporteCompletoArbol(arbolito);
                            system("pause");
                            break;

                        case 3:

                            system("cls");
                            int dniCliente=0;
                            nodoArbolCliente * encontrado=NULL;
                            printf("\n\n\n\n\t\t\t\t Informacion de cliente:\n");

                            do{
                                volverClientes=0;
                                frontElegirCliente(arbolito);
                                scanf("%i",&dniCliente);
                                encontrado=buscarNodoArbolPorDni(arbolito,dniCliente);

                                if(encontrado)
                                {
                                    system("cls");
                                    mostrarCliente(encontrado->dato);
                                    system("pause");
                                }
                                else{

                                    system("cls");
                                    printf("\n\n\t\tEl numero ingresado no corresponde a un DNI del listado\n\n\t\t");
                                    system("pause");
                                    }

                                printf("\n\n\t\tSi desea consultar otro cliente ingrese 1 o cualquier numero para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverClientes);

                            }while(volverClientes==1);
                          break;

                        case 4:

                            system("cls");
                            dniCliente=0;
                            printf("\n\n\n\n\t\t\t\t Alta cliente:\n\n\n");
                            arbolito=altaClienteArbol(arbolito,IDCLIENTES++);
                            printf("\n\n\n\t\t El cliente se guardo correctamente.\n\n\n\n\n\t\t");
                            system("pause");
                            break;

                        case 5:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Modificar cliente:\n\n\n");

                            do{
                                volverClientes=0;
                                frontModificarCliente(arbolito);
                                system("pause");
                                printf("\n\n\t\tSi desea modificar otro cliente ingrese 1 o cualquier tecla para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverClientes);
                            }while(volverClientes==1);
                            break;

                        case 6:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Dar de baja a un cliente:\n\n\n");

                            do{
                                volverClientes=0;
                                frontEliminarCliente(&arbolito);
                                system("pause");
                                printf("\n\n\t\tSi desea dar de baja otro cliente ingrese 1 o cualquier tecla para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverClientes);
                            }while(volverClientes==1);
                            break;

                        case 7:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Guardar clientes:\n\n\n");
                            system("pause");
                            guardarNodosModificadosArbol(arbolito);
                            printf("\n\n\t\t\t Datos guardados en el archivo\n\n\n\n\t\t\t\t ");
                            system("pause");
                            break;

                        case 8:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Listado de clientes inactivos:\n\n\n");
                            mostrarClientesInactivos();
                            system("pause");
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
                scanf("%i",&opcionClientes);
                }while(opcionClientes==1);
                break;


            case 2:

             do{

                frontMenuPedidos();
                fflush(stdin);
                scanf("%i",&opcionPedidos);

                switch(opcionPedidos)
                    {
                        case 1:

                            system("cls");
                            int dniCliente=0;
                            nodoArbolCliente * buscado=NULL;
                            printf("\n\n\n\n\t\t\t\t Listado de pedidos:\n\n\n");

                            do{
                                volverPedidos=0;
                                frontElegirCliente(arbolito);
                                fflush(stdin);
                                scanf("%i",&dniCliente);
                                buscado=buscarNodoArbolPorDni(arbolito,dniCliente);

                                if(buscado)
                                {
                                    printf("\n\n\t\t------------- Pedidos del cliente %s %s -------------\n\n",buscado->dato.Nombre,buscado->dato.Apellido);
                                    mostrarLista(buscado->pedidos);
                                }else{

                                    system("cls");
                                    printf("\n\n\t\tEl numero ingresado no corresponde a un DNI del listado\n\n\t\t");
                                    system("pause");
                               }

                                printf("\n\n\t\tSi desea consultar otro cliente ingrese 1 o cualquier numero para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverPedidos);
                            }while(volverPedidos==1);

                            system("pause");
                            break;

                        case 2:

                            system("cls");
                            dniCliente=0;
                            printf("\n\n\n\n\t\t\t\t Agregar pedido\n\n\n");

                            do{
                                volverPedidos=0;
                                frontElegirCliente(arbolito);
                                fflush(stdin);
                                scanf("%i",&dniCliente);
                                agregarPedido(arbolito,dniCliente,IDPEDIDO++);

                                printf("\n\n\t\tSi desea consultar otro cliente ingrese 1 o cualquier numero para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverPedidos);
                            }while(volverPedidos==1);

                            system("pause");
                            break;

                        case 3:

                            system("cls");
                            int idPedidos=0;
                            printf("\n\n\n\n\t\t\t\t 3 - Modificar Pedido Activo\n");

                            do{
                                volverPedidos=0;
                                modificarPedido(arbolito);
                                printf("\n\n\t\tPara modificar otro pedido ingrese 1 o cualquier tecla para volver al menu\n\n\t\t");
                                scanf("%i",&volverPedidos);
                            }while(volverPedidos==1);
                            break;

                        case 4:

                            system("cls");
                            idPedidos=0;
                            printf("\n\n\n\n\t\t\t\t Dar de baja a un pedido:\n\n\n");

                            do{
                                volverPedidos=0;
                                darBajaPedido(arbolito);
                                system("pause");
                                printf("\n\n\t\tSi desea dar de baja otro pedido ingrese 1 o cualquier tecla para volver al menu principal\n\t\t");
                                fflush(stdin);
                                scanf("%i",&volverPedidos);
                            }while(volverPedidos==1);


                        case 5:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Guardar pedidos:\n\n\n");
                            system("pause");
                            verificarModificaciones(arbolito);
                            printf("\n\n\t\t\t Datos guardados en el archivo\n\n\n\n\t\t\t\t ");
                            system("pause");
                            break;

                        case 6:

                            system("cls");
                            printf("\n\n\n\n\t\t\t\t Listado de pedidos inactivos:\n\n\n");
                            frontPedidosInactivos(arbolito);
                            system("pause");
                            break;

                        default:

                            system("cls");
                            printf("\n\n\t\tLa opcion ingresada es erronea.\n\n\t\t");
                            break;
                     }

                system("cls");
                printf("\n\n\n\n\t\tPara volver al MENU DE PEDIDOS ingrese 1 o cualquier tecla para salir:\n\n\t\t");
                fflush(stdin);
                scanf("%i",&opcionPedidos);

                }while(opcionPedidos==1);


                default:

                     printf("\n\n\t\tLa opcion ingresada es erronea.\n\n\t\t");
                     system("pause");
                     break;

        }
        system("cls");
        printf("\n\n\n\n\t\tPara volver al MENU PRINCIPAL ingrese 1 o cualquier tecla para salir:\n\n\t\t");
        fflush(stdin);
        scanf("%i",&opcionPrincipal);
        }while(opcionPrincipal==1);

	return 0;
}

nodoArbolCliente *array2arbol(stCliente array[], int base, int tope)
{
	int medio;

	nodoArbolCliente *arbol = NULL;

	if (!(base > tope))
	{
		medio = (base + tope) / 2;

		arbol = agregarNodoPorDni(arbol, array[medio]);

		arbol->izq = array2arbol(array, base, medio - 1);
		arbol->der = array2arbol(array, medio + 1, tope);
	}

	return arbol;
}

int leerArchivoClientes(stCliente array[], int dimension)
{
	FILE *a = fopen(ArchivoClientes, "r+b");
	stCliente c;
	int i = 0;

	if (a)
	{
		while (fread(&c, sizeof(stCliente), 1, a) > 0)
		{
			if (i < dimension && c.bajaCliente == 0)
			{
				if (IDCLIENTES < c.idCliente)
				{
					IDCLIENTES = c.idCliente;
				}

				array[i] = c;
				i++;
			}
		}
		fclose(a);
	}

	return i;
}

void mostrarModificados(nodoArbolCliente *t)
{
	if (t)
	{
		mostrarModificados(t->izq);
		if (t->modificado)
		{
			mostrarClienteResumido(t->dato);
		}
		mostrarModificados(t->der);
	}
}

void leerArchivoPedidos(nodoArbolCliente *arbol)
{
	FILE *a = fopen(ArchivoPedidos, "r+b");
	stPedido p;
	nodoArbolCliente *nodoArbol = NULL;
	if (a)
	{
		while (fread(&p, sizeof(stPedido), 1, a) > 0)
		{
			nodoArbol = buscarNodoArbolPorDni(arbol, p.dniCliente);
			if (nodoArbol)
			{
				if (IDPEDIDO < p.idPedido)
				{
					IDPEDIDO = p.idPedido;
				}

				if (!nodoArbol->pedidos)
				{
					nodoArbol->pedidos = inicLista();
				}
				nodoArbol->pedidos = insertarPedido(nodoArbol->pedidos, crearNodo(p));
			}
		}
		fclose(a);
	}
}

void frontInit()
{
    system("cls");
	printf("\n\n\n\n\t\t\t\tMenu principal\n");
	printf("\n\n\t\t\t 1) Clientes");
	printf("\n\n\t\t\t 2) Pedidos\n\n\t\t\t\t");
}

void frontElegirCliente(nodoArbolCliente *t)
{
	mostrarClientesAcotado(t);
	printf("\n\n\t\t\tIngrese el DNI del cliente que desea seleccionar:\n\t\t");
}

void frontMenuCliente()
{
    system("cls");
    printf("\n\n\n\n\t\t\t\t Menu Clientes \n");
	printf("\n\n\t\t\t 1) Mostrar listado resumido de clientes");
	printf("\n\n\t\t\t 2) Mostrar informe completo de clientes");
	printf("\n\n\t\t\t 3) Mostrar informacion de un cliente especifico");
	printf("\n\n\t\t\t 4) Agregar cliente");
	printf("\n\n\t\t\t 5) Modificar cliente");
	printf("\n\n\t\t\t 6) Dar de baja a un cliente");
	printf("\n\n\t\t\t 7) Guardar clientes");
	printf("\n\n\t\t\t 8) Mostrar clientes inactivos");
}

void frontMenuPedidos()
{
    system("cls");
    printf("\n\n\n\n\t\t\t\t Menu Pedidos \n");
	printf("\n\n\t\t\t 1) Listar pedidos por cliente");
	printf("\n\n\t\t\t 2) Agregar pedido");
	printf("\n\n\t\t\t 3) Modificar pedido");
	printf("\n\n\t\t\t 4) Anular pedido");
	printf("\n\n\t\t\t 5) Guardar clientes");
	printf("\n\n\t\t\t 6) Mostrar pedidos inactivos");
}

void frontModificarCliente(nodoArbolCliente *t)
{
	mostrarClientesAcotado(t);
	printf("\n\n\t\tIntroduzca el DNI del cliente que desea modificar:\n\t\t");
	int dni = -1;
	fflush(stdin);
	scanf("%d", &dni);

	nodoArbolCliente *busqueda = buscarNodoArbolPorDni(t, dni);

	if (busqueda)
	{
		if (modificarCliente(&busqueda->dato) > 0)
		{
			busqueda->modificado = 1;
			printf("\n\n\t\tEl cliente se modifico con exito\n\n\t");
		}
	}
	else
	{
		printf("\n\n\t\tCliente no encontrado.\n\n\n\n");
	}
}

void frontEliminarCliente(nodoArbolCliente **t)
{
	mostrarClientesAcotado(*t);
	printf("\n\n\t\tIntroduzca el DNI del cliente que desea dar de baja:\n\t\t");
	int dni = -1;
	fflush(stdin);
	scanf("%d", &dni);

	nodoArbolCliente *busqueda = buscarNodoArbolPorDni(*t, dni);

	if (busqueda)
	{
		bajaCliente(&busqueda->dato);
		*t = borrarNodoArbol(*t, dni);
		printf("\n\n\t\tSe dio de baja correctamente en cliente .\n\n\n\n");
	}
	else
	{
		printf("\n\n\t\tCliente no encontrado.\n\n\n\n");
	}
}

void frontPedidosInactivos (nodoArbolCliente *t)
{
	mostrarClientesAcotado(t);
	printf("\n\n\t\tIntroduzca el DNI del cliente que desea consultar:\n\t\t");
	int dni = -1;
	fflush(stdin);
	scanf("%d", &dni);
    mostrarPedidosInactivos(dni);
}


