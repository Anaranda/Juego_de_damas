#pragma once
#include "Peon.h"
#define MAX_PEONES 24
class ListaPeones
{
public:
	ListaPeones();
	//virtual ~ListaPeones;
	bool agregar(Peon* p);
	void dibuja();
	void mueve();
	void inicializa();
	Peon* buscar_lista_peon(int x, int y);

private:
	Peon* lista_peon[MAX_PEONES];
	int num;
};