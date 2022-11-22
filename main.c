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

int main()
{

	nodoArbolCliente *arbolito = inicArbol();
	stCliente arregloClientes[500];
	int validos = 0;
	validos = leerArchivoClientes(arregloClientes, 500);
	ordenarSeleccion(arregloClientes, validos);
	arbolito = array2arbol(arregloClientes, 0, validos - 1);

	leerArchivoPedidos(arbolito);
	nodoArbolCliente *buscado = buscarNodoArbolPorDni(arbolito, 30234987);

	reporteCompletoArbol(arbolito);
	system("pause");
	frontModificarCliente(arbolito);

	arbolito = borrarNodoArbol(arbolito, 38441203);

	inOrden(arbolito);

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

		arbol = agregarNodo(arbol, array[medio]);

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
			if (i < dimension)
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

void frontMenuCliente(nodoArbolCliente *t)
{
	printf("1) Mostrar listado resumido de clientes\n");
	printf("2) Mostrar informe completo de clientes\n");
	printf("3) Mostrar informacion de un cliente especifico\n");
	printf("4) Agregar cliente\n");
	printf("5) Modificar cliente\n");
	printf("6) Dar de baja a un cliente\n");
	printf("7) Guardar clientes");
	printf("8) Mostrar clientes inactivos");
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