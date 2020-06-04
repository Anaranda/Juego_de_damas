#include "Mouse.h"
#include <math.h>

#define M 8
#define PX_X  800
#define PX_Y  800

using namespace std;

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}


void Mouse::SetIndices(int button, int state, int mouseX, int mouseY)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		indices[1]= trunc(mouseX / (PX_X / M)); // el eje x corresponde con el indice j (COLUMNAS)
		indices[0] = trunc(mouseY / (PX_Y / M)); //el eje y corresponde con el indice i (FILAS)
	}
}
