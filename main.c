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

	// arbolito = leerArchivoClientes(arbolito);

	leerArchivoPedidos(arbolito);

	// preOrden(arbolito);

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
			// TODO: Cambiar idCliente a DNI
			// nodoArbol = buscarNodoArbolPorDni(arbol, p.idCliente);
			// nodoArbol = buscarNodoArbolPorDni(arbol, p.idCliente);
			// nodoArbol = buscarNodoArbolPorIdTrucho(arbol, p.idCliente);
			// if (nodoArbol->pedidos)
			// {
			// 	nodoArbol->pedidos = inicLista();
			// }
			// nodoArbol->pedidos = agregarFinal(nodoArbol->pedidos, crearNodo(p));
		}
		fclose(a);
	}
}

/*
void leerArchivoPedidos(nodoArbolCliente *arbol)
{
	FILE *cl = fopen(ArchivoClientes, "r+b");
	stCliente c;
	stCliente cls[100];
	int i = 0;
	if (cl)
	{
		while (fread(&c, sizeof(stCliente), 1, cl) > 0)
		{
			cls[i] = c;
			i++;
		}
		fclose(cl);
	}
	else
	{
		return;
	}

	FILE *a = fopen(ArchivoPedidos, "r+b");
	stPedidoAux p;
	stPedido ps[100];
	// nodoArbolCliente *nodoArbol = NULL;
	int x = 0;
	if (a)
	{
		while (fread(&p, sizeof(stPedidoAux), 1, a) > 0)
		{
			for (int z = 0; z < 10; z++)
			{
				ps[x].arregloDePedidos[z] = p.arregloDePedidos[z];
			}
			ps[x].cantidadProductos = p.cantidadProductos;
			ps[x].costoPedido = p.costoPedido;
			ps[x].detalleEstado = p.detalleEstado;
			ps[x].estadoDelPedido = p.estadoDelPedido;
			ps[x].fecha = p.fecha;
			ps[x].idCliente = p.idCliente;
			ps[x].idPedido = p.idPedido;

			ps[x].dniCliente = retornaClientePorPos(buscarClientePorID(p.idCliente)).dni;
			x++;
			// TODO: Cambiar idCliente a DNI
			// nodoArbol = buscarNodoArbolPorDni(arbol, p.idCliente);
			// nodoArbol = buscarNodoArbolPorDni(arbol, p.idCliente);
			// nodoArbol = buscarNodoArbolPorIdTrucho(arbol, p.idCliente);
			// if (nodoArbol->pedidos)
			// {
			// 	nodoArbol->pedidos = inicLista();
			// }
			// nodoArbol->pedidos = agregarFinal(nodoArbol->pedidos, crearNodo(p));
		}
		fclose(a);
	}

	FILE *help = fopen("./npedidos.dat", "w+b");

	if (help)
	{
		for (int z = 0; z < x; z++)
		{
			fwrite(&ps[z], sizeof(stPedido), 1, help);
		}
	}
}
*/