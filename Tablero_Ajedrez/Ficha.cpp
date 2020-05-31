#include "Ficha.h"
#include<math.h>
#include <iostream>
#include "glut.h"

#define M 8
#define PX_X  800
#define PX_Y  800

using namespace std;

void Ficha::SetColor(Color col)
{
	color = col;
}

float Ficha::GetRadio()
{
	return radio;
}

void Ficha::SetRadio(float rad)
{
	if (rad < 0.1F)
		rad = 0.1F;
	radio = rad;
}


void Ficha::SetPos(float ix, float iy)
{
	posicion[0] = ix;
	posicion[1] = iy;
}

int Ficha::GetPosX()
{

	return posicion[0];
}

int Ficha::GetPosY()
{
	return posicion[1];
}

Ficha::~Ficha()
{
}




