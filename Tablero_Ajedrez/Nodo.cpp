#include "Nodo.h"
#include <iostream>
Nodo::Nodo() {
	nhijos = 0;
	padre = 0;

}
Nodo::~Nodo() {
	this->eliminarNodo();
}

Nodo* Nodo::agregarHijo() {
	this->hijo.push_back(new Nodo);
	return this->hijo[nhijos++];
}

void Nodo::setInfo(ListaFichas _fichas) {
	fichas = _fichas;
}

ListaFichas Nodo::getInfo() {
	return fichas;
}
Nodo* Nodo::getHijo(int index) {
	if (index > nhijos) {
		std::cerr << "Fallo interno del nodo. Dimensión excedida" << std::endl;
		return hijo[nhijos - 1];
	}
	if (index < 0) {
		return hijo[0];
	}
	return hijo[index];
}

void Nodo::eliminarNodo() {
	/*El siguiente código elimina el nodo en cuestión y todos los nodos inferiores.*/

	Nodo* aux, * padre;
	aux = this;
	padre = this->padre;
	if (aux->nhijos != 0) {
		do {
			while (aux->nhijos != 0) {//Este bucle llega hasta el hijo más lejano
				aux = aux->hijo[nhijos - 1];//Salto de nodo en nodo
			}
			padre = aux->padre;
			delete aux;
			aux = padre;
			aux->nhijos--;
			aux->hijo.pop_back();
			if (aux->nhijos == 0) {
				aux = aux->padre;
			}
		} while (aux != this);
	}
	if (padre != 0) {
		int i = 0;
		for (i; i < padre->nhijos; i++) {
			if (padre->hijo[i] == this) {
				break;
			}
		}
		delete padre->hijo[i];
		padre->hijo.erase(padre->hijo.begin() + i);
		padre->nhijos--;
	}
	delete this;
}

int Nodo::getNumHijos() {
	return nhijos;
}

Nodo* Nodo::getPadre() {
	return padre;
}
