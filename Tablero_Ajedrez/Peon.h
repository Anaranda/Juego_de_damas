#pragma once
#include "Ficha.h"
#include"glut.h"
#include <math.h>



class Peon :public Ficha
{
	//friend class ListaPeon;
private:
	//Color color;

public:
	Peon();
	void Mueve();
	virtual void SetColor(Color col);
	virtual void SetRadio(float rad);
	virtual void SetPos(float ix, float iy);
	virtual int GetPosX();
	virtual int GetPosY();

	virtual void Dibuja();
};