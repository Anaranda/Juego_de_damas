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
					Ficha* aux = new Peon;
					aux->SetPos(i, j);
					aux->SetRadio(40.0f);
					aux->SetColor(ROJO);
					agregar(aux);
				}
				if (i > 4)
				{
					Ficha* aux = new Peon;
					aux->SetPos(i, j);
					aux->SetRadio(40.0f);
					aux->SetColor(BLANCO);
					agregar(aux);
				}
			}
		}
	}
}

void ListaFichas::eliminar_fichas()
{
	for (int i=0; i<num;i++)
	{
		lista_fichas[i]->BorraFicha();
	}
	num = 0;
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

bool ListaFichas::buscar_lista_color(Color color)
{
	for (int i = 0; i < num; i++)
	{
		if ((lista_fichas[i]->GetColor() == color) || lista_fichas[i]->GetColor() == VERDE)
			return true;
	}
	return false;
}

void ListaFichas::eliminar(int x, int y)
{
	int index = 0;
	for (int i = 0; i < num; i++)
	{
		if ((lista_fichas[i]->GetPosX() == x) && (lista_fichas[i]->GetPosY() == y))
		{
			index = i;
			lista_fichas[i]->BorraFicha();
			num--;
			for (int i = index; i < num; i++)
				lista_fichas[i] = lista_fichas[i + 1];
		}
	}
}

Ficha* ListaFichas::convertir_a_dama(int x, int y)
{
	Ficha* aux = new Dama;
	aux->SetPos(x, y);
	aux->SetRadio(40);
	aux->SetColor(buscar_lista_ficha(x, y)->GetColor());
	eliminar(x, y);
	agregar(aux);
	return aux;
}

 bool ListaFichas::posible_comida(Color turno) //comprueba si una ficha puede comer 1 primera vez
{
	Ficha* mificha;
	inicializarPosibleComida();

	for (int i = 0; i < num; i++)
	{
		mificha = lista_fichas[i];//mificha contiene la ficha que queremos ver si puede comer a sus adyacentes 
		if (lista_fichas[i]->GetColor() == turno || lista_fichas[i]->GetColor()==VERDE) //lo de verde es por si está seleccionada
		{
			if (lista_fichas[i]->GetTipo() == PEON)
			{
				if (turno == ROJO)
				{
					if (buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() - 1) != NULL && buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() - 1)->GetColor() == BLANCO) //comprobamos que en su adyacente 1 hay ficha que comer
					{
						if (buscar_lista_ficha(mificha->GetPosX() + 2, mificha->GetPosY() - 2) == NULL && dentro_de_tablero(mificha->GetPosX() + 2, mificha->GetPosY() - 2))
						{
							agregarFichaPosibleComida(lista_fichas[i]);
						}
					}
					if (buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() + 1) != NULL && buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() + 1)->GetColor() == BLANCO ) //comprobamos que en su adyacente 1 hay ficha que comer
					{
						if (buscar_lista_ficha(mificha->GetPosX() + 2, mificha->GetPosY() + 2) == NULL && dentro_de_tablero(mificha->GetPosX() + 2, mificha->GetPosY() + 2))
						{
							agregarFichaPosibleComida(lista_fichas[i]);
						}
					}
				}
				else if (turno == BLANCO)
				{
					mificha = lista_fichas[i];//mificha contiene la ficha que queremos ver si puede comer a sus adyacentes 
					if (buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() - 1) != NULL && buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() - 1)->GetColor() == ROJO) //comprobamos que en su adyacente 1 hay ficha que comer
					{
						if (buscar_lista_ficha(mificha->GetPosX() - 2, mificha->GetPosY() - 2) == NULL && dentro_de_tablero(mificha->GetPosX() - 2, mificha->GetPosY() - 2))
						{
							agregarFichaPosibleComida(lista_fichas[i]);
						}
					}
					if (buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() + 1) != NULL && buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() + 1)->GetColor() == ROJO) //comprobamos que en su adyacente 1 hay ficha que comer
					{
						if (buscar_lista_ficha(mificha->GetPosX() - 2, mificha->GetPosY() + 2) == NULL && dentro_de_tablero(mificha->GetPosX() - 2, mificha->GetPosY() + 2))
						{
							agregarFichaPosibleComida(lista_fichas[i]);
						}
					}
				}
			}
			else if (lista_fichas[i]->GetTipo() == DAMA)
			{
				if (buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() - 1) != NULL && buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() - 1)->GetColor() != turno ) //comprobamos que en su adyacente 1 hay ficha que comer
				{
					if (buscar_lista_ficha(mificha->GetPosX() + 2, mificha->GetPosY() - 2) == NULL && dentro_de_tablero(mificha->GetPosX() + 2, mificha->GetPosY() - 2))
					{
						agregarFichaPosibleComida(lista_fichas[i]);
					}
				}
				else if (buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() + 1) != NULL && buscar_lista_ficha(mificha->GetPosX() + 1, mificha->GetPosY() + 1)->GetColor() != turno) //comprobamos que en su adyacente 1 hay ficha que comer
				{
					if (buscar_lista_ficha(mificha->GetPosX() + 2, mificha->GetPosY() + 2) == NULL && dentro_de_tablero(mificha->GetPosX() + 2, mificha->GetPosY() + 2))
					{
						agregarFichaPosibleComida(lista_fichas[i]);
					}
				}
				else if (buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() - 1) != NULL && buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() - 1)->GetColor() != turno) //comprobamos que en su adyacente 1 hay ficha que comer
				{
					if (buscar_lista_ficha(mificha->GetPosX() - 2, mificha->GetPosY() - 2) == NULL && dentro_de_tablero(mificha->GetPosX() - 2, mificha->GetPosY() - 2))
					{
						agregarFichaPosibleComida(lista_fichas[i]);
					}
				}
				else if (buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() + 1) != NULL && buscar_lista_ficha(mificha->GetPosX() - 1, mificha->GetPosY() + 1)->GetColor() != turno) //comprobamos que en su adyacente 1 hay ficha que comer
				{
					if (buscar_lista_ficha(mificha->GetPosX() - 2, mificha->GetPosY() + 2) == NULL && dentro_de_tablero(mificha->GetPosX() - 2, mificha->GetPosY() + 2))
					{
						agregarFichaPosibleComida(lista_fichas[i]);
					}
				}
			}
		}
	}
	if (existe_posible_comida()) {
		return true;
	}
	else {
		return false;
	}
}

