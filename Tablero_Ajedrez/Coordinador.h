#pragma once
#include "Tablero.h"
#include "ListaFichas.h"

class CoordinadorEtsiDamas
{
public:
	//M�todos
	CoordinadorEtsiDamas();
	~CoordinadorEtsiDamas();
	void teclaEspecial(int key, int x, int y);
	void mouse(int m_x, int m_y);
	void dibuja();
	void musica();
	void dibujaTextura(const char* path);

	//PERMITE LECTURA DEL ESTADO DESDE EL TABLERO
	enum State //Se crea una enumeraci�n con los posibles estados que va a adoptar la m�quina de estados
	{
		INICIO, INIJUEGO, VSCPU, VSCPUARBOL, INSTRUC, ABOUT, FIN, FINCPU, FINCPUARBOL, SELINIJUEGO, SELVSCPU,SELEASY,SELDIF, SELINSTRUC, SELABOUT
	};
	State state;  //Se define una variable del tipo de la enumeraci�n anterior

protected:
	//Miembros. Un tablero por cada modo de juego
	Tablero MiTablero;
	Tablero MiTableroCPU;
	Tablero MiTableroCPUArbol;

};
