#pragma once
#define MAX_DAMAS 24
#include "Dama.h"
class ListaDamas
{
public:
    ListaDamas();
    virtual  ~ListaDamas();



    bool agregar(Dama* d);
    void dibuja();
    void eliminar(int index);
    void eliminar(Dama* d);
    Dama* operator[](int i);
    int getNumero() { return num; }
    Dama* buscar_lista_dama(int x, int y);



private:
    Dama* lista_damas[MAX_DAMAS];
    int num;
};
