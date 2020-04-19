#pragma once
#include "Ficha.h"
#include <stdio.h>
#include "Mouse.h"
#include "ETSIDI.h"

#define M 8 //dimensión del tablero
//dimension tablero
#define PX_X 800
#define PX_Y 800

using namespace std;


class Tablero
{
private:
	Ficha tablero[M][M];

public:
	enum Turno{blancas, rojas};
	Turno turno;
	bool seleccionada;
	int pos[2];
	int pos_verde[2];
	Tablero();
	void Inicializa();
	void DibujaTablero();
	void TexturaTablero();
	/*int GetX(); 
	int GetY();*/
	void SelecFicha (int button, int state, int mouseX, int mouseY);
};

