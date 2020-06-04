#include "Nodo.h"
#include "Tablero.h"

class Arbol {
private:
	Nodo* raiz;
	Tablero TableroJuego; //Tablero de juego de la m�quina
public:
	Arbol();
	Arbol(int profundidad, ListaFichas fichas);
	virtual ~Arbol();
	void construir(int profundidad);
	void destruir();
	ListaFichas mejorJugada();

	Nodo* getHijo(Nodo* nodo, int hijo);
	int buscarHijoIndice(Nodo* nodo);

};