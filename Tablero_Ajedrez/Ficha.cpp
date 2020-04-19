//Prueba para ver si se sincroniza






#include "Ficha.h"
#include<math.h>
#include <iostream>
#include "glut.h"

#define M 8
#define PX_X  800
#define PX_Y  800

using namespace std;

Estado Ficha::GetEstado()
{
	return estado;
}


void Ficha::SetEstado(Estado est)
{
	estado = est;
}

Tipo Ficha::GetTipo()
{
	return tipo;
}

void Ficha::SetTipo(Tipo tip)
{
	tipo = tip;
}

Color Ficha::GetColor()
{
	return color;
}

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
	radio = rad;
}

void Ficha::DibujaFicha(int i, int j)
{
	int x, y;
	float theta;
	radio = (PX_X / M) * 0.4; //definir en el set radio
	glBegin(GL_POLYGON);

	//Color de la ficha
	if (color == ROJO)
	{
		glColor3f(1, 0, 0);//Pinta de color rojo la ficha (ROJO=0)
	}
	else if (color == VERDE) //color de cuando lo seleccionas
	{
		glColor3f(0, 1, 0);
	}

	else if (color == BLANCO)
	{
		glColor3f(1, 1, 1); //pinta de color blanco la ficha
	}


	//El vector posicion corresponde con coordenadas en el dibujo (x,y).
	//Lo ideal es que fuesen los indices (i,j) del elemento de la matriz del tablero
	//y después, en función del tamaño del dibujo calcular las coordenadas (x,y)
	//algo como:
	//posicion.x=i*DIST_ENTRE_CUADRADOS + DISTANCIA_ENTRE_CUADRADOS/2 
	//posicion.y=-j*DIST_ENTRE_CUADRADOS - DISTANCIA_ENTRE_CUADRADOS/2

	//x = i * (PX_X / M) + (PX_X / (2 * M));
	//y = PX_Y - (j * (PX_Y / M) + (PX_Y / (2 * M))); //CUIDADO CON EL OFFSET

	x = j * (PX_X / M) + (PX_X / (2 * M));
	y = PX_Y - (i * (PX_Y / M) + (PX_Y / (2 * M)));

	/*cout << "Coordenadas:" << "(" << x << "," << y << ")" << endl;*/

	//DIBUJA CIRCULO
	for (int i = 0; i < 360; i++) {
		theta = i * 3.1416 / 180;
		glVertex2f(x + radio * cos(theta), y + radio * sin(theta));
	}
	glEnd();
}

void Ficha::BorraFicha(int i, int j, Color col)
{
	estado = VACIO;
	tipo = PEON;
	color = col;
}
