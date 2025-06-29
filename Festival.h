#pragma once
#include "Evento.h"

class Festival : public Evento {
private:
    int diasDuracion;
    string categoria;

public:
    Festival(int _id, string nombre, string fecha, double precio, int dias, string cat)
        : Evento(_id, nombre, fecha, precio), diasDuracion(dias), categoria(cat) {
    }

    void mostrar() override {
        cout << "" << endl;
        cout << "\n   |   Festival: " << nombre << endl;
        cout << "   |   Categoria: " << categoria << endl;
        cout << "   |   Duracion: " << diasDuracion << " dias" << endl;
        cout << "   |   Fecha: " << fecha << endl;
        cout << "   |   Precio: S/." << precio << "\n" << endl;
    }
};
