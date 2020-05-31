#include <vector>
#include "ListaFichas.h"

using namespace std;

//Estructura del nodo: parent>>nodo>>hijos
//Parent es el nodo predecesor
//Nodo es el nodo en sí
//Hijos es el vector de nodos sucesores

class Nodo {
private:
    ListaFichas fichas;
    int nhijos;

    Nodo* padre;
    vector<Nodo*> hijo;

public:
    
    Nodo();
    ~Nodo();
    Nodo* agregarHijo();
    Nodo* getHijo(int index);
    Nodo* getPadre();
    int getNumHijos();
    void eliminarNodo();
    void setInfo(ListaFichas);
    ListaFichas getInfo();
    
};