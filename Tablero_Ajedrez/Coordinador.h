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


protected:
	//Miembros
	Tablero MiTablero;
	
	enum State //Se crea una enumeración con los posibles estados que va a adoptar la máquina de estados
	{
		INICIO, INIJUEGO, INSTRUC, ABOUT, FIN, SELINIJUEGO,SELINSTRUC, SELABOUT
	};
	State state;  //Se define una variable del tipo de la enumeración anterior

};
