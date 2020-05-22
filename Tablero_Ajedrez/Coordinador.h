#pragma once
#include "Tablero.h"
#include "ListaFichas.h"


extern bool menu;

class CoordinadorEtsiDamas
{

public:
	//Métodos
	CoordinadorEtsiDamas();
	~CoordinadorEtsiDamas();
	void teclaEspecial(int key, int x, int y);
	void mouse(int button, int state, int m_x, int m_y);
	void tecla(unsigned char key);
	void dibuja();
	void musica();
	void dibujaTextura(const char* path);

	//PERMITE LECTURA DEL ESTADO DESDE EL TABLERO
	enum State //Se crea una enumeración con los posibles estados que va a adoptar la máquina de estados
	{
		INICIO, INIJUEGO, VSCPU, INSTRUC, ABOUT, FIN, FINCPU, SELINIJUEGO, SELVSCPU, SELINSTRUC, SELABOUT
	};
	State state;  //Se define una variable del tipo de la enumeración anterior

protected:
	//Miembros
	Tablero MiTablero;
	Tablero MiTableroCPU;

};
