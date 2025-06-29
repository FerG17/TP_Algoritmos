#pragma once
#include <string>
#include <iostream>
#include "SeccionLugar.h" 
using namespace std;

class Evento {
protected:
    int id;
    string nombre, fecha;
    double precio;
    SeccionLugar* seccion;
    SeccionLugar* seccionGeneral;
    SeccionLugar* seccionVIP;
public:
    Evento(int _id, string n, string f, double p)
        : id(_id), nombre(n), fecha(f), precio(p),
        seccion(new SeccionLugar("Principal")),
        seccionGeneral(new SeccionLugar("General")),
        seccionVIP(new SeccionLugar("VIP Gold")) {
    }

    virtual void mostrar() {
        cout << "Evento: " << nombre << "Id:  " << id << ", Fecha: " << fecha << ", Precio : " << precio << endl;
    }
    virtual void mostrarSeccion() {
        seccionGeneral = new SeccionLugar("General");
        seccionVIP = new SeccionLugar("VIP Gold");
    }
    string getFecha() const { return fecha; }
    double getPrecio() const { return precio; }
    SeccionLugar* getSeccion() {
        return seccion;
    }
    SeccionLugar* getSeccionGeneral() const { return seccionGeneral; }
    SeccionLugar* getSeccionVIP() const { return seccionVIP; }
    string getNombre() const { return nombre; }
    virtual ~Evento() {
        delete seccion;
        delete seccionGeneral;
        delete seccionVIP;
    }
    int getId() const { return id; }
};