bool ListaFichas::dentro_de_tablero(int i, int j)
{
	if (i <= 7 && i >= 0 && j <= 7 && j >= 0)
	{
		return true;
	}
	return false;
}

void ListaFichas::Mueve(Color color, int pos_iniX, int pos_iniY, int pos_finX, int pos_finY)
{
	Ficha* aux;
	aux = buscar_lista_ficha(pos_iniX, pos_iniY);
	aux->Mueve(pos_finX, pos_finY);
	aux->SetColor(color);
}

bool ListaFichas::pincho_en_ficha(int x, int y)
{
	if (buscar_lista_ficha(x, y) != NULL) return true;
	else	return false;
}

bool ListaFichas::existe_posible_comida()
{
	for (int i = 0; i < MAX_COMIDA; i++) {
		if (fichasConPosibleComida[i] != NULL) {
			return true;
		}
	}
	return false;
}
bool ListaFichas::esFichaConComida(Ficha* f) {
	for (int i = 0; i < MAX_COMIDA; i++) {
		if (fichasConPosibleComida[i] ==f) {
			return true;
		}
	}
	return false;
}

ListaFichas::ListaFichas()
{
	num = 0;
	for (int i = 0; i < MAX_FICHAS; i++)
		lista_fichas[i] = 0;
}

void ListaFichas::agregarFichaPosibleComida(Ficha* f) {
	for (int i = 0; i < MAX_COMIDA; i++) {
		if (fichasConPosibleComida[i] == NULL) {
			fichasConPosibleComida[i] = f;
			break;
		}
	}
}
void ListaFichas::inicializarPosibleComida() {
	for (int i = 0; i < MAX_COMIDA; i++) {
		fichasConPosibleComida[i] = NULL;
	}
}

int ListaFichas::getNumFichas() {
	return num;
}
Ficha* ListaFichas::operator[](int index) {
	return lista_fichas[index];
}

bool ListaFichas::operator!=(ListaFichas f) {
	if (f.num != num) {
		return true;
	}

	for (int i = 0; i < num; i++) {
		if (f[i]->GetPosX() != lista_fichas[i]->GetPosX() ||
			f[i]->GetPosY() != lista_fichas[i]->GetPosY() ||
			f[i]->GetColor() != lista_fichas[i]->GetColor() ||
			f[i]->GetTipo() != lista_fichas[i]->GetTipo()) {
			return true;
		}
	}
	return false;
}
