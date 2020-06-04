#include "Coordinador.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>
#include<ETSIDI.h>


#include"Ficha.h"
#include"Tablero.h"
#include"Vector2D.h"

#include"glut.h"

#define PX_X  800
#define PX_Y  800

CoordinadorEtsiDamas EtsiDamas;
//Tablero MiTablero;

void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnSpecialKeyboardDown(int key, int x, int y);
void OnMouseEvent(int button, int state, int m_x, int m_y);
void resize(int width, int height);


int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 0); //Posicion de la esquina superior izquierda del la ventana
	glutInitWindowSize(PX_X, PX_Y);
	glutCreateWindow("DRAUGHTS");

	//habilitar luces y definir perspectiva
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, PX_X, 0, PX_Y);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	
	glutSpecialFunc(OnSpecialKeyboardDown);
	glutMouseFunc(OnMouseEvent);
	glutReshapeFunc(resize);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//aqui es donde hay que poner el código de dibujo
	
	EtsiDamas.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnTimer(int value)
{
	glutPostRedisplay();
}

void OnMouseEvent(int button, int state, int m_x, int m_y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		EtsiDamas.mouse(m_x, m_y);
		cout << m_x << m_y << endl;
	}
}

void resize(int width, int height)
{
	glutReshapeWindow(800, 800);
	glutPostRedisplay();
}

void OnSpecialKeyboardDown(int key, int x, int y)  //Funciones para teclas especiales 
{
	EtsiDamas.teclaEspecial(key, x, y);
	glutPostRedisplay();
}


