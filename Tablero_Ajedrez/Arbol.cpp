#include "Arbol.h"
#define HIJOS 3
Arbol::Arbol() {
	raiz = new Nodo;
}

Arbol::~Arbol() {
	raiz->eliminarNodo();
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
	do{
		TableroJuego.SetListaFichas(aux->getInfo());
		//El siguiente bucle permite generar todos los hijos posibles
		//de orden 1 de profundidad, a partir de la ListaFichas 
		//aportada en el paso anterior al tablero de la máquina

		for (int j = 0; j < PX_X; j + PX_X / M) {
			for (int k = 0; k < PX_Y; k + PX_Y / M) {
				//El sigiente código selecciona todas las casilla posibles del tablero, y la función SelecFicha()
				//evalúa de que sea una ficha, en cuyo caso se guarda en ficha_Selec.
				TableroJuego.ficha_Selec = NULL;
				TableroJuego.estado = Tablero::ESPERANDO_1CLICK;
				TableroJuego.SelecFicha(j, k);
				if (TableroJuego.ficha_Selec != NULL) {
					//Si ha encontrado una ficha válidad que pase a realizar 
					//una combinatoria de todas las posibles casilla de destino
					for (int l = 0; l < PX_X; l + PX_X / M) {
						for (int m = 0; m < PX_Y; m + PX_Y / M) {
							TableroJuego.estado = Tablero::ESPERANDO_2CLICK;
							TableroJuego.SelecFicha(l, m);
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
		}
		
		if (profundidad > 0) {
			if (nivel == profundidad) {
				index=buscarHijoIndice(aux);
				index++;
				while (aux->getPadre()->getNumHijos() == index) {
					aux = aux->getPadre();
					nivel--;
					if (aux == raiz) {
						break;
					}
				}
				if (aux->getNumHijos() > index) {
					aux = aux->getHijo(index);
					nivel++;
				}
			}
			else {
				aux = aux->getHijo(index);
				nivel++;
			}
			
		}
	} while (aux != raiz);
}