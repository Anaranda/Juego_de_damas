#pragma once
#include "glut.h"

enum PULSACION { SIN_PULSAR, PRIMERO, SEGUNDO };

class Mouse
{

public:
    int indices[2];
    int i0, j0;

    PULSACION pulsacion;
    int button;// boton derecho o izqdo
    int state;// pulsado o no
    Mouse();
    ~Mouse();
    
    //MouseX y MouseY son las coordenadas en píxeles
    //convertidas a enteros
    void SetIndices(int button, int state, int mouseX, int mouseY);
};

