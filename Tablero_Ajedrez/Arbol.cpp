#include "Arbol.h"
#define HIJOS 3
Arbol::Arbol() {
	raiz = new Nodo;
}

Arbol::~Arbol() {
	raiz->eliminarNodo();
}

Arbol::Arbol(int profundidad, ListaFichas fichas) {
	raiz = new Nodo;
	raiz->setInfo(fichas);
	construir(profundidad);
}

Nodo* Arbol::getHijo(Nodo* nodo, int index) {
	return nodo->getHijo(index);
}

int Arbol::buscarHijoIndice(Nodo* nodo) {
	//Esta función indica qué posición ocupa este nodo en los hijos del padre
	for (int i = 0; i < nodo->getPadre()->getNumHijos(); i++) {
		if (nodo->getPadre()->getHijo(i) == nodo) {
			return i;
		}
	}
}

void Arbol::construir(int profundidad) {
	Nodo* aux, *hijoAux;
	aux = raiz;
	int nivel = 0;
	int index = 0;
	TableroJuego.inStateHUMAN = true;
	TableroJuego.inPlayCPU = true;
	bool hayFinDeJuego = false;

	do{
		
		//El siguiente bucle permite generar todos los hijos posibles
		//del orden de profundidad indicado, a partir de la ListaFichas 
		//aportada en el paso anterior al tablero de la máquina

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {

				for (int k = 0; k < M; k++) {
					for (int l = 0; l < M; l++) {

						TableroJuego.SetListaFichas(aux->getInfo());
						if (nivel % 2 == 0)TableroJuego.turno = ROJO;
						else if (nivel % 2 == 1)TableroJuego.turno = BLANCO;

						//El sigiente código selecciona todas las casilla posibles del tablero, y la función SelecFicha()
						//evalúa de que sea una ficha, en cuyo caso se guarda en ficha_Selec.
						TableroJuego.ficha_Selec = NULL;
						TableroJuego.estado = Tablero::ESPERANDO_1CLICK;
					
						TableroJuego.SelecFicha(i * PX_X / M, j * PX_Y / M);
						if (TableroJuego.ficha_Selec == NULL) continue;

						//Si ha encontrado una ficha válidad que pase a realizar 
						//una combinatoria de todas las posibles casilla de destino

						TableroJuego.SelecFicha(k * PX_X / M, l * PX_X / M);
						if (aux->getInfo() != TableroJuego.GetListaFichas()) {

							//Si se ha realizado algún cambio en la posición de las fichas 
							//del tablero, entonces es que se ha realizado un movimiento, 
							//y por tanto se genera un nuevo tablero posible

							hijoAux = aux->agregarHijo();
							hijoAux->setInfo(TableroJuego.GetListaFichas());
							
						}
					}
				}
			}
		}
		
		//ALGORITMO DE RECORRIDO DE NODOS

		for (int i = 0; i < aux->getNumHijos(); i++) {
			if (!aux->getHijo(i)->getInfo().buscar_lista_color(ROJO) ||
				!aux->getHijo(i)->getInfo().buscar_lista_color(BLANCO)) {
				hayFinDeJuego = true;
				break;
			}
		}
		if (profundidad > 0 && !hayFinDeJuego) {
			if (nivel == profundidad) {
				do {
					index = buscarHijoIndice(aux);
					index++;
					aux = aux->getPadre();
					nivel--;
				} while ((aux->getNumHijos() == index) && (aux != raiz));

				if (aux->getNumHijos() > index) {
					aux = aux->getHijo(index);
					index = 0;
					nivel++;
				}
			}
			else {

				aux = aux->getHijo(index);
				nivel++;
			}

		}
	} while (aux != raiz && !hayFinDeJuego);
}


void Arbol::destruir() {
	delete this;
}

ListaFichas Arbol::mejorJugada() {

	Nodo* aux = raiz, * mejorNodo = NULL;//mejorNodo es el nodo con la mejor jugada final
	float ratioFichas = 0;
	int indice = 0;//Garantiza un recorrido completo por el árbol
	int nivel = 0;
	do {
		while (aux->getNumHijos() != 0) {//Este bucle llega hasta el hijo más lejano
			aux = aux->getHijo(indice);//Salto de nodo en nodo
			nivel++;
		}
		aux = aux->getPadre();
		nivel--;
		for (int i = 0; i < aux->getNumHijos(); i++) {
			aux = aux->getHijo(i);
			nivel++;
			//En el siguiente condicional se evalúa la característica
			//elegida para comparar. En este caso, es la jugada que maximice la
			//relación entre las fichas rojas y las blancas

			float ratioNodo = aux->getInfo().ratioFichas();

			if (ratioNodo > ratioFichas){
				ratioFichas = ratioNodo;
				mejorNodo = aux;
			}
						
			aux = aux->getPadre();
			nivel--;
		}
		if (aux != raiz) {
			do {
				indice = buscarHijoIndice(aux);
				indice++;
				aux = aux->getPadre();
				nivel--;
			} while ((indice == aux->getNumHijos()) && (aux != raiz));

			if (aux->getNumHijos() > indice) {
				aux = aux->getHijo(indice);
				indice = 0;
				nivel++;
			}
		}
	} while (aux != raiz);
	aux = mejorNodo;
	while (aux->getPadre() != raiz) {
		//Este bucle indicará cuál es el siguiente movimiento
		//al actual para lograr la jugada presente en el nodo mejorNodo
		aux = aux->getPadre();
	}
	return aux->getInfo();
}