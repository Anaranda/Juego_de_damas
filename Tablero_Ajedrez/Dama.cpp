#include "Dama.h"
#include "ETSIDI.h"

#define M 8
#define PX_X  800
#define PX_Y  800

Dama::Dama()
{
	tipo = DAMA;
}

Dama::~Dama()
{
}

void Dama::SetColor(Color col)
{
	color = col;
}

void Dama::SetRadio(float rad)
{
	radio = rad;
}

void Dama::SetPos(int ix, int iy)
{
	posicion[0] = ix;
	posicion[1] = iy;
}

int Dama::GetPosX()
{
	return posicion[0];
}

int Dama::GetPosY()
{
	return posicion[1];
}

Color Dama::GetColor()
{
	return color;
}

Tipo Dama::GetTipo()
{
	return tipo;
}

void Dama::Mueve(int pos_finX, int pos_finY)
{
	posicion[0] = pos_finX;
	posicion[1] = pos_finY;
}

void Dama::Dibuja()
{
	int x, y;
	float theta;

	glEnable(GL_TEXTURE_2D);
	
	if (color == ROJO)
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/DamaRoja.png").id);//Pinta de color rojo la ficha (ROJO=0)
	}
	else if (color == VERDE)
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/DamaElegida.png").id);
	}

	else if (color == BLANCO)
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/DamaBlanca.png").id); //pinta de color blanco la ficha
	}

	//El vector posicion corresponde con coordenadas en el dibujo (x,y).
	//Lo ideal es que fuesen los indices (i,j) del elemento de la matriz del tablero
	//y después, en función del tamaño del dibujo calcular las coordenadas (x,y)
	//algo como:
	//posicion.x=i*DIST_ENTRE_CUADRADOS + DISTANCIA_ENTRE_CUADRADOS/2 
	//posicion.y=-j*DIST_ENTRE_CUADRADOS - DISTANCIA_ENTRE_CUADRADOS/2

	x = posicion[1] * (PX_X / M) + (PX_X / (2 * M));
	y = PX_Y - (posicion[0] * (PX_Y / M) + (PX_Y / (2 * M)));

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(x - radio, y - radio);
	glTexCoord2d(1, 1); glVertex2d(x + radio, y - radio);
	glTexCoord2d(1, 0); glVertex2d(x + radio, y + radio);
	glTexCoord2d(0, 0); glVertex2d(x - radio, y + radio);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Dama::BorraFicha() {
	delete this;
}