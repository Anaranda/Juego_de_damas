#include "Nodo.h"
#include "tablero.h"
class Arbol {
private:
	Nodo* raiz;
	Tablero TableroJuego; //Tablero de juego de la máquina
public:
	Arbol();
	Arbol(int profundidad, ListaFichas fichas);
	virtual ~Arbol();
	void construir(int profundidad);
	void destruir();
	ListaFichas mejorJugada();

	//void cambiarRaiz(int hijo);

	Nodo* getHijo(Nodo* nodo, int hijo);
	int buscarHijoIndice(Nodo* nodo);

};