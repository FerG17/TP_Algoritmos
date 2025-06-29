#pragma once
#include "Evento.h"

class ObraTeatral : public Evento {
private:
    string director;
    int duracionMin;

public:
    ObraTeatral(int _id, string nombre, string fecha, double precio, string director, int duracion)
        : Evento(_id, nombre, fecha, precio), director(director), duracionMin(duracion) {
    }

    void mostrar() override {
        cout << "" << endl;
        cout << "\n   |   Obra Teatral: " << nombre << endl;
        cout << "   |   Director: " << director << endl;
        cout << "   |   Duracion: " << duracionMin << " min" << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
        cout << "" << endl;
    }
};
