#include "ListaPeones.h"
#include <iostream>
//#include "Peon.h"
//#include "Ficha.h"

ListaPeones::ListaPeones()
{
	num = 0;
	for (int i = 0; i < MAX_PEONES; i++)
		lista_peon[i] = 0;

}

bool ListaPeones::agregar(Peon* p)
{
	if (num < MAX_PEONES)
		lista_peon[num++] = p;
	else
		return false;
	return true;

}

void ListaPeones::dibuja()
{
	for (int i = 0;i < num;i++)
		lista_peon[i]->Dibuja();

}

void ListaPeones::mueve()
{
}

void ListaPeones::inicializa()
{
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if ((i + j) % 2 != 0)
			{
				if (i < 3)
				{
					Peon* aux = new Peon;
					aux->SetPos(i, j);
					aux->SetRadio(40);
					aux->SetColor(ROJO);
					agregar(aux);
				}
				if (i > 4)
				{
					Peon* aux = new Peon;
					aux->SetPos(i, j);
					aux->SetRadio(40);
					aux->SetColor(BLANCO);
					agregar(aux);
				}

			}
		}
	}
}

Peon* ListaPeones::buscar_lista_peon(int x, int y)
{
	for (int i = 0; i < num;i++)
	{
		if ((lista_peon[i]->GetPosX() == x) && (lista_peon[i]->GetPosY() == y))
			return lista_peon[i];
	}
	return NULL;
}


