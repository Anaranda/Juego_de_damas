#include "Tablero.h"
#include "Ficha.h"
#include <iostream>

#define M 8
#define PX_X  800
#define PX_Y  800

bool estado_inicial = true;
bool turno_fallido = false;// BOOL EN CASO DE INCUMPLIMIENTO DE RREGALS DE MOVIMIENTO


Tablero::Tablero()
{
	turno = blancas;
	seleccionada = false;
}

void Tablero::Inicializa()
{
	//Se dibuja el tablero en su posición de comienzo de juego
	//Se considera que la esquina inferior izquierda y la superior derecha es negra y se juega sobre negras
	//Se considera piezas blancas abajo y rojas arriba

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			tablero[i][j].SetTipo(PEON); //inicialmente todas las fichas son peones

			if ((i + j) % 2 != 0) //Si el resto de dividir (i+j) entre 2 es distinto de 0, es decir, es IMPAR: estamos sobre cuadrado negro (donde se mueven las fichas)
			{

				if (i < 3) //estamos en las 3 primeras filas ¡¡¡¡SOLO VALIDO PARA TABLERO 8X8!!!!!
				{
					tablero[i][j].SetEstado(OCUPADO);
					tablero[i][j].SetColor(ROJO); //La pieza es roja
					tablero[i][j].DibujaFicha(i, j); //Dibujamos la ficha 
				}

				else if (i > 4) //estamos en las últimas 3 filas ¡¡¡¡SOLO VALIDO PARA TABLERO 8X8!!!!!
				{
					tablero[i][j].SetEstado(OCUPADO);
					tablero[i][j].SetColor(BLANCO); //la pieza es blanca
					tablero[i][j].DibujaFicha(i, j); //Dibujamos la ficha 
				}

			}
			else
			{
				tablero[i][j].SetEstado(VACIO); // Si está sobre cuadrados blancos pone la ficha como VACIO
			}
		}
	}
}

void Tablero::DibujaTablero()
{
	if (estado_inicial)
	{
		Inicializa();
		estado_inicial = false;
	}
	//Dibuja el tablero llamando a la función DibujaFicha() al recorrer cada posición del tablero
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//if (!&tablero[i][j]) //Si la dirección que contiene es distinto de 0 (NULL)
			//{
			//	tablero[i][j].DibujaFicha(i, j);
			//}

			if (tablero[i][j].GetEstado()) //si el estado es ocupado (1) 
			{
				tablero[i][j].DibujaFicha(i, j); //dibuja la ficha 
			}
		}
	}
}

void Tablero::TexturaTablero()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/main_board.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(0, PX_Y);
	glTexCoord2d(1, 1); glVertex2d(PX_X, PX_Y);
	glTexCoord2d(1, 0); glVertex2d(PX_X, 0);
	glTexCoord2d(0, 0); glVertex2d(0, 0);
	glEnd();
}

void Tablero::SelecFicha(int button, int state, int mouseX, int mouseY)
{
	
	//enum Turno { blancas, rojas };
	//Turno turno;
	
	Color ficha_selec;
	Color color_turno;
	int v_abs[2];
	int impar;
	

	if (turno == rojas) {
		color_turno=ROJO;
	} else color_turno = BLANCO;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		pos[1] = trunc(mouseX / (PX_X / M)); // el eje x corresponde con el indice j (COLUMNAS)
		pos[0] = trunc(mouseY / (PX_Y / M)); //el eje y corresponde con el indice i (FILAS)
		impar = (pos[1] + pos[0]) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA

		

		if (tablero[pos[0]][pos[1]].GetEstado() == OCUPADO && seleccionada==false)	// seleccionas una ficha de tu color cuando sea tu turno	
		{
			ficha_selec = tablero[pos[0]][pos[1]].GetColor();		// Se guarda el color de la ficha seleccionada
			if (ficha_selec == color_turno) {						//Ha seleccionado una de sus fichas
				tablero[pos[0]][pos[1]].SetColor(VERDE);			//Se pone de color verde
				seleccionada = true;								
				pos_verde[0] = pos[0];								//guardamos la posicion donde esta la ficha verde
				pos_verde[1] = pos[1];
				
			}
						
		}

		
		if (tablero[pos[0]][pos[1]].GetEstado() == VACIO && seleccionada && impar != 0)								//si la mueves a una casilla vacia
		{


			v_abs[1] = abs(pos[1] - pos_verde[1]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.
			v_abs[0] = abs(pos[0] - pos_verde[0]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.

			if (pos_verde[0] < pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == ROJO) {	// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
				seleccionada = false;
			}

			else if (pos_verde[0] > pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == BLANCO) {// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
				seleccionada = false;

			}
			else { //EN CASO DE ERROR EN EL NUMERO DE UNIDADES QUE QUEREMOS MOVERNOS, O EN CASO DE QUERER IR HACIA ATRAS, NOS MANDA A REPETIR EL MOVIMIENTO.
				turno_fallido = true;
				seleccionada = false;
				tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);

			}

			if (turno_fallido == false) {

				if (turno == rojas) turno = blancas;														//cambiamos el turno
				else turno = rojas;
			}


			else { // NOS PERMITE REPETIR EL MOVIMIENTO, YA QUE EL TURNO NO CAMBIA
				if (turno == rojas) turno = rojas;
				else turno = blancas;
				turno_fallido = false;
			}

		}
	}

	


}

//int Tablero::GetX()
//{
//	return PX_X;
//}
//
//int Tablero::GetY()
//{
//	return PX_Y;
//}
