#pragma once
#include "Persona.h"
#include <functional>

class Administrador : public Persona {
private:
    string claveAcceso;

public:
    Administrador() : Persona(), claveAcceso("admin123") {}
    Administrador(int id, string nombre, string apellido, string email, string telefono, string clave)
        : Persona(id, nombre, apellido, email, telefono), claveAcceso(clave) {
    }

    void setClave(string clave) { claveAcceso = clave; }
    string getClave() const { return claveAcceso; }

    bool validarAcceso(const string& claveIngresada) const {
        return claveIngresada == claveAcceso;
    }

    void mostrarInformacion() const override {
        Persona::mostrarInformacion();
        cout << "Nivel de acceso: Administrador" << endl;
    }

    void guardarEnArchivo(ofstream& archivo) const override {
        Persona::guardarEnArchivo(archivo);
        archivo << claveAcceso << ",";
    }

    bool cargarDesdeArchivo(ifstream& archivo) override {
        if (!Persona::cargarDesdeArchivo(archivo)) return false;
        getline(archivo, claveAcceso, ',');
        return true;
    }
    bool intentarAcceso(const string& claveIngresada,
        function<void(bool)> accionPostAcceso) {
        bool resultado = validarAcceso(claveIngresada);
        accionPostAcceso(resultado);
        return resultado;
    }
    bool cambiarClaveCondicional(const string& claveActual,
        const string& nuevaClave,
        function<bool(const string&)> validador) {
        if (validarAcceso(claveActual) && validador(nuevaClave)) {
            claveAcceso = nuevaClave;
            return true;
        }
        return false;
    }
    static void filtrarAdministradores(Administrador admins[], int cantidad,
        function<bool(const Administrador&)> criterio,
        function<void(const Administrador&)> accion) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(admins[i])) {
                accion(admins[i]);
            }
        }
    }
};
