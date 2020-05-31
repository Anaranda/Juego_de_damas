#pragma once
#include "Vector2D.h"

enum Color { ROJO = 0, BLANCO, VERDE }; //ROJO=O BLANCO=1 VERDE=2
enum Tipo { PEON, DAMA }; //PEON=0, DAMA=1

class Ficha
{
protected:
	int posicion[2];
	float radio;
	Color color;
	Tipo tipo;

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
	virtual ~Ficha();
	virtual void BorraFicha()=0;
	virtual void Dibuja()=0;
	virtual void Mueve(int posX, int posY) = 0;

};

