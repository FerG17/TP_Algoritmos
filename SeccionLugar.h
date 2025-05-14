#pragma once
#include "Asiento.h"
#include <iostream>
using namespace std;

class SeccionLugar {
    string nombre;
    Asiento* asientos[10];
public:
    SeccionLugar(string nom) : nombre(nom) {
        for (int i = 0; i < 10; ++i)
            asientos[i] = new Asiento(i + 1);
    }
    void mostrarAsientos() {
        cout << "\n========================================= Seccion: " << nombre << " =========================================" << endl;
        for (int i = 0; i < 10; ++i) {
            cout << "Asiento [" << asientos[i]->getNumero() << "]"
                << (asientos[i]->estaDisponible() ? " Disponible" : " Ocupado") << endl;
        }
    }
    void mostrarAsientosInverso() {
        cout << "\n========================================= Seccion: " << nombre << " (desde el fondo hacia adelante) =========================================" << endl;
        mostrarAsientosInversoRec(9);
    }
    void mostrarAsientosInversoRec(int idx) {
        if (idx < 0) return;
        cout << "\rAsiento [" << asientos[idx]->getNumero() << "]"
            << (asientos[idx]->estaDisponible() ? " Disponible" : " Ocupado") << endl;
        mostrarAsientosInversoRec(idx - 1);
    }
};
