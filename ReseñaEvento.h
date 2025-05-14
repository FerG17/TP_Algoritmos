#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;

class ReseñaEvento {
private:
    int id;
    string comentario;
    int calificacion;
    string nombreCliente;

public:
    ReseñaEvento() : id(0), comentario(""), calificacion(0), nombreCliente("") {}
    ReseñaEvento(int id, string com, int cal, string nom)
        : id(id), comentario(com), calificacion(cal), nombreCliente(nom) {
    }

    int getId() const { return id; }
    string getComentario() const { return comentario; }
    int getCalificacion() const { return calificacion; }
    string getNombreCliente() const { return nombreCliente; }

    void setComentario(string c) { comentario = c; }
    void setCalificacion(int cal) { calificacion = cal; }
    void setNombreCliente(string n) { nombreCliente = n; }

    void mostrar() const {
        cout << "Rese"<<char(164)<<"a #" << id << " - Cliente: " << nombreCliente
            << "\nCalificacion: " << calificacion << "/5"
            << "\nComentario: " << comentario << "\n" << endl;
    }

    bool operator<(const ReseñaEvento& otra) const {
        return calificacion < otra.calificacion;
    }

    bool operator>(const ReseñaEvento& otra) const {
        return calificacion > otra.calificacion;
    }
    static float calcularEstadistica(ReseñaEvento reseñas[], int cantidad,
        function<float(const ReseñaEvento&)> extractor,
        function<float(float, float)> acumulador) {
        float resultado = 0.0f;
        for (int i = 0; i < cantidad; i++) {
            resultado = acumulador(resultado, extractor(reseñas[i]));
        }
        return resultado;
    }
    static void filtrarReseñas(ReseñaEvento reseñas[], int cantidad,
        function<bool(const ReseñaEvento&)> criterio) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(reseñas[i])) {
                reseñas[i].mostrar();
            }
        }
    }
    static void buscarYModificar(ReseñaEvento reseñas[], int cantidad,
        function<bool(const ReseñaEvento&)> criterio,
        function<void(ReseñaEvento&)> modificador) {
        for (int i = 0; i < cantidad; i++) {
            if (criterio(reseñas[i])) {
                modificador(reseñas[i]);
            }
        }
    }
};
