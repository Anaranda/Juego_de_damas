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

	bool buscar_lista_color(Color color);

	//NUEVO2//////////////
	void eliminar(int x, int y);
	void crear_dama(int x, int y);
	Ficha* posible_comida(Color micolor, Vector2D* donde_come, Vector2D* donde_va);
	bool dentro_de_tablero(int i, int j);
	void Mueve(Color color, int pos_iniX, int pos_iniY, int pos_finX, int pos_finY);
	bool Pincho_en_ficha(int x, int y);
	bool existe_posible_comida(Color micolor); //esta igual sobra

private:
	Ficha* lista_fichas[MAX_FICHAS];
	int num;
};
