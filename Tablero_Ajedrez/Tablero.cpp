#include "Tablero.h"
#include "Ficha.h"
#include <math.h>
#include <iostream>

using namespace std;

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
	fichas.inicializa();

}

void Tablero::DibujaTablero()
{
	if (estado_inicial)
	{
		Inicializa();
		estado_inicial = false;
	}
	fichas.dibuja();	
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
	//Color ficha_selec;
	Color color_turno;
	int v_abs[2];
	int impar;
	int middle_pos[2];
	Vector2D donde_va, donde_come;

	//nuevo
	Ficha* ficha_selec;
	/////////

	if (turno == rojas) {

		color_turno = ROJO;
	}


	else {
		color_turno = BLANCO;
	}



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		pos[1] = trunc(mouseX / (PX_X / M)); // el eje x corresponde con el indice j (COLUMNAS)
		pos[0] = trunc(mouseY / (PX_Y / M)); //el eje y corresponde con el indice i (FILAS)
		impar = (pos[1] + pos[0]) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA

		ficha_selec = fichas.buscar_lista_ficha(pos[0], pos[1]);

		if ((fichas.posible_comida(color_turno, &donde_come, &donde_va) != NULL) && seleccionada == false) {


			fichas.posible_comida(color_turno, &donde_come, &donde_va)->SetColor(VERDE);			//Se pone de color verde
			seleccionada = true;
			pos_verde[0] = fichas.posible_comida(color_turno, &donde_come, &donde_va)->GetPosX();								//guardamos la posicion donde esta la ficha verde
			pos_verde[1] = fichas.posible_comida(color_turno, &donde_come, &donde_va)->GetPosY();
		}
		else if (ficha_selec != NULL && seleccionada == false)	// seleccionas una ficha de tu color cuando sea tu turno	
		{

			//ficha_selec = tablero[pos[0]][pos[1]].GetColor();		// Se guarda el color de la ficha seleccionada
			if (ficha_selec->GetColor() == color_turno) {						//Ha seleccionado una de sus fichas

				ficha_selec->SetColor(VERDE);			//Se pone de color verde
				seleccionada = true;
				pos_verde[0] = pos[0];								//guardamos la posicion donde esta la ficha verde
				pos_verde[1] = pos[1];

			}

		}

		if (pos[0] == 0 && color_turno == BLANCO) {

			ficha_selec = NULL;
			fichas.crear_dama(pos[0], pos[1]);

			cout << "DAMA" << endl;

		}

		else if (pos[0] == 7 && color_turno == ROJO) {

			ficha_selec = NULL;
			fichas.crear_dama(pos[0], pos[1]);
			cout << "DAMA" << endl;

		}


		if (ficha_selec == NULL && seleccionada && reglaCasillaNegra(pos[0], pos[1]) && direccion_correcta(pos[0], pos[1], pos_verde[0], pos_verde[1])) //si la mueves a una casilla vacia
		{
			if (movimiento_simple(pos[0], pos[1], pos_verde[0], pos_verde[1]))
			{
				fichas.Mueve(pos_verde[0], pos_verde[1], pos[0], pos[1]);
				seleccionada = false;						
						if (turno_fallido == false) 
						{
							if (turno == rojas) turno = blancas;														//cambiamos el turno
							else turno = rojas;
						}


						else 
						{ // NOS PERMITE REPETIR EL MOVIMIENTO, YA QUE EL TURNO NO CAMBIA
								if (turno == rojas) turno = rojas;
								else turno = blancas;
								turno_fallido = false;
						}
			}
				//ESTO ESTA MAAAAAAAAAAAAAAL EL PROGRAMA PETA

			

		}
	
		
		


		//middle_pos[0] = (pos_verde[0] + pos[0]) / 2;
		//middle_pos[1] = (pos_verde[1] + pos[1]) / 2;

		//v_abs[1] = abs(pos[1] - pos_verde[1]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.
		//v_abs[0] = abs(pos[0] - pos_verde[0]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.


		//int ady_pos_1[2];


		//ady_pos_1[0] = pos[0] + 1;
		//ady_pos_1[1] = pos[1] + 1;

		//int ady_pos_2[2];

		//ady_pos_2[0] = pos[0] - 1;
		//ady_pos_2[1] = pos[1] - 1;

		//int ady_pos_3[2];

		//ady_pos_3[0] = pos[0] + 1;
		//ady_pos_3[1] = pos[1] - 1;

		//int ady_pos_4[2];

		//ady_pos_4[0] = pos[0] - 1;
		//ady_pos_4[1] = pos[1] + 1;


		//int jump_pos_1[2];


		//jump_pos_1[0] = ady_pos_1[0] + 1;
		//jump_pos_1[1] = ady_pos_1[1] + 1;

		//int jump_pos_2[2];

		//jump_pos_2[0] = ady_pos_2[0] - 1;
		//jump_pos_2[1] = ady_pos_2[1] - 1;

		//int jump_pos_3[2];

		//jump_pos_3[0] = ady_pos_3[0] + 1;
		//jump_pos_3[1] = ady_pos_3[1] - 1;

		//int jump_pos_4[2];

		//jump_pos_4[0] = ady_pos_4[0] - 1;
		//jump_pos_4[1] = ady_pos_4[1] + 1;




		//	if (tablero[pos_verde[0]][pos_verde[1]].GetTipo() == DAMA) {


		//		if (v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == ROJO) {	// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

		//			if (v_abs[0] == 2 && v_abs[1] == 2) {

		//				if (tablero[middle_pos[0]][middle_pos[1]].GetEstado() == OCUPADO && tablero[middle_pos[0]][middle_pos[1]].GetColor() == BLANCO) {

		//					tablero[middle_pos[0]][middle_pos[1]].BorraFicha(middle_pos[0], middle_pos[1], color_turno);
		//					tablero[middle_pos[0]][middle_pos[1]].SetEstado(VACIO);
		//					tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//					tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//					tablero[pos[0]][pos[1]].SetTipo(DAMA);
		//					tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//					cout << pos[0] << "," << pos[1] << endl;
		//					seleccionada = false;

		//					if (tablero[ady_pos_1[0]][ady_pos_1[1]].GetEstado() == OCUPADO && tablero[ady_pos_1[0]][ady_pos_1[1]].GetColor() == BLANCO) {

		//						cout << "OCUPADA_1" << endl;

		//						if (tablero[jump_pos_1[0]][jump_pos_1[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_1[0]][ady_pos_1[1]].BorraFicha(ady_pos_1[0], ady_pos_1[1], color_turno);
		//							tablero[ady_pos_1[0]][ady_pos_1[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetTipo(DAMA);
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_1[0];

		//							cout << "MOVIDO_1" << endl;
		//							cout << jump_pos_1[0] << "," << jump_pos_1[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_2[0]][ady_pos_2[1]].GetEstado() == OCUPADO && tablero[ady_pos_2[0]][ady_pos_2[1]].GetColor() == BLANCO) {

		//						cout << "OCUPADA_2" << endl;

		//						if (tablero[jump_pos_2[0]][jump_pos_2[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_2[0]][ady_pos_2[1]].BorraFicha(ady_pos_2[0], ady_pos_2[1], color_turno);
		//							tablero[ady_pos_2[0]][ady_pos_2[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetTipo(DAMA);
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_2[0];
		//							cout << "MOVIDO_2" << endl;
		//							cout << jump_pos_2[0] << "," << jump_pos_2[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_3[0]][ady_pos_3[1]].GetEstado() == OCUPADO && tablero[ady_pos_3[0]][ady_pos_3[1]].GetColor() == BLANCO) {


		//						cout << "OCUPADA_3" << endl;

		//						if (tablero[jump_pos_3[0]][jump_pos_3[1]].GetEstado() == VACIO) {


		//							tablero[ady_pos_3[0]][ady_pos_3[1]].BorraFicha(ady_pos_3[0], ady_pos_3[1], color_turno);
		//							tablero[ady_pos_3[0]][ady_pos_3[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetTipo(DAMA);
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_3[0];
		//							cout << "MOVIDO_3" << endl;
		//							cout << jump_pos_3[0] << "," << jump_pos_3[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_4[0]][ady_pos_4[1]].GetEstado() == OCUPADO && tablero[ady_pos_4[0]][ady_pos_4[1]].GetColor() == BLANCO) {

		//						cout << "OCUPADA_4" << endl;

		//						if (tablero[jump_pos_4[0]][jump_pos_4[1]].GetEstado() == VACIO) {
		//							tablero[ady_pos_4[0]][ady_pos_4[1]].BorraFicha(ady_pos_4[0], ady_pos_4[1], color_turno);
		//							tablero[ady_pos_4[0]][ady_pos_4[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetTipo(DAMA);
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_4[0];
		//							cout << "MOVIDO_4" << endl;
		//							cout << jump_pos_4[0] << "," << jump_pos_4[1] << endl;

		//						}
		//						else {


		//						}
		//					}

		//					seleccionada = false;

		//				}
		//				else {

		//					turno_fallido = true;
		//					seleccionada = false;
		//					tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);

		//				}
		//			}
		//			else if ((v_abs[0] == 1 && v_abs[1] == 1)) {
		//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//				tablero[pos[0]][pos[1]].SetTipo(DAMA);
		//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//				seleccionada = false;
		//			}


		//		}


		//		else if (v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == BLANCO) {	// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

		//			if (v_abs[0] == 2 && v_abs[1] == 2) {

		//				if (tablero[middle_pos[0]][middle_pos[1]].GetEstado() == OCUPADO && tablero[middle_pos[0]][middle_pos[1]].GetColor() == ROJO) {

		//					tablero[middle_pos[0]][middle_pos[1]].BorraFicha(middle_pos[0], middle_pos[1], color_turno);
		//					tablero[middle_pos[0]][middle_pos[1]].SetEstado(VACIO);
		//					tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//					tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//					tablero[pos[0]][pos[1]].SetTipo(DAMA);
		//					tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//					cout << pos[0] << "," << pos[1] << endl;
		//					seleccionada = false;

		//					if (tablero[ady_pos_1[0]][ady_pos_1[1]].GetEstado() == OCUPADO && tablero[ady_pos_1[0]][ady_pos_1[1]].GetColor() == ROJO) {

		//						cout << "OCUPADA_1" << endl;

		//						if (tablero[jump_pos_1[0]][jump_pos_1[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_1[0]][ady_pos_1[1]].BorraFicha(ady_pos_1[0], ady_pos_1[1], color_turno);
		//							tablero[ady_pos_1[0]][ady_pos_1[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetTipo(DAMA);
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_1[0];

		//							cout << "MOVIDO_1" << endl;
		//							cout << jump_pos_1[0] << "," << jump_pos_1[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_2[0]][ady_pos_2[1]].GetEstado() == OCUPADO && tablero[ady_pos_2[0]][ady_pos_2[1]].GetColor() == ROJO) {

		//						cout << "OCUPADA_2" << endl;

		//						if (tablero[jump_pos_2[0]][jump_pos_2[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_2[0]][ady_pos_2[1]].BorraFicha(ady_pos_2[0], ady_pos_2[1], color_turno);
		//							tablero[ady_pos_2[0]][ady_pos_2[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetTipo(DAMA);
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_2[0];
		//							cout << "MOVIDO_2" << endl;
		//							cout << jump_pos_2[0] << "," << jump_pos_2[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_3[0]][ady_pos_3[1]].GetEstado() == OCUPADO && tablero[ady_pos_3[0]][ady_pos_3[1]].GetColor() == ROJO) {


		//						cout << "OCUPADA_3" << endl;

		//						if (tablero[jump_pos_3[0]][jump_pos_3[1]].GetEstado() == VACIO) {


		//							tablero[ady_pos_3[0]][ady_pos_3[1]].BorraFicha(ady_pos_3[0], ady_pos_3[1], color_turno);
		//							tablero[ady_pos_3[0]][ady_pos_3[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetTipo(DAMA);
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_3[0];
		//							cout << "MOVIDO_3" << endl;
		//							cout << jump_pos_3[0] << "," << jump_pos_3[1] << endl;
		//						}

		//						else {


		//						}
		//					}


		//					else if (tablero[ady_pos_4[0]][ady_pos_4[1]].GetEstado() == OCUPADO && tablero[ady_pos_4[0]][ady_pos_4[1]].GetColor() == ROJO) {

		//						cout << "OCUPADA_4" << endl;

		//						if (tablero[jump_pos_4[0]][jump_pos_4[1]].GetEstado() == VACIO) {
		//							tablero[ady_pos_4[0]][ady_pos_4[1]].BorraFicha(ady_pos_4[0], ady_pos_4[1], color_turno);
		//							tablero[ady_pos_4[0]][ady_pos_4[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetTipo(DAMA);
		//							tablero[jump_pos_4[0]][jump_pos_4[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_4[0];
		//							cout << "MOVIDO_4" << endl;
		//							cout << jump_pos_4[0] << "," << jump_pos_4[1] << endl;

		//						}
		//						else {


		//						}
		//					}
		//					seleccionada = false;

		//				}
		//				else {

		//					turno_fallido = true;
		//					seleccionada = false;
		//					tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);

		//				}
		//			}
		//			else if ((v_abs[0] == 1 && v_abs[1] == 1)) {
		//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//				tablero[pos[0]][pos[1]].SetTipo(DAMA);
		//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//				seleccionada = false;
		//			}


		//		}




		//		else { //EN CASO DE ERROR EN EL NUMERO DE UNIDADES QUE QUEREMOS MOVERNOS, O EN CASO DE QUERER IR HACIA ATRAS, NOS MANDA A REPETIR EL MOVIMIENTO.
		//			turno_fallido = true;
		//			seleccionada = false;
		//			tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);

		//		}

		//		if (turno_fallido == false) {

		//			if (turno == rojas) turno = blancas;														//cambiamos el turno
		//			else turno = rojas;
		//		}


		//		else { // NOS PERMITE REPETIR EL MOVIMIENTO, YA QUE EL TURNO NO CAMBIA
		//			if (turno == rojas) turno = rojas;
		//			else turno = blancas;
		//			turno_fallido = false;
		//		}

		//	}

		//	else {
		//		if (pos_verde[0] < pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == ROJO) {	// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

		//			if (v_abs[0] == 2 && v_abs[1] == 2) {
		//				if (tablero[middle_pos[0]][middle_pos[1]].GetEstado() == OCUPADO && tablero[middle_pos[0]][middle_pos[1]].GetColor() == BLANCO) {

		//					tablero[middle_pos[0]][middle_pos[1]].BorraFicha(middle_pos[0], middle_pos[1], color_turno);
		//					tablero[middle_pos[0]][middle_pos[1]].SetEstado(VACIO);
		//					tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//					tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//					tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//					cout << pos[0] << "," << pos[1] << endl;
		//					seleccionada = false;

		//					if (tablero[ady_pos_1[0]][ady_pos_1[1]].GetEstado() == OCUPADO && tablero[ady_pos_1[0]][ady_pos_1[1]].GetColor() == BLANCO) {

		//						cout << "OCUPADA_1" << endl;

		//						if (tablero[jump_pos_1[0]][jump_pos_1[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_1[0]][ady_pos_1[1]].BorraFicha(ady_pos_1[0], ady_pos_1[1], color_turno);
		//							tablero[ady_pos_1[0]][ady_pos_1[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_1[0]][jump_pos_1[1]].SetColor(color_turno);												//con su color correspondiente

		//							pos[0] = jump_pos_1[0];
		//							cout << "MOVIDO_1" << endl;
		//							cout << jump_pos_1[0] << "," << jump_pos_1[1] << endl;
		//						}

		//						else {


		//						}
		//					}

		//					else if (tablero[ady_pos_3[0]][ady_pos_3[1]].GetEstado() == OCUPADO && tablero[ady_pos_3[0]][ady_pos_3[1]].GetColor() == BLANCO) {


		//						cout << "OCUPADA_3" << endl;

		//						if (tablero[jump_pos_3[0]][jump_pos_3[1]].GetEstado() == VACIO) {


		//							tablero[ady_pos_3[0]][ady_pos_3[1]].BorraFicha(ady_pos_3[0], ady_pos_3[1], color_turno);
		//							tablero[ady_pos_3[0]][ady_pos_3[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_3[0]][jump_pos_3[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_3[0];
		//							cout << "MOVIDO_3" << endl;
		//							cout << jump_pos_3[0] << "," << jump_pos_3[1] << endl;
		//						}
		//						else {


		//						}

		//					}



		//					seleccionada = false;

		//				}
		//				else {
		//					turno_fallido = true;
		//					seleccionada = false;
		//					tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);
		//				}
		//			}

		//			else if ((v_abs[0] == 1 && v_abs[1] == 1)) {
		//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//				seleccionada = false;
		//			}

		//		}

		//		else if (pos_verde[0] > pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == BLANCO) {// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.

		//			if (v_abs[0] == 2 && v_abs[1] == 2) {
		//				if (tablero[middle_pos[0]][middle_pos[1]].GetEstado() == OCUPADO && tablero[middle_pos[0]][middle_pos[1]].GetColor() == ROJO) {

		//					tablero[middle_pos[0]][middle_pos[1]].BorraFicha(middle_pos[0], middle_pos[1], color_turno);
		//					tablero[middle_pos[0]][middle_pos[1]].SetEstado(VACIO);
		//					tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//					tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//					tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//					seleccionada = false;


		//					if (tablero[ady_pos_2[0]][ady_pos_2[1]].GetEstado() == OCUPADO && tablero[ady_pos_2[0]][ady_pos_2[1]].GetColor() == ROJO) {

		//						cout << "OCUPADA_2" << endl;

		//						if (tablero[jump_pos_2[0]][jump_pos_2[1]].GetEstado() == VACIO) {

		//							tablero[ady_pos_2[0]][ady_pos_2[1]].BorraFicha(ady_pos_2[0], ady_pos_2[1], color_turno);
		//							tablero[ady_pos_2[0]][ady_pos_2[1]].SetEstado(VACIO);
		//							tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//							tablero[jump_pos_2[0]][jump_pos_2[1]].SetColor(color_turno);												//con su color correspondiente
		//							pos[0] = jump_pos_2[0];
		//							cout << "MOVIDO_2" << endl;
		//							cout << jump_pos_2[0] << "," << jump_pos_2[1] << endl;
		//						}

		//						else if (tablero[ady_pos_4[0]][ady_pos_4[1]].GetEstado() == OCUPADO && tablero[ady_pos_4[0]][ady_pos_4[1]].GetColor() == BLANCO) {

		//							cout << "OCUPADA_4" << endl;

		//							if (tablero[jump_pos_4[0]][jump_pos_4[1]].GetEstado() == VACIO) {
		//								tablero[ady_pos_4[0]][ady_pos_4[1]].BorraFicha(ady_pos_4[0], ady_pos_4[1], color_turno);
		//								tablero[ady_pos_4[0]][ady_pos_4[1]].SetEstado(VACIO);
		//								tablero[pos[0]][pos[1]].BorraFicha(pos[0], pos[1], color_turno);	//eliminas la ficha
		//								tablero[jump_pos_4[0]][jump_pos_4[1]].SetEstado(OCUPADO);	//ocupamos la casilla
		//								tablero[jump_pos_4[0]][jump_pos_4[1]].SetColor(color_turno);
		//								pos[0] = jump_pos_4[0];
		//								//con su color correspondiente

		//								cout << "MOVIDO_4" << endl;
		//								cout << jump_pos_4[0] << "," << jump_pos_4[1] << endl;

		//							}

		//						}

		//						else {


		//						}
		//					}




		//					seleccionada = false;

		//				}

		//				else {
		//					turno_fallido = true;
		//					seleccionada = false;
		//					tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);
		//				}
		//			}
		//			else if ((v_abs[0] == 1 && v_abs[1] == 1)) {
		//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
		//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
		//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
		//				seleccionada = false;
		//			}

		//		}
		//		else { //EN CASO DE ERROR EN EL NUMERO DE UNIDADES QUE QUEREMOS MOVERNOS, O EN CASO DE QUERER IR HACIA ATRAS, NOS MANDA A REPETIR EL MOVIMIENTO.
		//			turno_fallido = true;
		//			seleccionada = false;
		//			tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);

		//		}

		//		if (turno_fallido == false) {

		//			if (turno == rojas) turno = blancas;														//cambiamos el turno
		//			else turno = rojas;
		//		}


		//		else { // NOS PERMITE REPETIR EL MOVIMIENTO, YA QUE EL TURNO NO CAMBIA
		//			if (turno == rojas) turno = rojas;
		//			else turno = blancas;
		//			turno_fallido = false;
		//		}

		//	}
		//}

	}



}

