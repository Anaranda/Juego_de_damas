#include "Nodo.h"
#include <iostream>

Nodo::Nodo() {
	nhijos = 0;
	padre = 0;
}

Nodo* Nodo::agregarHijo() {
	this->hijo.push_back(new Nodo);
	this->hijo[nhijos]->padre = this;
	return this->hijo[nhijos++];
}

void Nodo::setInfo(ListaFichas _fichas) {
	fichas.copiaDesde(_fichas);
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

	Nodo* aux, * _padre;
	aux = this;
	_padre = padre;
	if (aux->nhijos != 0) {
		do {
			while (aux->nhijos != 0) {//Este bucle llega hasta el hijo más lejano
				aux = aux->hijo[aux->nhijos - 1];//Salto de nodo en nodo
			}
			_padre = aux->padre;
			delete aux;
			aux = _padre;
			aux->nhijos--;
			aux->hijo.pop_back();
			if (aux->nhijos != 0) {
				aux = aux->hijo[aux->nhijos - 1];
			}
		} while (aux != this);
	}
	if (aux->padre != 0) {
		int i = 0;
		for (i; i < _padre->nhijos; i++) {
			if (_padre->hijo[i] == this) {
				break;
			}
		}
		delete _padre->hijo[i];
		_padre->hijo.erase(_padre->hijo.begin() + i);
		_padre->nhijos--;
	}
	delete this;
}

void Nodo::setPadre(Nodo* _padre) {
	padre = _padre;
}

int Nodo::getNumHijos() {
	return nhijos;
}

Nodo* Nodo::getPadre() {
	return padre;
}
