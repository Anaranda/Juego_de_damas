#pragma once
#include "Ficha.h"
#include "Dama.h"
#include "Peon.h"

#define MAX_FICHAS 24
#define MAX_COMIDA 5

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
	void eliminar_fichas();
	Ficha* buscar_lista_ficha(int x, int y);

	bool buscar_lista_color(Color color);

	//NUEVO2//////////////
	void eliminar(int x, int y);
	Ficha* convertir_a_dama(int x, int y);
	bool posible_comida(Color turno);
	void agregarFichaPosibleComida(Ficha*);
	void inicializarPosibleComida();
	bool dentro_de_tablero(int i, int j);
	void Mueve(Color color, int pos_iniX, int pos_iniY, int pos_finX, int pos_finY);
	bool pincho_en_ficha(int x, int y);
	bool existe_posible_comida();
	bool esFichaConComida(Ficha*);
private:
	Ficha* lista_fichas[MAX_FICHAS];
	Ficha* fichasConPosibleComida[MAX_COMIDA];
	int num;
};
