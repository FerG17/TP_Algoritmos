#pragma once
#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <chrono>
#include <ctime>
#include "Persona.h"
#include "Lista.h"

class Compra;

class Cliente : public Persona {
private:
    string direccion;
    string fechaRegistro;
    int puntosLealtad;
    mutable Lista<int> historialCompras;

public:
    Cliente() : Persona(), direccion(""), fechaRegistro(""), puntosLealtad(0) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaRegistro = fecha;
    }

    Cliente(int _id, string _nombre, string _apellido, string _email,
        string _telefono, string _direccion)
        : Persona(_id, _nombre, _apellido, _email, _telefono),
        direccion(_direccion), puntosLealtad(0) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaRegistro = fecha;
    }

    string getDireccion() const { return direccion; }
    string getFechaRegistro() const { return fechaRegistro; }
    int getPuntosLealtad() const { return puntosLealtad; }
    void setDireccion(string _direccion) { direccion = _direccion; }
    void setFechaRegistro(string _fecha) { fechaRegistro = _fecha; }
    void setPuntosLealtad(int _puntos) { puntosLealtad = _puntos; }
    void aumentarPuntos(int puntos) {
        puntosLealtad += puntos;
    }
    bool canjearPuntos(int puntos) {
        if (puntosLealtad >= puntos) {
            puntosLealtad -= puntos;
            return true;
        }
        return false;
    }
    void agregarCompraAlHistorial(int compraId) {
        historialCompras.insertarFinal(compraId);
    }
    Lista<int>& obtenerHistorialCompras() {
        return historialCompras;
    }

    const Lista<int>& obtenerHistorialCompras() const {
        return historialCompras;
    }

    double calcularTotalCompras(Lista<Compra>& compras, size_t index = 0) const;
    void guardarEnArchivo(ofstream& archivo) const {
        archivo << id << "," << nombre << "," << apellido << "," << email << "," << telefono << ",";
        archivo << direccion << "," << fechaRegistro << "," << puntosLealtad << ",";
        archivo << historialCompras.tamaño();
        for (size_t i = 0; i < historialCompras.tamaño(); i++) {
            int valor = historialCompras.obtener(i);
            archivo << "," << valor;
        }
        archivo << endl;
    }
    static Cliente cargarDesdeArchivo(string linea) {
        Cliente cliente;
        size_t pos = 0;
        string token;
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            cliente.id = stoi(token);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.nombre = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.apellido = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.email = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.telefono = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.direccion = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            cliente.fechaRegistro = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            cliente.puntosLealtad = stoi(token);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        int cantidadCompras = 0;
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            cantidadCompras = stoi(token);
            linea.erase(0, pos + 1);
        }
        for (int i = 0; i < cantidadCompras; i++) {
            pos = linea.find(",");
            if (pos != string::npos) {
                token = linea.substr(0, pos);
                cliente.historialCompras.insertarFinal(stoi(token));
                linea.erase(0, pos + 1);
            }
            else if (!linea.empty()) {
                cliente.historialCompras.insertarFinal(stoi(linea));
                break;
            }
        }
        return cliente;
    }
    //RECURSIVIDAD
    void mostrarDetalles(int nivel = 0) const {
        if (nivel == 0) {
            cout << "Detalles de Cliente:" << endl;
            cout << "ID: " << id << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 1) {
            cout << "Nombre completo: " << getNombreCompleto() << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 2) {
            cout << "Email: " << email << " | Telefono: " << telefono << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 3) {
            cout << "Direccion: " << direccion << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 4) {
            cout << "Fecha de registro: " << fechaRegistro << endl;
            mostrarDetalles(nivel + 1);
        }
        else if (nivel == 5) {
            cout << "Puntos de lealtad: " << puntosLealtad << endl;
            mostrarDetalles(nivel + 1);
        }
    }
    void sumarPuntos(int puntos) {
        puntosLealtad += puntos;
    }
    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << "Cliente [" << cliente.id << "]: " << cliente.getNombreCompleto()
            << " | Puntos: " << cliente.puntosLealtad;
        return os;
    }
};

#endif
