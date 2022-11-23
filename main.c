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
void frontApretarCero();
void frontElegirCliente(nodoArbolCliente *t);
void mostrarModificados(nodoArbolCliente *t);
void frontEliminarCliente(nodoArbolCliente **t);
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
	// frontModificarCliente(arbolito);
	frontEliminarCliente(&arbolito);

	mostrarModificados(arbolito);
	system("pause");
	guardarNodosModificadosArbol(arbolito);

	frontInit();
	system("pause");
	system("cls");

	frontMenuCliente();

	system("pause");
	system("cls");
	frontElegirCliente(arbolito);
	system("pause");

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
	printf("Menu principal\n");
	printf("1) Clientes\n");
	printf("2) Pedidos\n");
}

void frontApretarCero()
{
	printf("\n0) Volver atras\n");
}

void frontElegirCliente(nodoArbolCliente *t)
{
	listadoClientesArbol(t);
	printf("Ingrese el DNI del cliente que desea seleccionar: ");
}

void frontMenuCliente()
{
	printf("1) Mostrar listado resumido de clientes\n");
	printf("2) Mostrar informe completo de clientes\n");
	printf("3) Mostrar informacion de un cliente especifico\n");
	printf("4) Agregar cliente\n");
	printf("5) Modificar cliente\n");
	printf("6) Dar de baja a un cliente\n");
	printf("7) Guardar clientes\n");
	printf("8) Mostrar clientes inactivos\n");
	frontApretarCero();
}

void frontMenuPedidos()
{
	printf("1) Listar pedidos\n");
	printf("2) Agregar pedido\n");
	printf("3) Modificar pedido\n");
	printf("4) Anular pedido\n");
	printf("5) Mostrar pedidos inactivos\n");
	frontApretarCero();
}

void frontModificarCliente(nodoArbolCliente *t)
{
	// system("cls");
	listadoClientesArbol(t);
	printf("Introduzca el DNI del cliente que desea modificar: ");
	int dni = -1;
	fflush(stdin);
	scanf("%d", &dni);

	nodoArbolCliente *busqueda = buscarNodoArbolPorDni(t, dni);

	if (busqueda)
	{
		if (modificarCliente(&busqueda->dato) > 0)
		{
			busqueda->modificado = 1;
		}
	}
	else
	{
		printf("Cliente no encontrado.\n");
	}
}

void frontEliminarCliente(nodoArbolCliente **t)
{
	// system("cls");
	listadoClientesArbol(*t);
	printf("Introduzca el DNI del cliente que desea dar de baja: ");
	int dni = -1;
	fflush(stdin);
	scanf("%d", &dni);

	nodoArbolCliente *busqueda = buscarNodoArbolPorDni(*t, dni);

	if (busqueda)
	{
		bajaCliente(&busqueda->dato);
		*t = borrarNodoArbol(*t, dni);
	}
	else
	{
		printf("Cliente no encontrado.\n");
	}
}