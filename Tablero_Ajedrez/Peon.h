#pragma once
#include "Ficha.h"
#include "ListaPeones.h"

class Peon :public Ficha
{
	//friend class ListaPeon;
private:
	Color color;

public:
	void Mueve();
	//void Dibuja();
};