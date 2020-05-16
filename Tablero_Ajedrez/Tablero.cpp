#include "Tablero.h"
#include "Ficha.h"
#include "ListaPeones.h"
#include <iostream>



#define M 8
#define PX_X  800
#define PX_Y  800

bool estado_inicial = true;
bool turno_fallido = false;// BOOL EN CASO DE INCUMPLIMIENTO DE RREGALS DE MOVIMIENTO


Tablero::Tablero()
{
	/*turno = blancas;
	seleccionada = false;*/
	turno = BLANCO;
	estado = ESPERANDO_1CLICK;
}

//void Tablero::dibuja()
//{
//	//peones.dibuja();
//}

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
	glTexCoord2d(0, 1); glVertex3d(0, PX_Y,-0.01);
	glTexCoord2d(1, 1); glVertex3d(PX_X, PX_Y,-0.01);
	glTexCoord2d(1, 0); glVertex3d(PX_X, 0,-0.01);
	glTexCoord2d(0, 0); glVertex3d(0, 0,-0.01);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);


}

void Tablero::SelecFicha(int button, int state, int mouseX, int mouseY)
{


	//convertimos las coordenadas en el dibujo en indices de la matriz simbólica del tablero:
	int indices[2];
	int indices_finales[2];
	Vector2D donde_come, donde_va;
	paso_a_indices(button, state, mouseX, mouseY, indices);

	//ahora el vector indices contiene las coordenadas del click que se ha detectado
	///////////////////////////////////////////////////////////////////////
		//primer busca que ficha tiene esos indices:
	Ficha* aux = fichas.buscar_lista_ficha(indices[0], indices[1]); //si devuelve un puntero a null significa que no hay ninguna ficha con esos indices
																	//puede ser porque esta fuera del tablero, xq es un sitio vacio... etc.
	switch (estado)
	{
	case Tablero::ESPERANDO_1CLICK: //aquí se gestiona todo lo que tiene que ver con el primer click
		//El primer click solo puede ser valido si:
		//he seleccionado una ficha, es de mi color
		//en caso de que haya alguna que pueda comer, debo seleccionar esa.

		//comprueba si ha clicado sobre una ficha:
		if (aux == NULL || !ficha_mia(aux) || (fichas.posible_comida(turno, &donde_come, &donde_va) != NULL && fichas.posible_comida(turno, &donde_come, &donde_va) != aux)) //si esta vacio o si no es mi ficha o existe una ficha que puede comer y aux es distinta de esa:
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
			estado = ESPERANDO_2CLICK;

			aux = NULL;// igual sobra pero por si acaso
			break;
		}
	case Tablero::ESPERANDO_2CLICK:

		if (ficha_Selec == aux) {//Desmarcar la ficha antes elegida
			ficha_Selec->SetColor(turno);
			ficha_Selec = NULL;
			estado = ESPERANDO_1CLICK;
			break;
		}

		indices_finales[0] = ficha_Selec->GetPosX();
		indices_finales[1] = ficha_Selec->GetPosY();
		//aquí se gestiona todo lo que tiene que ver con el segundo click
		//el segundo click es correcto si:
			//1- la casilla está vacia
			//2-dirección correcta y 1 máx si no come y 2 máx si puede comer
			//3-si come, y no puede seguir comiendo esa posición (el click es correcto pero sigue )

		//en el segundo click tiene que:
		//moverse a un sitio vacio:
			//si esta el sitio vacio, direccion correcta, es negro y es de distancia 1 !Y NO PODÍA COMER!
		//comer:
			//hay una ficha enemiga en medio y distancia 2 (si puede seguir comiendo se mueve a ese sitio pero no cambia el turno ni el estado)
		//coronar:
			//mueve a casilla negra, direccion correcta, distancia 1 y posicion final final última contraria (blancas fila 0 y rojas fila 7) Y ERES UN PEON!!!!

		//MOVER A UN SITIO VACIO
		if (muevo_a_vacio_simple(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) && fichas.posible_comida(turno, &donde_come, &donde_va) == NULL)
		{
			//si se cumple esto puedo realizar mi movimiento:
			ficha_Selec->Mueve(indices[0], indices[1]);
			ficha_Selec->SetColor(turno);
			if (indices[0] == 7 && turno == ROJO || indices[0] == 0 && turno == BLANCO) {

				fichas.crear_dama(indices[0], indices[1]);
			}
			cambio_turno();
			cambio_estado();
			ficha_Selec = NULL; //aqui es importante hacer esto xq sino se queda la ficha anterior seleccionada
			break;
		}

		else if (muevo_y_como(indices[0], indices[1], ficha_Selec->GetPosX(), ficha_Selec->GetPosY()) && fichas.posible_comida(turno, &donde_come, &donde_va) != NULL) {

			ficha_Selec->Mueve(indices[0], indices[1]);
			ficha_Selec->SetColor(turno);
			//cout << ficha_Selec->GetPosX() << ficha_Selec->GetPosY() << endl;
			indices_finales[0] = (ficha_Selec->GetPosX() + indices_finales[0]) / 2;
			indices_finales[1] = (ficha_Selec->GetPosY() + indices_finales[1]) / 2;
			//cout << indices_finales[0] << indices_finales[1] << endl;
			fichas.eliminar(indices_finales[0], indices_finales[1]);
			if (indices[0] == 7 && turno == ROJO || indices[0] == 0 && turno == BLANCO) {

				fichas.crear_dama(indices[0], indices[1]);
			}


			cambio_turno();
			if (fin_de_juego(turno) == true) {

				

				cout << "HAS GANAO" << endl;



				/*ETSIDI::setTextColor(0, 255, 0);
				ETSIDI::setFont("Arcadepix Plus.ttf", 100);
				ETSIDI::printxy("Has ganado", 100.0, 100.0, 0.0);*/
				//system("cls");



				//CoordinadorEtsiDamas::state = INIJUEGO;

				//hacemos llamada al destructor y nos a

			}
			cambio_estado();
			ficha_Selec = NULL; //aqui es importante hacer esto xq sino se queda la ficha anterior seleccionada
			break;
		}
		

		break;
	default:
		break;
	}
	//	
	//	//enum Turno { blancas, rojas };
	//	//Turno turno;
	//	
	//	Color ficha_selec;
	//	Color color_turno;
	//	int v_abs[2];
	//	int impar;
	//	
	//
	//	if (turno == rojas) {
	//		color_turno=ROJO;
	//	} else color_turno = BLANCO;
	//
	//
	//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	//	{
	//		pos[1] = trunc(mouseX / (PX_X / M)); // el eje x corresponde con el indice j (COLUMNAS)
	//		pos[0] = trunc(mouseY / (PX_Y / M)); //el eje y corresponde con el indice i (FILAS)
	//		impar = (pos[1] + pos[0]) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA
	//
	//		
	//
	//		if (tablero[pos[0]][pos[1]].GetEstado() == OCUPADO && seleccionada==false)	// seleccionas una ficha de tu color cuando sea tu turno	
	//		{
	//			ficha_selec = tablero[pos[0]][pos[1]].GetColor();		// Se guarda el color de la ficha seleccionada
	//			if (ficha_selec == color_turno) {						//Ha seleccionado una de sus fichas
	//				tablero[pos[0]][pos[1]].SetColor(VERDE);			//Se pone de color verde
	//				seleccionada = true;								
	//				pos_verde[0] = pos[0];								//guardamos la posicion donde esta la ficha verde
	//				pos_verde[1] = pos[1];
	//				
	//			}
	//						
	//		}
	//
	//		
	//		if (tablero[pos[0]][pos[1]].GetEstado() == VACIO && seleccionada && impar != 0)								//si la mueves a una casilla vacia
	//		{
	//
	//
	//			v_abs[1] = abs(pos[1] - pos_verde[1]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.
	//			v_abs[0] = abs(pos[0] - pos_verde[0]);// GUARDA EN UN VECTOR DE DOS COORDENADAS LOS VALORES DEL V. ABS DE LA RESTA DE LA POSICION ACTUAL CON LA POSTERIOR. ASI QUEDA RESTRINGIDO EL MOVIMIENTO A DOS UNIDADES MAX.
	//
	//			if (pos_verde[0] < pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == ROJO) {	// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.
	//
	//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
	//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
	//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
	//				seleccionada = false;
	//			}
	//
	//			else if (pos_verde[0] > pos[0] && v_abs[0] <= 2 && v_abs[1] <= 2 && v_abs[0] != 0 && v_abs[1] != 0 && color_turno == BLANCO) {// SE EVALUA PRIMERO QUE LA POSICION SIGUIENTE EN EL EJE Y PERMITE SU MOVIMIENTO. DESPUES, QUE EL MOVIMIENTO ES DE DOS UNIDADES. ADEMAS, QUE TAMPOCO SEA CERO.
	//
	//				tablero[pos_verde[0]][pos_verde[1]].BorraFicha(pos_verde[0], pos_verde[1], color_turno);	//eliminas la ficha
	//				tablero[pos[0]][pos[1]].SetEstado(OCUPADO);													//ocupamos la casilla
	//				tablero[pos[0]][pos[1]].SetColor(color_turno);												//con su color correspondiente
	//				seleccionada = false;
	//
	//			}
	//			else { //EN CASO DE ERROR EN EL NUMERO DE UNIDADES QUE QUEREMOS MOVERNOS, O EN CASO DE QUERER IR HACIA ATRAS, NOS MANDA A REPETIR EL MOVIMIENTO.
	//				turno_fallido = true;
	//				seleccionada = false;
	//				tablero[pos_verde[0]][pos_verde[1]].SetColor(color_turno);
	//
	//			}
	//
	//			if (turno_fallido == false) {
	//
	//				if (turno == rojas) turno = blancas;														//cambiamos el turno
	//				else turno = rojas;
	//			}
	//
	//
	//			else { // NOS PERMITE REPETIR EL MOVIMIENTO, YA QUE EL TURNO NO CAMBIA
	//				if (turno == rojas) turno = rojas;
	//				else turno = blancas;
	//				turno_fallido = false;
	//			}
	//
	//		}
	//	}
	//
	//	


}

