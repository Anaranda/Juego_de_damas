#pragma once
#include "Vector2D.h"



//enum Estado { VACIO, OCUPADO }; //VACIO=0 OCUPADO=1
//enum Tipo { PEON, DAMA }; //PEON=0, DAMA=1
//enum Color { ROJO, BLANCO, VERDE }; //ROJO=O BLANCO=1

enum Color { ROJO, BLANCO, VERDE }; //ROJO=O BLANCO=1
enum Tipo { PEON, DAMA }; //PEON=0, DAMA=1

class Ficha
{
	//friend class ListaPeon;
protected:
	int posicion[2];
	float radio;
	Color color;
	Tipo tipo;



	/*Estado estado;
	Tipo tipo;
	Color color;*/

	//Vector2D posicion; //Se puede sustituir por un vector de floats o de ints en un principio


public:


	//Puede que estas funciones get and set sean inncesarias pero las he puesto por si acaso
	/*Estado GetEstado();
	void SetEstado(Estado est);
	Tipo GetTipo();
	void SetTipo(Tipo tip);*/
	virtual Tipo GetTipo() = 0;
	virtual Color GetColor()=0;
	virtual void SetColor(Color col);
	float GetRadio();
	virtual void SetRadio(float rad);
	virtual void SetPos(float ix, float iy);
	virtual int GetPosX();
	virtual int GetPosY();



	//funcion que dibuja una ficha. La idea es que se llame a esta funcion 
	//en otra funcion como "DibujarTablero()" que pertenezca a la clase "Tablero" o "Partida"
	//igual que en las practicas con la clase "Mundo"
	//Recibe como parametros los indices i j de la posicion de dicha ficha en el tablero
	//mas info dentro de la funcion FALTA CODIGO DENTRO DE LA FUNCION
	//void Dibuja(int i, int j);
	virtual void Dibuja()=0;
	virtual void BorraFicha(int i, int j, Color col);
	virtual void Mueve(int posX, int posY) = 0;

};

