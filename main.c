#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "./Headers/arbol.h"
#include "./Headers/lista.h"

#include "./Headers/pedidos.h"
#include "./Headers/cliente.h"

nodoArbolCliente *leerArchivoClientes(nodoArbolCliente *arbol);
void leerArchivoPedidos(nodoArbolCliente *arbol);

int main()
{

	nodoArbolCliente *arbolito = inicArbol();

	arbolito = leerArchivoClientes(arbolito);

	leerArchivoPedidos(arbolito);

	preOrden(arbolito);

	system("pause");

	return 0;
}

nodoArbolCliente *leerArchivoClientes(nodoArbolCliente *arbol)
{
	FILE *a = fopen(ArchivoClientes, "r+b");
	stCliente c;
	if (a)
	{
		while (fread(&c, sizeof(stCliente), 1, a) > 0)
		{
			arbol = agregarNodoPorDni(arbol, c);
		}
		fclose(a);
	}

	return arbol;
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
			if (!nodoArbol->pedidos)
			{
				nodoArbol->pedidos = inicLista();
			}
			nodoArbol->pedidos = insertarPedido(nodoArbol->pedidos, crearNodo(p));
		}
		fclose(a);
	}
}