bool Tablero::reglaCasillaNegra(int i, int j)
{
	bool resultado;

	resultado =	(i + j) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA
	return resultado;
}

bool Tablero::ficha_en_medio(int posX, int posY, int posVerdeX, int posVerdeY)
{
	int medio_pos[2];
	int v_abs[2];
	Ficha* aux;
	v_abs[0] = abs(posX - posVerdeX);
	v_abs[1] = abs(posY - posVerdeY);

	if (v_abs[0] == 2 && v_abs[1] == 2) {
		medio_pos[0] = 0.5 * (posX + posVerdeX);
		medio_pos[1] = 0.5 * (posY + posVerdeY);
		aux = fichas.buscar_lista_ficha(medio_pos[0], medio_pos[1]);
		return (aux!= NULL) && (aux->GetColor() != turno);
	}
	return false;
}

bool Tablero::casilla_vacia(int posX, int posY) {
	return (fichas.buscar_lista_ficha(posX, posY) == NULL);
}

bool Tablero::dentro_de_tablero(int i, int j)
{
	if (i <= 7 && i >= 0 && j <= 7 && j >= 0)
	{
		return true;
	}
	return false;
}
bool Tablero::movimiento_simple(int posX, int posY, int posVerdeX, int posVerdeY)
{
	
	int v_abs[2];
	Ficha* aux;
	v_abs[0] = abs(posX - posVerdeX);
	v_abs[1] = abs(posY - posVerdeY);

	if (v_abs[0] == 1 && v_abs[1] == 1) {
		aux = fichas.buscar_lista_ficha(posX, posY);
		return (aux == NULL);
	}
	return false;
}

bool Tablero::direccion_correcta(int posX, int posY, int posVerdeX, int posVerdeY)
{
	if (turno == rojas && posX > posVerdeX)
	{
		return true;
	}
	else if (turno == blancas && posX < posVerdeX)
	{
		return true;
	}
	else return false;
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
