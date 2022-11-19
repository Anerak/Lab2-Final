#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include ".\Headers\arbol.h"
#include ".\Headers\lista.h"

#include "./Headers/pedidos.h"
#include "./Headers/cliente.h"
void ordenarSeleccion(stCliente array[], int validos);
int buscarPosMenor(stCliente array[], int pos, int validos);

int leerArchivoClientes(stCliente array[], int dimension);
void leerArchivoPedidos(nodoArbolCliente *arbol);

/////////////
void insertarCliente(stCliente array[], int u, stCliente c);
void ordenarArray(stCliente array[], int validos);
nodoArbolCliente *array2arbol(stCliente array[], int base, int tope);

int main()
{

	nodoArbolCliente *arbolito = inicArbol();

	stCliente arregloClientes[500];
	int validos = 0;

	validos = leerArchivoClientes(arregloClientes, 500);
	ordenarSeleccion(arregloClientes, validos);
	// ordenarArray(arregloClientes, validos);

	for (int i = 0; i < validos; i++)
	{
		printf("ID: %d | DNI: %d | %s %s\n", arregloClientes[i].idCliente, arregloClientes[i].dni, arregloClientes[i].Nombre, arregloClientes[i].Apellido);
	}

	arbolito = array2arbol(arregloClientes, 0, validos - 1);
	/// ver que pasa si los datos son impares.

	leerArchivoPedidos(arbolito);

	inOrden(arbolito);

	system("pause");

	return 0;
}

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
