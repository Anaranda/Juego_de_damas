#pragma once
#include "Ficha.h"
#include "glut.h"

class Dama : public Ficha
{
public:
	Dama();
	virtual ~Dama();
	virtual void SetColor(Color col);
	virtual void SetRadio(float rad);
	virtual void SetPos(int ix, int iy);
	virtual int GetPosX();
	virtual int GetPosY();
	//////////////////////////
	virtual Color GetColor();
	virtual Tipo GetTipo();
	virtual void Mueve(int pos_finX, int pos_finY);
	virtual void Dibuja();
	virtual void BorraFicha();
};