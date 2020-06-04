#include "Coordinador.h"
#include "ETSIDI.h"
#include <thread>
#include <chrono>
#include "glut.h"

#define PX_X  800
#define PX_Y  800


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

void CoordinadorEtsiDamas::mouse(int m_x, int m_y) {

	//Función para controlar los eventos de mouse 
	//en función del modo de juego seleccionado

	if (CoordinadorEtsiDamas::state == INIJUEGO) {
		MiTablero.SelecFicha(m_x, m_y);
	}
	else if (CoordinadorEtsiDamas::state == VSCPU) {
		MiTableroCPU.SelecFicha(m_x, m_y);
	}
	else if (CoordinadorEtsiDamas::state == VSCPUARBOL) {
		MiTableroCPUArbol.SelecFicha(m_x, m_y);
	}
}

void CoordinadorEtsiDamas::teclaEspecial(int key, int x, int y)
{

	if (state != INIJUEGO && state != VSCPU) {

		switch (key) 
		{
			//Esta función se encarga de gestionar los estados
			//en función de los datos recibidos por las teclas 
			//especiales (flechas)

		case GLUT_KEY_DOWN:


			ETSIDI::play("bin/sonidos/menu_select.wav");


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


void CoordinadorEtsiDamas::dibuja()  //Para dibujar en pantalla los distintos estados
{
	switch (state) {
	case INICIO: //Estado de INICIO
		musica();
		dibujaTextura("bin/imagenes/Inicio.png");
		
		break;


	case SELINIJUEGO:  //Estado selección humano-humano
		dibujaTextura("bin/imagenes/Sel_Juego.png");
		MiTablero.inStateHUMAN = false;
		break;


	case INIJUEGO: //
		glDisable(GL_LIGHTING);
		MiTablero.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTablero.TexturaTablero();
		MiTablero.inStateHUMAN = true; //Variable del tablero para interpretar la información recibida según selección del menú
		
		//Si detecta que no hay fichas de un jugador
		if (MiTablero.fin_de_juego()) {
			state = FIN;
			MiTablero.inStateHUMAN = false;
		}
		break;


	case SELVSCPU: //Estado selección humano-máquina
		dibujaTextura("bin/imagenes/Sel_Play_CPU.png");
		MiTableroCPU.inStateCPU = false;
		MiTableroCPUArbol.inStateCPUArbol = false;
		break;
	case SELEASY: //Estado selección humano-máquina fácil
		dibujaTextura("bin/imagenes/EasySelec.png");
		break;
	case SELDIF: //Estado selección humano-máquina difícil
		dibujaTextura("bin/imagenes/DifficultSelec.png");
		break;

	case VSCPU: //Inicio modo CPU fácil
		glDisable(GL_LIGHTING);
		MiTableroCPU.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPU.TexturaTablero();
		MiTableroCPU.inStateCPU = true;

		//Si detecta que no hay fichas de un jugador
		if (MiTableroCPU.fin_de_juego()) {
			state = FINCPU;
			MiTablero.inStateCPU = false;
		}
		break;

	case VSCPUARBOL:// Inicio modo CPU difícil

		glDisable(GL_LIGHTING);
		MiTableroCPUArbol.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPUArbol.TexturaTablero();
		MiTableroCPUArbol.inStateCPUArbol = true;

		//Si detecta que no hay fichas de un jugador
		if (MiTableroCPUArbol.fin_de_juego()) {
			state = FINCPUARBOL;
			MiTableroCPUArbol.inStateCPUArbol = false;

		}
		break;

	case SELINSTRUC:  //Estado selección instrucciones
		dibujaTextura("bin/imagenes/Sel_Instruc.png");
		break;


	case INSTRUC: //Instrucciones 
		dibujaTextura("bin/imagenes/IniInstruc.png");
		break;


	case SELABOUT: //Estado selección información
		dibujaTextura("bin/imagenes/Sel_About.png");
		break;


	case ABOUT: //Información
		dibujaTextura("bin/imagenes/IniAbout.png");
		break;


	case FIN:
		dibujaTextura("bin/imagenes/FIN.png");
		ETSIDI::play("bin/sonidos/pulsar_escape.wav");
		state = SELINIJUEGO;
		
		MiTablero.eliminar();
		
		glDisable(GL_LIGHTING);
		MiTablero.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTablero.TexturaTablero();

		MiTablero.cambio_estado_juego();
		if (MiTablero.turno == ROJO)
			MiTablero.cambio_turno();

		break;


	case FINCPU:
		dibujaTextura("bin/imagenes/FIN.png");
		ETSIDI::play("bin/sonidos/pulsar_escape.wav");
		state = SELVSCPU;

		MiTableroCPU.eliminar();

		glDisable(GL_LIGHTING);
		MiTableroCPU.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPU.TexturaTablero();

		MiTableroCPU.cambio_estado_juego();
		if (MiTableroCPU.turno == ROJO)
			MiTableroCPU.cambio_turno();

		break;

	case FINCPUARBOL:
		dibujaTextura("bin/imagenes/FIN.png");
		ETSIDI::play("bin/sonidos/pulsar_escape.wav");
		state = SELVSCPU;

		MiTableroCPUArbol.eliminar();

		glDisable(GL_LIGHTING);
		MiTableroCPUArbol.DibujaTablero();
		glEnable(GL_LIGHTING);
		MiTableroCPUArbol.TexturaTablero();

		MiTableroCPUArbol.cambio_estado_juego();
		if (MiTableroCPUArbol.turno == ROJO)
			MiTableroCPUArbol.cambio_turno();

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