bool Tablero::reglaCasillaNegra(int i, int j)
{
	bool resultado;

	resultado = (i + j) % 2; //COMPRUEBA SI LA CASILLA ES NEGRA, PARA PERMITIR O NO LA COLOCACION DE LA FICHA
	return resultado;
}

void Tablero::paso_a_indices(int button, int state, int mouseX, int mouseY, int* indices)
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
	if (estado=ESPERANDO_1CLICK)
		estado = ESPERANDO_2CLICK;
	else if (estado==ESPERANDO_2CLICK)
		estado=ESPERANDO_1CLICK;
}

bool Tablero::dentro_de_tablero(int i, int j)
{
	if (i <= 7 && i >= 0 && j <= 7 && j >= 0)
	{
		return true;
	}
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

	if (v_abs[0] == 2 && v_abs[1] == 2) {
		aux = fichas.buscar_lista_ficha(posX, posY);
		return (aux == NULL);
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
	if (!fichas.Pincho_en_ficha(posX, posY) && dentro_de_tablero(posX, posY) && reglaCasillaNegra(posX, posY) && movimiento_simple(posX, posY, posVerdeX, posVerdeY) && direccion_correcta(posX, posY, posVerdeX, posVerdeY))
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

	if (!fichas.Pincho_en_ficha(posX, posY) && dentro_de_tablero(posX, posY) && reglaCasillaNegra(posX, posY) && movimiento_comida_simple(posX, posY, posVerdeX, posVerdeY) && direccion_correcta(posX, posY, posVerdeX, posVerdeY)) {

		return true;
	}
	return false;
}

bool Tablero::fin_de_juego(Color turno)
{

	if (fichas.buscar_lista_color(turno) == false) {


		
		return true;


	}
	return false;
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
