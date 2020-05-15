#include "ListaDamas.h"



ListaDamas::ListaDamas()
{
    num = 0;
    for (int i = 0; i < MAX_DAMAS; i++)
    {
        lista_damas[i] = 0;
    }
}



ListaDamas::~ListaDamas()
{
    for (int i = 0; i < num; i++)
    {
        delete lista_damas[i];
    }
    num = 0;
}



bool ListaDamas::agregar(Dama* d)
{
    if (num < MAX_DAMAS)
        lista_damas[num++] = d;
    else
        return false;



    return true;
}



void ListaDamas::dibuja()
{
    for (int i = 0; i < num; i++)
    {
        lista_damas[i]->Dibuja();
    }
}



void ListaDamas::eliminar(int index)
{
    if ((index < 0) || index >= num)
        return;
    delete lista_damas[index];
    num--;
    for (int i = index; i < num; i++)
    {
        lista_damas[i] = lista_damas[i + 1];
    }
}



void ListaDamas::eliminar(Dama* d)
{
    for (int i = 0; i < num; i++)
    {
        if (lista_damas[i] == d)
        {
            eliminar(i);
            return;
        }
    }
}



Dama* ListaDamas::operator[](int i)
{
    if (i >= num)
    {
        i = num - 1;
    }
    if (i < 0)
    {
        i = 0;
    }
    return lista_damas[i];
}

Dama* ListaDamas::buscar_lista_dama(int x, int y)
{
    for (int i = 0; i < num;i++)
    {
        if ((lista_damas[i]->GetPosX() == x) && (lista_damas[i]->GetPosY() == y))
            return lista_damas[i];
    }
    return NULL;
}
