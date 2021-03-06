#pragma once
#include "Ficha.h"
#include <math.h>
#include"glut.h"



class Peon :public Ficha
{
public:
	Peon();
	virtual ~Peon();
	void Mueve();
	virtual void SetColor(Color col);
	virtual void SetRadio(float rad);
	virtual void SetPos(float ix, float iy);
	////////////////////////
	virtual int GetPosX();
	virtual int GetPosY();
	virtual Color GetColor();
	virtual Tipo GetTipo();
	////////////////////////
	virtual void Mueve(int pos_finX, int pos_finY);
	virtual void Dibuja();
	virtual void BorraFicha();
};