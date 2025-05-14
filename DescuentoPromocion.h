#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;

class DescuentoPromocion {
private:
    int codigo;
    string descripcion;
    float porcentaje;
    bool vigente;

public:
    DescuentoPromocion() : codigo(0), descripcion(""), porcentaje(0.0f), vigente(false) {}
    DescuentoPromocion(int c, string d, float p, bool v) : codigo(c), descripcion(d), porcentaje(p), vigente(v) {}

    int getCodigo() const { return codigo; }
    string getDescripcion() const { return descripcion; }
    float getPorcentaje() const { return porcentaje; }
    bool estaVigente() const { return vigente; }

    void setCodigo(int c) { codigo = c; }
    void setDescripcion(string d) { descripcion = d; }
    void setPorcentaje(float p) { porcentaje = p; }
    void setVigente(bool v) { vigente = v; }

    void mostrar() const {
        cout << "Codigo: " << codigo << " | " << descripcion
            << " | " << porcentaje << "% de descuento"
            << (vigente ? " (Activo)" : " (Inactivo)") << endl;
    }

    bool operator<(const DescuentoPromocion& otra) const {
        return porcentaje < otra.porcentaje;
    }

    bool operator>(const DescuentoPromocion& otra) const {
        return porcentaje > otra.porcentaje;
    }
    static void filtrarMostrar(DescuentoPromocion descuentos[], int cantidad, function<bool(const DescuentoPromocion&)> criterio) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(descuentos[i])) {
                descuentos[i].mostrar();
            }
        }
    }
    static DescuentoPromocion* encontrar(DescuentoPromocion descuentos[], int cantidad, function<bool(const DescuentoPromocion&)> criterio) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(descuentos[i])) {
                return &descuentos[i];
            }
        }
        return nullptr;
    }
    static void aplicarCambio(DescuentoPromocion descuentos[], int cantidad,
        function<bool(const DescuentoPromocion&)> criterio,
        function<void(DescuentoPromocion&)> transformacion) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(descuentos[i])) {
                transformacion(descuentos[i]);
            }
        }
    }
};
