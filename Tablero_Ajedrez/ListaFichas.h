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
	void eliminar(int x, int y);
	void crear_dama(int x, int y);
	Ficha* posible_comida(Color micolor, Vector2D* donde_come, Vector2D* donde_va);

	bool dentro_de_tablero(int i, int j);
	//analisis_diagonales_peon(int i, int j, Color micolor)
private:
	Ficha* lista_fichas[MAX_FICHAS];
	int num;
};
