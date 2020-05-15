#include "Coordinador.h"
#include <iostream>
#include "ETSIDI.h"
#include "Tablero.h"
#include"glut.h"
#include <thread>
#include <chrono>
#include<Windows.h>

extern bool menu = true;


CoordinadorEtsiDamas::CoordinadorEtsiDamas() //Constructor del coordinador 
{
	state = INICIO;  //Cuando se empieza el juego el coordinador debe estar en el inicico
}

CoordinadorEtsiDamas::~CoordinadorEtsiDamas()  //Destructor
{
}

void CoordinadorEtsiDamas::musica()  //Función para controlar la música
{
	ETSIDI::playMusica("bin/musica/menu_musica_fondo.mp3", true);
}

void CoordinadorEtsiDamas::mouse(int button, int state, int m_x, int m_y) {

	if (CoordinadorEtsiDamas::state==INIJUEGO) {

		MiTablero.SelecFicha(button, state, m_x, m_y);
	}
	

}

void CoordinadorEtsiDamas::teclaEspecial(int key, int x, int y)
{
	
	if (state!= INIJUEGO) {


		switch (key)
		{

		case GLUT_KEY_DOWN:


			ETSIDI::play("bin/sonidos/menu_select.wav");
			//ETSIDI::stopMusica();


			if (state == SELINIJUEGO) {

				state = SELINSTRUC;
			}
			else if (state == SELINSTRUC) {

				state = SELABOUT;
			}
			break;




		case GLUT_KEY_UP:
			ETSIDI::play("bin/sonidos/menu_select.wav");
			//ETSIDI::stopMusica();
			if (state == SELABOUT) {

				state = SELINSTRUC;
			}
			else if (state == SELINSTRUC) {

				state = SELINIJUEGO;
			}
			break;



		case GLUT_KEY_RIGHT:

			ETSIDI::play("bin/sonidos/menu_forward.wav");
			//ETSIDI::stopMusica();

			if (state == INICIO) {

				state = SELINIJUEGO;

			}
			else if (state == SELINIJUEGO) {

				state = INIJUEGO;
				
				break;

			}
			else if (state == SELINSTRUC) {

				state = INSTRUC;

			}
			else if (state == SELABOUT) {

				state = ABOUT;

			}

			break;


		case GLUT_KEY_LEFT:

			ETSIDI::play("bin/sonidos/menu_back.wav");
			//ETSIDI::stopMusica();

			if (state == INICIO) {

				ETSIDI::play("bin/sonidos/pulsar_escape.wav");
				//ETSIDI::stopMusica();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				exit(0);

			}
			else if (state == SELINIJUEGO) {

				state = INICIO;

			}
			else if (state == SELINSTRUC) {

				state = INICIO;

			}
			else if (state == SELABOUT) {

				state = INICIO;

			}
			else if (state == INIJUEGO) {

				state = SELINIJUEGO;

			}
			else if (state == INSTRUC) {

				state = SELINSTRUC;

			}
			else if (state == ABOUT) {

				state = SELABOUT;

			}

			break;
		}

	}

	else {

		if (key == GLUT_KEY_LEFT)
		{
			ETSIDI::play("bin/sonidos/menu_back.wav");
			//ETSIDI::stopMusica();

			if (state == INIJUEGO) {

				state = SELINIJUEGO;

			}
		}


}




}

void CoordinadorEtsiDamas::tecla(unsigned char key)
{

	if (state == INIJUEGO || state == INSTRUC || state == ABOUT|| state==INICIO) {

		if (key == 27) {
			exit(0);
		}
	}


}

void CoordinadorEtsiDamas::dibuja()  //Para dibujar en pantalla los distintos estados
{
	if (state == INICIO)  //Estado de INICIO
	{

		musica();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Inicio.png").id);  //Al abrir el juego aparece la imagen de INICIO con el título del juego y los creadores
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	
	}

	if (state == SELINIJUEGO)  //MENU inicial del juego
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Sel_Juego.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
		//glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glEnd();

	}
	if (state == INIJUEGO)  //MENU inicial del juego
	{
		
		MiTablero.TexturaTablero();
		MiTablero.DibujaTablero();



		
		
	}

	if (state == SELINSTRUC)  //INSTRUCCIONES
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Sel_Instruc.png").id); 
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
	
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}

	if (state == INSTRUC)  //INSTRUCCIONES
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/IniInstruc.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
		//glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
	if (state == SELABOUT)  //INSTRUCCIONES
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Sel_About.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
		//glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
	if (state == ABOUT)  //INSTRUCCIONES
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/IniAbout.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex2d(0, 0);
		glTexCoord2d(1, 1); glVertex2d(800, 0);
		glTexCoord2d(1, 0); glVertex2d(800, 800);
		glTexCoord2d(0, 0); glVertex2d(0, 800);
		//glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}

}


