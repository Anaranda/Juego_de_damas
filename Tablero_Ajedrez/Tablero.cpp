#include "Tablero.h"
#include "Arbol.h"
#include "Ficha.h"
#include <iostream>

#define M 8
#define PX_X  800
#define PX_Y  800


bool turno_fallido = false;// BOOL EN CASO DE INCUMPLIMIENTO DE RREGALS DE MOVIMIENTO
bool mov_ok = false;
bool com_ok = false;
bool ficha_roja = false;


Tablero::Tablero()
{
	/*turno = blancas;
	seleccionada = false;*/
	turno = BLANCO;
	estado = ESPERANDO_1CLICK;
}


void Tablero::Inicializa()
{
	fichas.inicializa();
}

void Tablero::SetListaFichas(ListaFichas _fichas) {
	fichas.copiaDesde(_fichas);
}

ListaFichas Tablero::GetListaFichas() {
	return fichas;
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
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Tablero::SelecFicha(int mouseX, int mouseY)
{
	//convertimos las coordenadas en el dibujo en indices de la matriz simbólica del tablero:
	int indices[2];
	//Vector2D donde_come, donde_va;

	paso_a_indices(mouseX, mouseY, indices);

	//ahora el vector indices contiene las coordenadas del click que se ha detectado
	///////////////////////////////////////////////////////////////////////
		//primer busca que ficha tiene esos indices:
	Ficha* aux = fichas.buscar_lista_ficha(indices[0], indices[1]); //si devuelve un puntero a null significa que no hay ninguna ficha con esos indices




	if (inStateHUMAN) {
		switch (estado)
		{
		case Tablero::ESPERANDO_1CLICK: //aquí se gestiona todo lo que tiene que ver con el primer click
			//El primer click solo puede ser valido si:
			//he seleccionado una ficha, es de mi color
			//en caso de que haya alguna que pueda comer, debo seleccionar esa.

			//comprueba si ha clicado sobre una ficha:
			if (aux == NULL || !ficha_mia(aux) || (fichas.posible_comida(turno) && !fichas.esFichaConComida(aux))) //si esta vacio o si no es mi ficha o existe una ficha que puede comer y aux es distinta de esa:
			{
				if(!inPlayCPU)ETSIDI::play("bin/sonidos/draughts_not_ok.wav");
				aux = NULL; //por si acaso que apunte a null aunque igual esta linea no hace falta
				break; //si clica sobre vacio, fuera del tablero, no es de su color
			}
			else //en caso de que haya una ficha, sea mia y no hay ficha que pueda comer o la hay pero la he seleccionado:
			{
				if (!inPlayCPU)ETSIDI::play("bin/sonidos/draught_ok_move.mp3");
				//guardo la ficha seleccionada
				ficha_Selec = aux;
				ficha_Selec->SetColor(VERDE);

				//ETSIDI::stopMusica();


				//cambio el estado pero no se cambia el turno ojo:
				cambio_estado();

				aux = NULL;// igual sobra pero por si acaso
				break;
			}
		case Tablero::ESPERANDO_2CLICK:

			if (ficha_Selec == aux) {//Desmarcar la ficha antes elegida
				ficha_Selec->SetColor(turno);
				ficha_Selec = NULL;
				cambio_estado();
				break;
			}

			//aquí se gestiona todo lo que tiene que ver con el segundo click
			//el segundo click es correcto si:
				//1- la casilla está vacia
				//2- es dirección correcta y 1 máx si no come y 2 máx si puede comer
				//3- si come, y no puede seguir comiendo esa posición (el click es correcto pero sigue )

			//en el segundo click tiene que:
			//moverse a un sitio vacio:
				//si esta el sitio vacio, direccion correcta, es negro y es de distancia 1 !Y NO PODÍA COMER!
			//comer:
				//hay una ficha enemiga en medio y distancia 2 (si puede seguir comiendo se mueve a ese sitio pero no cambia el turno ni el estado)
			//coronar:
				//mueve a casilla negra, direccion correcta, distancia 1 y posicion final final última contraria (blancas fila 0 y rojas fila 7) Y ERES UN PEON!!!!
			//MOVER A UN SITIO VACIO
			if (muevo_a_vacio_simple(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				!fichas.posible_comida(turno))
			{
				//si se cumple esto puedo realizar mi movimiento:
				ficha_Selec->Mueve(indices[0], indices[1]);
				ficha_Selec->SetColor(turno);
				if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO)) {

					fichas.convertir_a_dama(indices[0], indices[1]);
				}
				cambio_turno();
				cambio_estado();
				ficha_Selec = NULL; //Es importante esto para olvidar la ficha anterior seleccionada
				break;
			}
			

			else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec))
			{
				int incrementoX = (indices[0] - ficha_Selec->GetPosX());
				int incrementoY = (indices[1] - ficha_Selec->GetPosY());
				fichas.eliminar((incrementoX / 2) + ficha_Selec->GetPosX(), (incrementoY / 2) + ficha_Selec->GetPosY());
				ficha_Selec->Mueve(indices[0], indices[1]);
				ficha_Selec->SetColor(turno);
				if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO))
				{
					ficha_Selec = fichas.convertir_a_dama(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
				}
				indices[0] += incrementoX;
				indices[1] += incrementoY;
				if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
					fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec)) {
					cambio_estado();
					break;
				}
				else {
					cambio_turno();
					cambio_estado();
					ficha_Selec = NULL;
				}

			}
			else {
				if (inPlayCPU) {
					cambio_estado();
					ficha_Selec->SetColor(turno);
					ficha_Selec = NULL;
				}
			}
			break;

			//if (fin_de_juego() == true) {

			////	//estado_inicial = true;
			////	cout << "HAS GANAO" << endl;
			////	//cambio_turno();

			//	ficha_Selec = NULL;
			//	break;
			//	

			////	/*ETSIDI::setTextColor(0, 255, 0);
			////	ETSIDI::setFont("Arcadepix Plus.ttf", 100);
			////	ETSIDI::printxy("Has ganado", 100.0, 100.0, 0.0);*/
			////	//system("cls");

			////	//CoordinadorEtsiDamas::state = INIJUEGO;
			////	//hacemos llamada al destructor y nos a

			//}


		}
	}

	else if (inStateCPU) {

		if (turno == BLANCO) {

			switch (estado)
			{
			case Tablero::ESPERANDO_1CLICK: //aquí se gestiona todo lo que tiene que ver con el primer click
				//El primer click solo puede ser valido si:
				//he seleccionado una ficha, es de mi color
				//en caso de que haya alguna que pueda comer, debo seleccionar esa.

				//comprueba si ha clicado sobre una ficha:
				if (aux == NULL || !ficha_mia(aux) || (fichas.posible_comida(turno) && !fichas.esFichaConComida(aux))) //si esta vacio o si no es mi ficha o existe una ficha que puede comer y aux es distinta de esa:
				{
					ETSIDI::play("bin/sonidos/draughts_not_ok.wav");
					aux = NULL; //por si acaso que apunte a null aunque igual esta linea no hace falta
					break; //si clica sobre vacio, fuera del tablero, no es de su color
				}
				else //en caso de que haya una ficha, sea mia y no hay ficha que pueda comer o la hay pero la he seleccionado:
				{
					ETSIDI::play("bin/sonidos/draught_ok_move.mp3");
					//guardo la ficha seleccionada
					ficha_Selec = aux;
					ficha_Selec->SetColor(VERDE);

					//ETSIDI::stopMusica();


					//cambio el estado pero no se cambia el turno ojo:
					cambio_estado();

					aux = NULL;// igual sobra pero por si acaso
					break;
				}
			case Tablero::ESPERANDO_2CLICK:

				if (ficha_Selec == aux) {//Desmarcar la ficha antes elegida
					ficha_Selec->SetColor(turno);
					ficha_Selec = NULL;
					cambio_estado();
					break;
				}

				//aquí se gestiona todo lo que tiene que ver con el segundo click
				//el segundo click es correcto si:
					//1- la casilla está vacia
					//2- es dirección correcta y 1 máx si no come y 2 máx si puede comer
					//3- si come, y no puede seguir comiendo esa posición (el click es correcto pero sigue )

				//en el segundo click tiene que:
				//moverse a un sitio vacio:
					//si esta el sitio vacio, direccion correcta, es negro y es de distancia 1 !Y NO PODÍA COMER!
				//comer:
					//hay una ficha enemiga en medio y distancia 2 (si puede seguir comiendo se mueve a ese sitio pero no cambia el turno ni el estado)
				//coronar:
					//mueve a casilla negra, direccion correcta, distancia 1 y posicion final final última contraria (blancas fila 0 y rojas fila 7) Y ERES UN PEON!!!!
				//MOVER A UN SITIO VACIO
				if (muevo_a_vacio_simple(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
					!fichas.posible_comida(turno))
				{
					//si se cumple esto puedo realizar mi movimiento:
					ficha_Selec->Mueve(indices[0], indices[1]);
					ficha_Selec->SetColor(turno);
					if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO)) {

						fichas.convertir_a_dama(indices[0], indices[1]);
					}
					cambio_turno();
					cambio_estado();
					ficha_Selec = NULL; //Es importante esto para olvidar la ficha anterior seleccionada
					break;
				}
				//else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				//	fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec)) {
				//	do {
				//		int incrementoX = (indices[0] - ficha_Selec->GetPosX());
				//		int incrementoY = (indices[1] - ficha_Selec->GetPosY());
				//		fichas.eliminar((incrementoX / 2) + ficha_Selec->GetPosX(), (incrementoY / 2) + ficha_Selec->GetPosY());
				//		ficha_Selec->Mueve(indices[0], indices[1]);
				//		ficha_Selec->SetColor(turno);
				//		if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO)) {
				//			ficha_Selec = fichas.convertir_a_dama(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
				//		}
				//		indices[0] += incrementoX;
				//		indices[1] += incrementoY;
				//	} while (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				//		fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec));
				//	cambio_turno();
				//	cambio_estado();
				//	ficha_Selec = NULL;
				//}

				else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
					fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec))
				{
					int incrementoX = (indices[0] - ficha_Selec->GetPosX());
					int incrementoY = (indices[1] - ficha_Selec->GetPosY());
					fichas.eliminar((incrementoX / 2) + ficha_Selec->GetPosX(), (incrementoY / 2) + ficha_Selec->GetPosY());
					ficha_Selec->Mueve(indices[0], indices[1]);
					ficha_Selec->SetColor(turno);
					if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO))
					{
						ficha_Selec = fichas.convertir_a_dama(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
					}
					indices[0] += incrementoX;
					indices[1] += incrementoY;
					if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
						fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec)) {
						cout << "Encuentro doble comida" << endl;
						cambio_estado();
						break;
					}
					else {

						cambio_turno();
						cambio_estado();
						ficha_Selec = NULL;
					}
				}
				break;

				//if (fin_de_juego() == true) {

				////	//estado_inicial = true;
				////	cout << "HAS GANAO" << endl;
				////	//cambio_turno();

				//	ficha_Selec = NULL;
				//	break;
				//	

				////	/*ETSIDI::setTextColor(0, 255, 0);
				////	ETSIDI::setFont("Arcadepix Plus.ttf", 100);
				////	ETSIDI::printxy("Has ganado", 100.0, 100.0, 0.0);*/
				////	//system("cls");

				////	//CoordinadorEtsiDamas::state = INIJUEGO;
				////	//hacemos llamada al destructor y nos a

				//}


			}

		}

		else if (turno == ROJO) {


			//estado = ESPERANDO_2CLICK;
			cout << "CPUs TURN!" << endl;
			//ETSIDI::play("bin/sonidos/draughts_not_ok.wav");

			if (fichas.posible_comida(ROJO) == NULL) {

				cout << "NO PUEDO COMER, MUEVO ALEATORIAMENTE" << endl;
				int i; int j;


				while (mov_ok != true) {

					i = ETSIDI::lanzaDado(8, 0);
					j = ETSIDI::lanzaDado(8, 0);

					cout << "Ficha que analizo: " << i << "," << j << endl;
					cpu = fichas.buscar_lista_ficha(i, j);
					ficha_Selec = cpu;
					//cout << cpu->GetPosX() << cpu->GetPosY() << endl;


					if (cpu != NULL && cpu->GetColor() == ROJO) {

						cout << "DETECTO FICHA ROJA, vamos que la ficha es roja" << endl;


						//ANALIZAMOS POSICIÓN INFERIOR IZDA

						if (((fichas.pincho_en_ficha(cpu->GetPosX() + 1, cpu->GetPosY() - 1) == NULL)) &&
							dentro_de_tablero(cpu->GetPosX() + 1, cpu->GetPosY() - 1) == true &&
							reglaCasillaNegra(cpu->GetPosX() + 1, cpu->GetPosY() - 1)) {

							cout << "Ficha seleccionada: " << cpu->GetPosX() << cpu->GetPosY() << endl;

							cout << "Posicion diagonal izda: " << (cpu->GetPosX()) + 1 << (cpu->GetPosY()) - 1 << endl;

							cpu->Mueve(cpu->GetPosX() + 1, cpu->GetPosY() - 1);
							cout << "MUEVO EN DIAGONAL IZDA" << endl;
							if (cpu->GetPosX() == 7) {

								fichas.convertir_a_dama(cpu->GetPosX(), cpu->GetPosY());
							}
							mov_ok = true;

						}
						//else  {

						//ANALIZAMOS POSICIÓN INFERIOR DCHA

						else if (((fichas.pincho_en_ficha(cpu->GetPosX() + 1, cpu->GetPosY() + 1) == NULL)) && dentro_de_tablero(cpu->GetPosX() + 1, cpu->GetPosY() + 1) && reglaCasillaNegra(cpu->GetPosX() + 1, cpu->GetPosY() + 1)) {

							cout << "Ficha seleccionada: " << cpu->GetPosX() << cpu->GetPosY() << endl;

							cout << "Posicion diagonal dcha: " << (cpu->GetPosX()) + 1 << (cpu->GetPosY()) + 1 << endl;


							cpu->Mueve(cpu->GetPosX() + 1, cpu->GetPosY() + 1);
							cout << "MUEVO EN DIAGONAL DCHA" << endl;
							if (cpu->GetPosX() == 7) {

								fichas.convertir_a_dama(cpu->GetPosX(), cpu->GetPosY());
							}
							mov_ok = true;

						}

						//ANALIZAMOS POSICIÓN SUPERIOR IZDA (DAMA)

						else if (cpu->GetTipo() == DAMA) {
							if (((fichas.pincho_en_ficha(cpu->GetPosX() - 1, cpu->GetPosY() - 1) == NULL)) && dentro_de_tablero(cpu->GetPosX() - 1, cpu->GetPosY() - 1) && reglaCasillaNegra(cpu->GetPosX() - 1, cpu->GetPosY() - 1)) {

								cout << "Ficha seleccionada: " << cpu->GetPosX() << cpu->GetPosY() << endl;

								cout << "Posicion diagonal sup izda: " << (cpu->GetPosX()) - 1 << (cpu->GetPosY()) - 1 << endl;

								cpu->Mueve(cpu->GetPosX() - 1, cpu->GetPosY() - 1);
								cout << "MUEVO EN DIAGONAL IZDA SUP" << endl;

								mov_ok = true;

							}
							else if (((fichas.pincho_en_ficha(cpu->GetPosX() - 1, cpu->GetPosY() + 1) == NULL)) && dentro_de_tablero(cpu->GetPosX() - 1, cpu->GetPosY() + 1) && reglaCasillaNegra(cpu->GetPosX() - 1, cpu->GetPosY() + 1)) {
								cout << "Ficha seleccionada: " << cpu->GetPosX() << cpu->GetPosY() << endl;

								cout << "Posicion diagonal sup dcha: " << (cpu->GetPosX()) - 1 << (cpu->GetPosY()) + 1 << endl;

								cpu->Mueve(cpu->GetPosX() - 1, cpu->GetPosY() + 1);
								cout << "MUEVO EN DIAGONAL DCHA SUP" << endl;

								mov_ok = true;
							}
						}

						else {

							cpu = NULL;
							cout << "NO" << endl;
							mov_ok = false;


						}
						//}

					}
				}
				cambio_turno();
				mov_ok = false;

			}

			else {

				cout << "PUEDO COMER, BUSCO ESA FICHA" << endl;

				int m; int n;

				while (com_ok != true) {

					cpu = NULL;
					ficha_Selec = NULL;
					ficha_Selec_2 = NULL;
					ficha_Selec_3 = NULL;
					ficha_Selec_4 = NULL;


					m = ETSIDI::lanzaDado(8, 0);
					n = ETSIDI::lanzaDado(8, 0);

					//cout << m << "/" << n << endl;
					cpu = fichas.buscar_lista_ficha(m, n);

					ficha_Selec = cpu;
					ficha_Selec_2 = cpu;
					ficha_Selec_3 = cpu;
					ficha_Selec_4 = cpu;

					if (cpu != NULL && cpu->GetColor() == ROJO) {


						cout << "Ficha seleccionada: " << cpu->GetPosX() << cpu->GetPosY() << endl;


						//ficha_Selec->SetPos(ficha_Selec->GetPosX() + 1, ficha_Selec->GetPosY() - 1);
						if (dentro_de_tablero(ficha_Selec->GetPosX() + 1, ficha_Selec->GetPosY() - 1) == true && fichas.buscar_lista_ficha((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1) != NULL) {

							ficha_Selec = fichas.buscar_lista_ficha((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1);
							cout << "Ficha diagonal izda: " << ficha_Selec->GetPosX() << ficha_Selec->GetPosY() << endl;
							cout << "Color de ficha diagonal: " << ficha_Selec->GetColor() << endl;

							if (ficha_Selec->GetColor() == BLANCO) {

								cout << "COMESTIBLE_DIAGONAL_IZDA" << endl;

								if (((fichas.pincho_en_ficha((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1) == NULL)) && dentro_de_tablero((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1) == true && reglaCasillaNegra((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1)) {
									cout << "Ficha que me como: " << ficha_Selec->GetPosX() << ficha_Selec->GetPosY() << endl;
									cpu->Mueve((ficha_Selec->GetPosX()) + 1, (ficha_Selec->GetPosY()) - 1);
									fichas.eliminar(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
									if (cpu->GetPosX() == 7) {

										fichas.convertir_a_dama(cpu->GetPosX(), cpu->GetPosY());
									}
									cout << "COME_OK_1" << endl;
									com_ok = true;
									if (fichas.posible_comida(ROJO)) com_ok = false;
								}
							}
						}

						if (com_ok != true && dentro_de_tablero((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1) == true && fichas.buscar_lista_ficha((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1) != NULL) {
							//ficha_Selec_2->SetPos(ficha_Selec_2->GetPosX() + 1, ficha_Selec_2->GetPosY() - 1);
							ficha_Selec_2 = fichas.buscar_lista_ficha((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1);
							cout << "Ficha diagonal dcha: " << ficha_Selec_2->GetPosX() << ficha_Selec_2->GetPosY() << endl;
							cout << "Color de ficha diagonal: " << ficha_Selec_2->GetColor() << endl;

							if (ficha_Selec_2->GetColor() == BLANCO) {

								cout << "COMESTIBLE_DIAGONAL_DCHA" << endl;

								if (((fichas.pincho_en_ficha((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1) == NULL)) && dentro_de_tablero((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1) == true && reglaCasillaNegra((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1)) {
									cout << "Ficha quue me como: " << ficha_Selec_2->GetPosX() << ficha_Selec_2->GetPosY() << endl;
									cpu->Mueve((ficha_Selec_2->GetPosX()) + 1, (ficha_Selec_2->GetPosY()) + 1);
									fichas.eliminar(ficha_Selec_2->GetPosX(), ficha_Selec_2->GetPosY());
									if (cpu->GetPosX() == 7) {

										fichas.convertir_a_dama(cpu->GetPosX(), cpu->GetPosY());
									}

									cout << "COME_OK_2" << endl;
									com_ok = true;
									if (fichas.posible_comida(ROJO)) com_ok = false;
								}
							}
						}
						if (com_ok != true && ficha_Selec_3->GetTipo() == DAMA && dentro_de_tablero((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1) == true && fichas.buscar_lista_ficha((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1) != NULL) {

							ficha_Selec_3 = fichas.buscar_lista_ficha((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1);
							cout << "Ficha diagonal sup izda: " << ficha_Selec_3->GetPosX() << ficha_Selec_3->GetPosY() << endl;
							cout << "Color de ficha diagonal: " << ficha_Selec_3->GetColor() << endl;

							if (ficha_Selec_3->GetColor() == BLANCO) {

								cout << "COMESTIBLE_DIAGONAL_SUP_IZDA" << endl;

								if (((fichas.pincho_en_ficha((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1) == NULL)) && dentro_de_tablero((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1) == true && reglaCasillaNegra((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1)) {
									cout << "Ficha quue me como: " << ficha_Selec_3->GetPosX() << ficha_Selec_3->GetPosY() << endl;
									cpu->Mueve((ficha_Selec_3->GetPosX()) - 1, (ficha_Selec_3->GetPosY()) - 1);
									fichas.eliminar(ficha_Selec_3->GetPosX(), ficha_Selec_3->GetPosY());

									cout << "COME_OK_1_DAMA" << endl;
									com_ok = true;
									if (fichas.posible_comida(ROJO)) com_ok = false;
								}
							}
						}

						if (com_ok != true && ficha_Selec_4->GetTipo() == DAMA && dentro_de_tablero((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1) == true && fichas.buscar_lista_ficha((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1) != NULL) {
							//ficha_Selec_2->SetPos(ficha_Selec_2->GetPosX() + 1, ficha_Selec_2->GetPosY() - 1);
							ficha_Selec_4 = fichas.buscar_lista_ficha((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1);
							cout << "Ficha diagonal dcha: " << ficha_Selec_4->GetPosX() << ficha_Selec_4->GetPosY() << endl;
							cout << "Color de ficha diagonal: " << ficha_Selec_4->GetColor() << endl;

							if (ficha_Selec_4->GetColor() == BLANCO) {

								cout << "COMESTIBLE_DIAGONAL_SUP_DCHA" << endl;

								if (((fichas.pincho_en_ficha((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1) == NULL)) && dentro_de_tablero((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1) == true && reglaCasillaNegra((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1)) {
									cout << "Ficha quue me como: " << ficha_Selec_4->GetPosX() << ficha_Selec_4->GetPosY() << endl;
									cpu->Mueve((ficha_Selec_4->GetPosX()) - 1, (ficha_Selec_4->GetPosY()) + 1);
									fichas.eliminar(ficha_Selec_4->GetPosX(), ficha_Selec_4->GetPosY());

									cout << "COME_OK_2_DAMA" << endl;
									com_ok = true;
									if (fichas.posible_comida(ROJO)) com_ok = false;
								}
							}
						}



						/*if (1){

							cpu = NULL;
							ficha_Selec = NULL;
							ficha_Selec_2 = NULL;
							cout << "NO_COMO" << endl;
							com_ok = false;


						}*/
					}

				}

				cambio_turno();
				com_ok = false;

			}
		}
	}

	else if (inStateCPUArbol) {
		if (turno == BLANCO) {

			switch (estado)
			{
			case Tablero::ESPERANDO_1CLICK: //aquí se gestiona todo lo que tiene que ver con el primer click
				//El primer click solo puede ser valido si:
				//he seleccionado una ficha, es de mi color
				//en caso de que haya alguna que pueda comer, debo seleccionar esa.

				//comprueba si ha clicado sobre una ficha:
				if (aux == NULL || !ficha_mia(aux) || (fichas.posible_comida(turno) && !fichas.esFichaConComida(aux))) //si esta vacio o si no es mi ficha o existe una ficha que puede comer y aux es distinta de esa:
				{
					ETSIDI::play("bin/sonidos/draughts_not_ok.wav");
					aux = NULL; //por si acaso que apunte a null aunque igual esta linea no hace falta
					break; //si clica sobre vacio, fuera del tablero, no es de su color
				}
				else //en caso de que haya una ficha, sea mia y no hay ficha que pueda comer o la hay pero la he seleccionado:
				{
					ETSIDI::play("bin/sonidos/draught_ok_move.mp3");
					//guardo la ficha seleccionada
					ficha_Selec = aux;
					ficha_Selec->SetColor(VERDE);

					//ETSIDI::stopMusica();


					//cambio el estado pero no se cambia el turno ojo:
					cambio_estado();

					aux = NULL;// igual sobra pero por si acaso
					break;
				}
			case Tablero::ESPERANDO_2CLICK:

				if (ficha_Selec == aux) {//Desmarcar la ficha antes elegida
					ficha_Selec->SetColor(turno);
					ficha_Selec = NULL;
					cambio_estado();
					break;
				}

				//aquí se gestiona todo lo que tiene que ver con el segundo click
				//el segundo click es correcto si:
					//1- la casilla está vacia
					//2- es dirección correcta y 1 máx si no come y 2 máx si puede comer
					//3- si come, y no puede seguir comiendo esa posición (el click es correcto pero sigue )

				//en el segundo click tiene que:
				//moverse a un sitio vacio:
					//si esta el sitio vacio, direccion correcta, es negro y es de distancia 1 !Y NO PODÍA COMER!
				//comer:
					//hay una ficha enemiga en medio y distancia 2 (si puede seguir comiendo se mueve a ese sitio pero no cambia el turno ni el estado)
				//coronar:
					//mueve a casilla negra, direccion correcta, distancia 1 y posicion final final última contraria (blancas fila 0 y rojas fila 7) Y ERES UN PEON!!!!
				//MOVER A UN SITIO VACIO
				if (muevo_a_vacio_simple(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
					!fichas.posible_comida(turno))
				{
					//si se cumple esto puedo realizar mi movimiento:
					ficha_Selec->Mueve(indices[0], indices[1]);
					ficha_Selec->SetColor(turno);
					if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO)) {

						fichas.convertir_a_dama(indices[0], indices[1]);
					}
					cambio_turno();
					cambio_estado();
					ficha_Selec = NULL; //Es importante esto para olvidar la ficha anterior seleccionada
					break;
				}
				//else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				//	fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec)) {
				//	do {
				//		int incrementoX = (indices[0] - ficha_Selec->GetPosX());
				//		int incrementoY = (indices[1] - ficha_Selec->GetPosY());
				//		fichas.eliminar((incrementoX / 2) + ficha_Selec->GetPosX(), (incrementoY / 2) + ficha_Selec->GetPosY());
				//		ficha_Selec->Mueve(indices[0], indices[1]);
				//		ficha_Selec->SetColor(turno);
				//		if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO)) {
				//			ficha_Selec = fichas.convertir_a_dama(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
				//		}
				//		indices[0] += incrementoX;
				//		indices[1] += incrementoY;
				//	} while (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
				//		fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec));
				//	cambio_turno();
				//	cambio_estado();
				//	ficha_Selec = NULL;
				//}

				else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
					fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec))
				{
					int incrementoX = (indices[0] - ficha_Selec->GetPosX());
					int incrementoY = (indices[1] - ficha_Selec->GetPosY());
					fichas.eliminar((incrementoX / 2) + ficha_Selec->GetPosX(), (incrementoY / 2) + ficha_Selec->GetPosY());
					ficha_Selec->Mueve(indices[0], indices[1]);
					ficha_Selec->SetColor(turno);

					if ((indices[0] == 7 && turno == ROJO) || (indices[0] == 0 && turno == BLANCO))
					{
						ficha_Selec = fichas.convertir_a_dama(ficha_Selec->GetPosX(), ficha_Selec->GetPosY());
					}

					indices[0] += incrementoX;
					indices[1] += incrementoY;
					if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) &&
						fichas.posible_comida(turno) && fichas.esFichaConComida(ficha_Selec)) {
						cout << "Encuentro doble comida" << endl;
						cambio_estado();
						break;
					}
					else {

						cambio_turno();
						cambio_estado();
						ficha_Selec = NULL;
					}
				}
				break;

				//if (fin_de_juego() == true) {

				////	//estado_inicial = true;
				////	cout << "HAS GANAO" << endl;
				////	//cambio_turno();

				//	ficha_Selec = NULL;
				//	break;
				//	

				////	/*ETSIDI::setTextColor(0, 255, 0);
				////	ETSIDI::setFont("Arcadepix Plus.ttf", 100);
				////	ETSIDI::printxy("Has ganado", 100.0, 100.0, 0.0);*/
				////	//system("cls");

				////	//CoordinadorEtsiDamas::state = INIJUEGO;
				////	//hacemos llamada al destructor y nos a

				//}


			}
		}
		else {
			if (fichas.buscar_lista_color(ROJO)) {
				Arbol arbol(2, fichas);
				fichas = arbol.mejorJugada();
				cambio_turno();
			}
			
		}
	}

}



bool Tablero::reglaCasillaNegra(int i, int j)
{
	bool resultado;

	resultado = (i + j) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA
	return resultado;
}

void Tablero::paso_a_indices(int mouseX, int mouseY, int* indices)
{
	//Esta función nos pasa de las coordenadas del tablero a indices de la matriz, no vuelve nada HACE PASO POR REFERENCIA DE VECTOR INDICES
	//if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	//{
	indices[1] = trunc(mouseX / (PX_X / M)); // el eje x corresponde con el indice j (COLUMNAS)
	indices[0] = trunc(mouseY / (PX_Y / M)); //el eje y corresponde con el indice i (FILAS)
//}
}

bool Tablero::ficha_mia(Ficha* ficha)
{
	//si la ficha es del color del turno entonces devuelve un true
	return (ficha->GetColor() == turno);
}

void Tablero::cambio_turno()
{
	if (turno == BLANCO)
		turno = ROJO;
	else if (turno == ROJO)
		turno = BLANCO;
}

void Tablero::cambio_estado()
{
	if (estado == ESPERANDO_1CLICK)
		estado = ESPERANDO_2CLICK;
	else if (estado == ESPERANDO_2CLICK)
		estado = ESPERANDO_1CLICK;
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


bool Tablero::movimiento_comida_simple(int posX, int posY, int posVerdeX, int posVerdeY)
{
	int v_abs[2];
	Ficha* aux;
	v_abs[0] = abs(posX - posVerdeX);
	v_abs[1] = abs(posY - posVerdeY);

	if (v_abs[0] == 2 && v_abs[1] == 2 && fichas.buscar_lista_ficha(posX, posY) == NULL
		&& fichas.buscar_lista_ficha((posX + posVerdeX) * 0.5, (posY + posVerdeY) * 0.5)!=NULL) {
		if (!ficha_mia(fichas.buscar_lista_ficha((posX + posVerdeX) * 0.5, (posY + posVerdeY) * 0.5))) {
			return (true);
		}
	}
	return false;
}

bool Tablero::direccion_correcta(int posX, int posY, int posVerdeX, int posVerdeY)
{

	if (ficha_Selec->GetTipo() == DAMA) {

		return true;
	}

	else {
		if (turno == ROJO && posX > posVerdeX)
			return true;
		else if (turno == BLANCO && posX < posVerdeX)
			return true;
		else
			return false;
	}


}

bool Tablero::muevo_a_vacio_simple(int posX, int posY, int posVerdeX, int posVerdeY)
{
	//si pincho en un sitio sin ficha, dentro del tablero, casilla negra, a distancia 1 y en la dirección correcta
	if (!fichas.pincho_en_ficha(posX, posY) &&
		dentro_de_tablero(posX, posY) &&
		reglaCasillaNegra(posX, posY) &&
		movimiento_simple(posX, posY, posVerdeX, posVerdeY) &&
		direccion_correcta(posX, posY, posVerdeX, posVerdeY))
	{
		return true;
	}
	//else if (!fichas.Pincho_en_ficha(posX, posY) && dentro_de_tablero(posX, posY) && reglaCasillaNegra(posX, posY) && movimiento_simple(posX, posY, posVerdeX, posVerdeY)&& ) {

	//	return true;
	//}
	else
		return false;
}

bool Tablero::muevo_y_como(int posX, int posY, int posVerdeX, int posVerdeY)
{

	if (!fichas.pincho_en_ficha(posX, posY) &&
		dentro_de_tablero(posX, posY) &&
		reglaCasillaNegra(posX, posY) &&
		movimiento_comida_simple(posX, posY, posVerdeX, posVerdeY) &&
		direccion_correcta(posX, posY, posVerdeX, posVerdeY)) {

		return true;
	}
	return false;
}

bool Tablero::fin_de_juego()
{

	if (fichas.buscar_lista_color(turno) == false) {

		return true;

	}
	return false;
}

void Tablero::eliminar()
{
	fichas.eliminar_fichas();
}

void Tablero::cambio_estado_juego()
{
	if (estado_inicial) estado_inicial = false;
	else estado_inicial = true;
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

