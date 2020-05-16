#include "Peon.h"

#include "ETSIDI.h"
#define M 8
#define PX_X  800
#define PX_Y  800

Peon::Peon()
{
	tipo = PEON;
}

void Peon::Mueve()
{
	//Aqui llamamos a la funcion mueve de las fichas
}

void Peon::SetColor(Color col)
{
	color = col;
}

void Peon::SetRadio(float rad)
{
	radio = rad;
}

void Peon::SetPos(float ix, float iy)
{
	posicion[0] = ix;
	posicion[1] = iy;
}

int Peon::GetPosX()
{
	return posicion[0];
}

int Peon::GetPosY()
{
	return posicion[1];
}

Color Peon::GetColor()
{
	return color;
}

Tipo Peon::GetTipo()
{
	return tipo;
}

void Peon::Mueve(int pos_finX, int pos_finY)
{
	posicion[0] = pos_finX;
	posicion[1] = pos_finY;
}

void Peon::Dibuja()
{
	int x, y;
	float theta;
	radio = (PX_X / M) * 0.4; //definir en el set radio

	glEnable(GL_TEXTURE_2D);
	//Color de la ficha

	if (color == ROJO)
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/PeonRojo.png").id);//Pinta de color rojo la ficha (ROJO=0)
	}
	else if (color == VERDE) //color de cuando lo seleccionas
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/FichaElegida.png").id);
	}

	else if (color == BLANCO)
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/PeonBlanco.png").id); //pinta de color blanco la ficha
	}


	//El vector posicion corresponde con coordenadas en el dibujo (x,y).
	//Lo ideal es que fuesen los indices (i,j) del elemento de la matriz del tablero
	//y después, en función del tamaño del dibujo calcular las coordenadas (x,y)
	//algo como:
	//posicion.x=i*DIST_ENTRE_CUADRADOS + DISTANCIA_ENTRE_CUADRADOS/2 
	//posicion.y=-j*DIST_ENTRE_CUADRADOS - DISTANCIA_ENTRE_CUADRADOS/2

	//x = i * (PX_X / M) + (PX_X / (2 * M));
	//y = PX_Y - (j * (PX_Y / M) + (PX_Y / (2 * M))); //CUIDADO CON EL OFFSET

	x = posicion[1] * (PX_X / M) + (PX_X / (2 * M));
	y = PX_Y - (posicion[0] * (PX_Y / M) + (PX_Y / (2 * M)));

	/*cout << "Coordenadas:" << "(" << x << "," << y << ")" << endl;*/

	//DIBUJA CIRCULO

	
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(x-40, y-40);
	glTexCoord2d(1, 1); glVertex2d(x+40, y-40);
	glTexCoord2d(1, 0); glVertex2d(x+40, y+40);
	glTexCoord2d(0, 0); glVertex2d(x-40, y+40);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	/*glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glTranslatef(x, y, 0);
	for (int i = 0; i < 360; i=i+36) {
		theta = i * 3.1416 / 180;
		glVertex2f(x + radio * cos(theta), y + radio * sin(theta));
	}
	glTranslatef(-x, -y, 0);
	glEnd();
	glEnable(GL_LIGHTING);*/
}
