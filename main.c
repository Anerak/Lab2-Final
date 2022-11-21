#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include ".\Headers\arbol.h"
#include ".\Headers\lista.h"

#include "./Headers/pedidos.h"
#include "./Headers/cliente.h"

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

	arbolito = array2arbol(arregloClientes, 0, validos - 1);

	leerArchivoPedidos(arbolito);

	//	inOrden(arbolito);

	nodoArbolCliente *buscado = NULL;
	int idPedido;
	printf("\n\nLos pedidos de Oriana son:\n");
	buscado = buscarNodoArbolPorDni(arbolito, 38441203);
	mostrarLista(buscado->pedidos);

	printf("\nIngrese el nro de ID del pedido a modificar:\n");
	scanf("%i", &idPedido);
	anularPedido(buscado->pedidos);

	mostrarUnPedido(buscado->pedidos->dato);

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
