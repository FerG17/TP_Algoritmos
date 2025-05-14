#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <fstream>
#include "Lista.h"
using namespace std;

class Persona {
protected:
    int id;
    string nombre;
    string apellido;
    string email;
    string telefono;

public:
    Persona() : id(0), nombre(""), apellido(""), email(""), telefono("") {}

    Persona(int _id, string _nombre, string _apellido, string _email, string _telefono)
        : id(_id), nombre(_nombre), apellido(_apellido), email(_email), telefono(_telefono) {
    }

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getEmail() const { return email; }
    string getTelefono() const { return telefono; }
    string getNombreCompleto() const { return nombre + " " + apellido; }

    void setId(int _id) { id = _id; }
    void setNombre(string _nombre) { nombre = _nombre; }
    void setApellido(string _apellido) { apellido = _apellido; }
    void setEmail(string _email) { email = _email; }
    void setTelefono(string _telefono) { telefono = _telefono; }

    virtual void actualizarDatos(string _nombre, string _apellido, string _email, string _telefono) {
        nombre = _nombre;
        apellido = _apellido;
        email = _email;
        telefono = _telefono;
    }
    //RECURSIVIDAD
    bool validarEmail(const string& email, size_t pos = 0) {
        if (pos >= email.length()) {
            return email.find('@') != string::npos && email.find('.', email.find('@')) != string::npos;
        }

        char c = email[pos];
        bool caracterValido = (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '.' || c == '@' || c == '_' || c == '-';

        if (!caracterValido) return false;

        return validarEmail(email, pos + 1);
    }

    virtual void guardarEnArchivo(ofstream& archivo) const {
        archivo << id << "," << nombre << "," << apellido << "," << email << "," << telefono << ",";
    }

    virtual bool cargarDesdeArchivo(ifstream& archivo) {
        string linea;
        if (getline(archivo, linea)) {
            size_t pos = 0;
            string token;

            pos = linea.find(',');
            if (pos == string::npos) return false;
            id = stoi(linea.substr(0, pos));
            linea.erase(0, pos + 1);

            pos = linea.find(',');
            if (pos == string::npos) return false;
            nombre = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find(',');
            if (pos == string::npos) return false;
            apellido = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find(',');
            if (pos == string::npos) return false;
            email = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find(',');
            if (pos == string::npos) return false;
            telefono = linea.substr(0, pos);

            return true;
        }
        return false;
    }

    virtual void mostrarInformacion() const {
        cout << "ID: " << id << endl;
        cout << "Nombre completo: " << getNombreCompleto() << endl;
        cout << "Email: " << email << endl;
        cout << "Telefono: " << telefono << endl;
    }

    bool operator==(const Persona& otra) const {
        return id == otra.id;
    }

    friend ostream& operator<<(ostream& os, const Persona& persona) {
        os << persona.id << " - " << persona.getNombreCompleto();
        return os;
    }
};
