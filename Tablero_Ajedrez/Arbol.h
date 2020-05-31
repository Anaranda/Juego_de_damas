#include "Nodo.h"
#include "tablero.h"
class Arbol {
private:
	Nodo* raiz;
	Tablero TableroJuego; //Tablero de juego de la máquina
public:
	Arbol();
	virtual ~Arbol();
	void construir(int profundidad);
	Nodo* getHijo(Nodo* nodo, int hijo);
	int buscarHijoIndice(Nodo* nodo);

};