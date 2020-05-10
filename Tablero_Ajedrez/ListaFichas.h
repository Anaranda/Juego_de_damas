#pragma once
#include "Ficha.h"
#include "Dama.h"
#include "Peon.h"
#define MAX_FICHAS 24
class ListaFichas
{
public:

	ListaFichas();
	//virtual ~ListaFichas;
	bool agregar(Ficha* p);

	//bool agregar(Peon* p);
	//bool agregar(Dama* p);
	void dibuja();
	//void mueve();
	void inicializa();
	Ficha* buscar_lista_ficha(int x, int y);

private:
	Ficha* lista_fichas[MAX_FICHAS];
	int num;
};
