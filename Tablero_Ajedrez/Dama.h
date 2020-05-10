#pragma once
#include "Ficha.h"
#include "glut.h"
#include <math.h>



class Dama : public Ficha
{
private:
	//Color color;
public:
	Dama();
	virtual void SetColor(Color col);
	virtual void SetRadio(float rad);
	virtual void SetPos(float ix, float iy);
	virtual int GetPosX();
	virtual int GetPosY();

	virtual void Dibuja();
};