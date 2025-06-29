#pragma once
#include "Evento.h"

class Deporte : public Evento {
private:
    string equipoLocal;
    string equipoVisitante;

public:
    Deporte(int _id, string nombre, string fecha, double precio, string local, string visitante)
        : Evento(_id, nombre, fecha, precio), equipoLocal(local), equipoVisitante(visitante) {
    }

    void mostrar() override {
        cout << "" << endl;
        cout << "\n   |   Partido Deportivo: " << equipoLocal << " vs " << equipoVisitante << endl;
        cout << "   |   Evento: " << nombre << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;

    }
};
