#include "Coordinador.h"
#include "ETSIDI.h"
#include <thread>
#include <chrono>
#include"glut.h"

#define PX_X  800
#define PX_Y  800

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
	//ETSIDI::playMusica("bin/musica/menu_musica_fondo.mp3", true);
}

void CoordinadorEtsiDamas::mouse(int m_x, int m_y) {

	if (CoordinadorEtsiDamas::state == INIJUEGO) {
		MiTablero.SelecFicha(m_x, m_y);
		cout << "SelecFicha" << endl;
	}

	else if (CoordinadorEtsiDamas::state == VSCPU) {
		MiTableroCPU.SelecFicha(m_x, m_y);
		cout << "SelecFichaVSCPU" << endl;
	}
	else if (CoordinadorEtsiDamas::state == VSCPUARBOL) {
		MiTableroCPUArbol.SelecFicha(m_x, m_y);
		cout << "SelecFichaVSCPUArbol" << endl;
	}
}

void CoordinadorEtsiDamas::teclaEspecial(int key, int x, int y)
{


	if (state != INIJUEGO && state != VSCPU) {


		switch (key)
		{

		case GLUT_KEY_DOWN:


			ETSIDI::play("bin/sonidos/menu_select.wav");
			//ETSIDI::stopMusica();


			if (state == SELINIJUEGO) {

				state = SELVSCPU;
			}
			else if (state == SELVSCPU) {

				state = SELINSTRUC;
			}
			else if (state == SELINSTRUC) {

				state = SELABOUT;
			}
			else if (state == SELEASY) {
				state = SELDIF;
			}
			break;




		case GLUT_KEY_UP:
			ETSIDI::play("bin/sonidos/menu_select.wav");
			//ETSIDI::stopMusica();
			if (state == SELABOUT) {

				state = SELINSTRUC;
			}
			else if (state == SELINSTRUC) {

				state = SELVSCPU;
			}
			else if (state == SELVSCPU) {

				state = SELINIJUEGO;
			}
			else if (state == SELDIF) {
				state = SELEASY;
			}
			break;



		case GLUT_KEY_RIGHT:

			ETSIDI::play("bin/sonidos/menu_forward.wav");
			//ETSIDI::stopMusica();

			if (state == INICIO) {

				state = SELINIJUEGO;

			}
			else if (state == SELINIJUEGO) {

				menu = true;
				state = INIJUEGO;

				break;

			}
			else if (state == SELINSTRUC) {

				state = INSTRUC;

			}
			else if (state == SELVSCPU) {

				state = SELEASY;

			}
			else if (state == SELEASY) {

				state = VSCPU;

			}
			else if (state == SELDIF) {

				state = VSCPUARBOL;

			}
			else if (state == SELABOUT) {

				state = ABOUT;

			}

			break;


		case GLUT_KEY_LEFT:

			ETSIDI::play("bin/sonidos/menu_back.wav");
			//ETSIDI::stopMusica();

			if (state == INICIO) {

				ETSIDI::stopMusica();
				ETSIDI::play("bin/sonidos/pulsar_escape.wav");

				std::this_thread::sleep_for(std::chrono::seconds(1));
				exit(0);

			}
			else if (state == SELINIJUEGO) {

				state = INICIO;

			}
			else if (state == SELVSCPU) {

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
			else if (state == VSCPU) {

				state = SELEASY;

			}
			else if (state == SELEASY) {

				state = SELVSCPU;

			}
			else if (state == VSCPUARBOL) {

				state = SELDIF;

			}
			else if (state == SELDIF) {

				state = SELVSCPU;

			}
			else if (state == INSTRUC) {

				state = SELINSTRUC;

			}
			else if (state == ABOUT) {

				state = SELABOUT;

			}

			else if (state == FIN) {
				state = SELINIJUEGO;

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
			else if (state == VSCPU) {


				state = SELVSCPU;
			}
		}
	}
}

void CoordinadorEtsiDamas::tecla(unsigned char key)
{
	if (state == INIJUEGO || state == INSTRUC || state == ABOUT || state == INICIO) {
		if (key == 27) {
			exit(0);
		}
	}


}

void CoordinadorEtsiDamas::dibuja()  //Para dibujar en pantalla los distintos estados
{
	switch (state) {
	case INICIO: //Estado de INICIO
		musica();
		dibujaTextura("bin/imagenes/Inicio.png");
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("bin/fuentes/Arcadepix_Plus.ttf", 24);
		ETSIDI::printxy("PRESS RIGHT TO PLAY", 255, 400);
		break;


	case SELINIJUEGO:  //MENU inicial del juego
		dibujaTextura("bin/imagenes/Sel_Juego.png");
		MiTablero.inStateHUMAN = false;
		break;


	case INIJUEGO: //MENU inicial del juego
		glDisable(GL_LIGHTING);
		MiTablero.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTablero.TexturaTablero();
		MiTablero.inStateHUMAN = true;
		if (MiTablero.fin_de_juego()) {
			state = FIN;
			ETSIDI::setTextColor(255, 255, 0);
			ETSIDI::setFont("bin/fuentes/Arcadepix Plus.ttf", 50);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			MiTablero.inStateHUMAN = false;

		}
		break;


	case SELVSCPU:  //MENU inicial del juego
		dibujaTextura("bin/imagenes/Sel_Play_CPU.png");
		MiTableroCPU.inStateCPU = false;
		break;
	case SELEASY:
		dibujaTextura("bin/imagenes/EasySelec.png");
		break;
	case SELDIF:
		dibujaTextura("bin/imagenes/DifficultSelec.png");
		break;

	case VSCPU: //MENU inicial del juego
		glDisable(GL_LIGHTING);
		MiTableroCPU.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPU.TexturaTablero();
		MiTableroCPU.inStateCPU = true;

		if (MiTableroCPU.fin_de_juego()) {
			state = FINCPU;
			ETSIDI::setTextColor(255, 255, 0);
			ETSIDI::setFont("bin/fuentes/Arcadepix Plus.ttf", 50);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			MiTablero.inStateCPU = false;

		}
		break;

	case VSCPUARBOL:

		glDisable(GL_LIGHTING);
		MiTableroCPUArbol.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPUArbol.TexturaTablero();
		MiTableroCPUArbol.inStateCPUArbol = true;

		if (MiTableroCPUArbol.fin_de_juego()) {
			state = FINCPU;
			ETSIDI::setTextColor(255, 255, 0);
			ETSIDI::setFont("bin/fuentes/Arcadepix Plus.ttf", 50);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			ETSIDI::printxy("", 200.0, 400.0, 0.0);
			MiTableroCPUArbol.inStateCPU = false;

		}
		break;

	case SELINSTRUC:  //INSTRUCCIONES
		dibujaTextura("bin/imagenes/Sel_Instruc.png");
		break;


	case INSTRUC:
		dibujaTextura("bin/imagenes/IniInstruc.png");
		break;


	case SELABOUT:
		dibujaTextura("bin/imagenes/Sel_About.png");
		break;


	case ABOUT:
		dibujaTextura("bin/imagenes/IniAbout.png");
		break;


	case FIN:
		dibujaTextura("bin/imagenes/FIN.png");
		ETSIDI::play("bin/sonidos/pulsar_escape.wav");
		state = SELINIJUEGO;
		cout << "Cambia a Selini" << endl;
		MiTablero.eliminar();
		cout << "Elimina" << endl;
		glDisable(GL_LIGHTING);
		MiTablero.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTablero.TexturaTablero();

		MiTablero.cambio_estado_juego();
		if(MiTablero.turno==ROJO)
		MiTablero.cambio_turno();



		//REVISA ESTO PARA QUE NO EMPIECEN LAS ROJAS 

		//AHORA QUE LO PIENSO DEPENDE DE QUIEN GANE LA PARTIDA ASI QUE HAY QUE CAMBIAR EL TURNO EN SELECFICHA O PONER UN IF
		//PONER UN TEXTO SOBRE EL TABLERO QUE NOS PIDA PULSAR UNA TECLA PARA PASAR A SELINIJUEGO Y ECHAR OTRA PARTIDA O LO QUE QUIERAS


		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/IniAbout.png").id);
		//glDisable(GL_LIGHTING);
		//glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		//glTexCoord2d(0, 1); glVertex2d(0, 0);
		//glTexCoord2d(1, 1); glVertex2d(800, 0);
		//glTexCoord2d(1, 0); glVertex2d(800, 800);
		//glTexCoord2d(0, 0); glVertex2d(0, 800);
		////glEnable(GL_LIGHTING);
		//glEnd();
		//glDisable(GL_TEXTURE_2D);

		cout << "Entramos en fin" << endl;
		
		//MiTablero.eliminar();
		break;


	case FINCPU:
		dibujaTextura("bin/imagenes/FIN.png");
		ETSIDI::play("bin/sonidos/pulsar_escape.wav");
		state = SELVSCPU;
		cout << "Cambia a SelVSCPU" << endl;
		MiTableroCPU.eliminar();
		cout << "Elimina" << endl;
		glDisable(GL_LIGHTING);
		MiTableroCPU.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPU.TexturaTablero();

		MiTableroCPU.cambio_estado_juego();
		if(MiTableroCPU.turno==ROJO)
		MiTableroCPU.cambio_turno();

	

		//REVISA ESTO PARA QUE NO EMPIECEN LAS ROJAS 

		//AHORA QUE LO PIENSO DEPENDE DE QUIEN GANE LA PARTIDA ASI QUE HAY QUE CAMBIAR EL TURNO EN SELECFICHA O PONER UN IF
		//PONER UN TEXTO SOBRE EL TABLERO QUE NOS PIDA PULSAR UNA TECLA PARA PASAR A SELINIJUEGO Y ECHAR OTRA PARTIDA O LO QUE QUIERAS


		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/IniAbout.png").id);
		//glDisable(GL_LIGHTING);
		//glBegin(GL_POLYGON);
		//glColor3f(1, 1, 1);
		//glTexCoord2d(0, 1); glVertex2d(0, 0);
		//glTexCoord2d(1, 1); glVertex2d(800, 0);
		//glTexCoord2d(1, 0); glVertex2d(800, 800);
		//glTexCoord2d(0, 0); glVertex2d(0, 800);
		////glEnable(GL_LIGHTING);
		//glEnd();
		//glDisable(GL_TEXTURE_2D);
		
		cout << "Entramos en fin CPU" << endl;

		//MiTablero.eliminar();
		break;
	}
}

void CoordinadorEtsiDamas::dibujaTextura(const char* path) {
	//Esta función imprime en toda la pantalla la imagen indicada

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(path).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(0, 0);
	glTexCoord2d(1, 1); glVertex2d(PX_X, 0);
	glTexCoord2d(1, 0); glVertex2d(PX_X, PX_Y);
	glTexCoord2d(0, 0); glVertex2d(0, PX_Y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}


