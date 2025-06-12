#pragma once
#ifndef __COMPRA_H__
#define __COMPRA_H__

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include "Entrada.h"
#include "Lista.h"
#include "Pila.h"
#include "Cola.h"
using namespace std;

enum class EstadoCompra {
    PENDIENTE,
    CONFIRMADA,
    CANCELADA,
    COMPLETADA
};

class Compra {
private:
    static int contadorIds;
    int id;
    int clienteId;
    string fechaCompra;
    double subtotal;
    double descuentoAplicado;
    double total;
    string metodoPago;
    EstadoCompra estado;
    Lista<Entrada> entradas;
    Pila<string> historialAcciones;
    Cola<Entrada> colaValidacion;

    void registrarAccion(const string& accion) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char timestamp[30];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now_time));

        stringstream ss;
        ss << "[" << timestamp << "] " << accion;
        historialAcciones.push(ss.str());
    }

public:
    Compra() : id(++contadorIds), clienteId(0), subtotal(0.0), descuentoAplicado(0.0), total(0.0), estado(EstadoCompra::PENDIENTE), metodoPago("") {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaCompra = fecha;

        registrarAccion("Compra inicializada vacia");
    }

    Compra(int _clienteId, string _metodoPago)
        : id(++contadorIds), clienteId(_clienteId), subtotal(0.0), descuentoAplicado(0.0), total(0.0), metodoPago(_metodoPago), estado(EstadoCompra::PENDIENTE) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        char fecha[20];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&now_time));
        fechaCompra = fecha;

        stringstream ss;
        ss << "Compra creada para cliente ID: " << clienteId;
        registrarAccion(ss.str());
    }

    int getId() const { return id; }
    int getClienteId() const { return clienteId; }
    string getFechaCompra() const { return fechaCompra; }
    double getSubtotal() const { return subtotal; }
    double getDescuentoAplicado() const { return descuentoAplicado; }
    double getTotal() const { return total; }
    EstadoCompra getEstado() const { return estado; }
    string getMetodoPago() const { return metodoPago; }
    Lista<Entrada>& getEntradas() { return entradas; }
    int getCantidadEntradas() const { return entradas.tamaño(); }
    double calcularSubtotal() const { return subtotal; }
    double calcularTotal() const { return total; }


    void agregarEntrada(const Entrada& entrada) {
        entradas.insertarFinal(entrada);
        subtotal += entrada.getPrecio();
        total = subtotal - descuentoAplicado;

        stringstream ss;
        ss << "Entrada agregada: " << entrada.getCodigo() << " - S/." << fixed << setprecision(2) << entrada.getPrecio();
        registrarAccion(ss.str());
    }

    bool quitarEntrada(size_t indice) {
        if (indice >= entradas.tamaño()) return false;

        Entrada entrada = entradas.obtener(indice);
        subtotal -= entrada.getPrecio();
        total = subtotal - descuentoAplicado;
        entradas.eliminar(indice);

        stringstream ss;
        ss << "Entrada removida: " << entrada.getCodigo() << " - S/." << fixed << setprecision(2) << entrada.getPrecio();
        registrarAccion(ss.str());
        return true;
    }

    void aplicarDescuento(double porcentaje) {
        if (porcentaje < 0 || porcentaje > 100) {
            cerr << "Error: porcentaje de descuento invalido\n";
            return;
        }

        descuentoAplicado = subtotal * (porcentaje / 100.0);
        total = subtotal - descuentoAplicado;

        stringstream ss;
        ss << "Descuento aplicado: " << porcentaje << "% - S/." << fixed << setprecision(2) << descuentoAplicado;
        registrarAccion(ss.str());
    }

    void finalizarCompra() {
        estado = EstadoCompra::COMPLETADA;
        registrarAccion("Compra finalizada y marcada como COMPLETADA");

        for (size_t i = 0; i < entradas.tamaño(); i++) {
            Entrada e = entradas.obtener(i);
            e.marcarUtilizada();
            entradas.modificar(i, e);
            colaValidacion.enqueue(e);
        }
    }
    void validarEntradas() {
        cout << "\n=== VALIDANDO ENTRADAS ===\n";
        while (!colaValidacion.esVacia()) {
            Entrada e = colaValidacion.dequeue();
            if (e.validar()) {
                cout << "Entrada " << e.getCodigo() << " validada correctamente.\n";
            }
            else {
                cout << "Entrada " << e.getCodigo() << " invalida o ya utilizada.\n";
            }
        }
        cout << "Todas las entradas han sido procesadas.\n";
    }

    void mostrarResumen() const {
        cout << "\n========= COMPRA #" << id << " =========\n";
        cout << "Cliente ID: " << clienteId << "\n";
        cout << "Fecha: " << fechaCompra << "\n";
        cout << "Estado: ";
        switch (estado) {
        case EstadoCompra::PENDIENTE: cout << "PENDIENTE"; break;
        case EstadoCompra::CONFIRMADA: cout << "CONFIRMADA"; break;
        case EstadoCompra::CANCELADA: cout << "CANCELADA"; break;
        case EstadoCompra::COMPLETADA: cout << "COMPLETADA"; break;
        }
        cout << "\nMetodo de pago: " << metodoPago;
        cout << "\nSubtotal: S/." << fixed << setprecision(2) << subtotal;
        cout << "\nDescuento aplicado: S/." << fixed << setprecision(2) << descuentoAplicado;
        cout << "\nTotal a pagar: S/." << fixed << setprecision(2) << total;
        cout << "\nCantidad de entradas: " << entradas.tamaño() << "\n";

        for (size_t i = 0; i < entradas.tamaño(); i++) {
            cout << i + 1 << ". " << entradas.obtener(i) << "\n";
        }

        cout << "=====================================\n";
    }

    bool operator==(const Compra& otra) const {
        return id == otra.id;
    }

    friend ostream& operator<<(ostream& os, const Compra& compra) {
        os << "Compra #" << compra.id << " | Cliente: " << compra.clienteId
            << " | Fecha: " << compra.fechaCompra
            << " | Total: S/." << fixed << setprecision(2) << compra.total;
        return os;
    }
};
int Compra::contadorIds = 0;
#endif
