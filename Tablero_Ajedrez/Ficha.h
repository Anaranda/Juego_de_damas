#pragma once
#include "Vector2D.h"

#define M 8
#define PX_X  800
#define PX_Y  800

enum Estado { VACIO, OCUPADO }; //VACIO=0 OCUPADO=1
enum Tipo { PEON, DAMA }; //PEON=0, DAMA=1
enum Color { ROJO, BLANCO, VERDE }; //ROJO=O BLANCO=1

class Ficha
{
private:
	Estado estado;
	Tipo tipo;
	Color color;

	float radio;

	Vector2D posicion; //Se puede sustituir por un vector de floats o de ints en un principio
	

public:
	
	//Puede que estas funciones get and set sean inncesarias pero las he puesto por si acaso
	Estado GetEstado();
	void SetEstado(Estado est);
	Tipo GetTipo();
	void SetTipo(Tipo tip);
	Color GetColor();
	void SetColor(Color col);
	float GetRadio();
	void SetRadio(float rad);

	//funcion que dibuja una ficha. La idea es que se llame a esta funcion 
	//en otra funcion como "DibujarTablero()" que pertenezca a la clase "Tablero" o "Partida"
	//igual que en las practicas con la clase "Mundo"
	//Recibe como parametros los indices i j de la posicion de dicha ficha en el tablero
	//mas info dentro de la funcion FALTA CODIGO DENTRO DE LA FUNCION
	void DibujaFicha(int i, int j);
	void BorraFicha(int i, int j, Color col);

};

