#pragma once
#ifndef __ENTRADA_H__
#define __ENTRADA_H__

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <random>
#include <iomanip>
#include <sstream>

class Entrada {
private:
    string codigo;
    int eventoId;
    int asientoId;
    double precio;
    bool utilizada;
    string fechaEmision;
    string generarCodigo() {
        const string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, caracteres.size() - 1);

        string codigo = "";
        for (int i = 0; i < 8; ++i) {
            codigo += caracteres[dis(gen)];
        }
        return codigo;
    }

public:
    Entrada() : eventoId(0), asientoId(0), precio(0.0), utilizada(false) {
        codigo = generarCodigo();
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaEmision = fecha;
    }

    Entrada(int _eventoId, int _asientoId, double _precio)
        : eventoId(_eventoId), asientoId(_asientoId), precio(_precio), utilizada(false) {
        codigo = generarCodigo();
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaEmision = fecha;
    }
    string getCodigo() const { return codigo; }
    int getEventoId() const { return eventoId; }
    int getAsientoId() const { return asientoId; }
    double getPrecio() const { return precio; }
    bool getUtilizada() const { return utilizada; }
    string getFechaEmision() const { return fechaEmision; }
    void setCodigo(string _codigo) { codigo = _codigo; }
    void setEventoId(int _eventoId) { eventoId = _eventoId; }
    void setAsientoId(int _asientoId) { asientoId = _asientoId; }
    void setPrecio(double _precio) { precio = _precio; }
    void setUtilizada(bool _utilizada) { utilizada = _utilizada; }
    void setFechaEmision(string _fechaEmision) { fechaEmision = _fechaEmision; }
    bool validar() const {
        return !utilizada && eventoId > 0 && asientoId > 0;
    }
    void marcarUtilizada() {
        utilizada = true;
    }
    //RECURSIVIDAD
    void imprimirEntrada(int nivel = 0) const {
        if (nivel == 0) {
            cout << "\n========= ENTRADA " << codigo << " =========" << endl;
            imprimirEntrada(nivel + 1);
        }
        else if (nivel == 1) {
            cout << "Evento ID: " << eventoId << endl;
            imprimirEntrada(nivel + 1);
        }
        else if (nivel == 2) {
            cout << "Asiento ID: " << asientoId << endl;
            imprimirEntrada(nivel + 1);
        }
        else if (nivel == 3) {
            cout << "Precio: $" << fixed << setprecision(2) << precio << endl;
            imprimirEntrada(nivel + 1);
        }
        else if (nivel == 4) {
            cout << "Fecha de emision: " << fechaEmision << endl;
            imprimirEntrada(nivel + 1);
        }
        else if (nivel == 5) {
            cout << "Estado: " << (utilizada ? "UTILIZADA" : "NO UTILIZADA") << endl;
            cout << "=====================================" << endl;
        }
    }

    void guardarEnArchivo(ofstream& archivo) const {
        archivo << codigo << "," << eventoId << "," << asientoId << ","
            << precio << "," << (utilizada ? "1" : "0") << "," << fechaEmision << endl;
    }

    static Entrada cargarDesdeArchivo(string linea) {
        Entrada entrada;
        size_t pos = 0;
        string token;
        pos = linea.find(",");
        if (pos != string::npos) {
            entrada.codigo = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            entrada.eventoId = stoi(token);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            entrada.asientoId = stoi(token);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            entrada.precio = stod(token);
            linea.erase(0, pos + 1);
        }
        pos = linea.find(",");
        if (pos != string::npos) {
            token = linea.substr(0, pos);
            entrada.utilizada = (token == "1");
            linea.erase(0, pos + 1);
        }
        entrada.fechaEmision = linea;
        return entrada;
    }
    bool operator==(const Entrada& otra) const {
        return codigo == otra.codigo;
    }
    friend ostream& operator<<(ostream& os, const Entrada& entrada) {
        os << "Entrada [" << entrada.codigo << "] - Evento: " << entrada.eventoId
            << " | Asiento: " << entrada.asientoId
            << " | Precio: $" << fixed << setprecision(2) << entrada.precio
            << (entrada.utilizada ? " (UTILIZADA)" : "");
        return os;
    }
};

#endif
