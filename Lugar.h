#pragma once
#include "SeccionLugar.h"

class Lugar {
    string nombre;
    SeccionLugar* seccion;
public:
    Lugar(string nom) : nombre(nom), seccion(new SeccionLugar("General")) {}
    void mostrarLugar() {
        cout << "Lugar: " << nombre << endl;
        seccion->mostrarAsientos();
    }
};
