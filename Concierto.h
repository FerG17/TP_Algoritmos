#pragma once
#pragma once
#include "Evento.h"

class Concierto : public Evento {
    string artista;
public:
    Concierto(int _id, string n, string f, double p, string art) : Evento(_id, n, f, p), artista(art) {}
    void mostrar() override {
        cout << "" << endl;
        cout << "\n   |   CONCIERTO: " << nombre << endl;
        cout << "   |   Artista: " << artista << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
    }
};
