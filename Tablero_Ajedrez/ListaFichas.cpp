#include "ListaFichas.h"

bool ListaFichas::agregar(Ficha* p)
{
	if (num < MAX_FICHAS)
		lista_fichas[num++] = p;
	else
		return false;
	return true;
}

void ListaFichas::dibuja()
{
	for (int i = 0; i < num; i++)
		lista_fichas[i]->Dibuja();
}

void ListaFichas::inicializa()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 != 0)
			{
				if (i < 3)
				{
					Ficha* aux = new Dama;
					aux->SetPos(i, j);
					aux->SetRadio(40);
					aux->SetColor(ROJO);
					agregar(aux);
				}
				if (i > 4)
				{
					Ficha* aux = new Peon;
					aux->SetPos(i, j);
					aux->SetRadio(40);
					aux->SetColor(BLANCO);
					agregar(aux);
				}

			}
		}
	}
}

Ficha* ListaFichas::buscar_lista_ficha(int x, int y)
{
	for (int i = 0; i < num; i++)
	{
		if ((lista_fichas[i]->GetPosX() == x) && (lista_fichas[i]->GetPosY() == y))
			return lista_fichas[i];
	}
	return NULL;
}

ListaFichas::ListaFichas()
{
	num = 0;
	for (int i = 0; i < MAX_FICHAS; i++)
		lista_fichas[i] = 0;
}

