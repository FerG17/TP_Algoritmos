#pragma once
#include "Lista.h"
#include "Evento.h"
#include "Concierto.h"
#include <stack>
#include "Hash.h"


class GestorEventos {
private:
    Lista<Evento*> eventos;
    stack<Evento*> historial;
    HashTabla hashEventos;

public:
	GestorEventos() : hashEventos(100) {}
    Lista<Evento*>& getEventos();
    void agregarEvento(Evento* e);
    void mostrarEventos();
    Evento* buscarPorMes(const string& mes);
    void historialPush(Evento* e);
    void historialPop();
    bool historialVacio() const;
    Evento* buscarPorId(int id);
    ~GestorEventos();
};
Lista<Evento*>& GestorEventos::getEventos() {
    return eventos;
}
void GestorEventos::agregarEvento(Evento* e) {
    eventos.insertarOrdenado(e, [](Evento* a, Evento* b) {
        return a->getFecha() < b->getFecha();
        });
    int idx = eventos.tamaño() - 1;
    hashEventos.insertar(e->getId(), idx);
}

void GestorEventos::mostrarEventos() {
    int y = 5;
    eventos.forEach([&y](Evento* e) {
        gotoxy(10, y += 5);
        e->mostrar();
        });
}

Evento* GestorEventos::buscarPorMes(const string& mes) {
    return eventos.buscar([mes](Evento* e) {
        return e->getFecha().substr(5, 2) == mes;
        });
}

Evento* GestorEventos::buscarPorId(int id) {
    int idx = hashEventos.buscar(id);
    if (idx == -1) return nullptr;
    return eventos.obtener(idx);
}

void GestorEventos::historialPush(Evento* e) {
    historial.push(e);
}

void GestorEventos::historialPop() {
    if (!historial.empty()) {
        Evento* e = historial.top();
        historial.pop();
        cout << "Evento retirado del historial: ";
        e->mostrar();
    }
    else {
        cout << "Historial vacio." << endl;
    }
}

bool GestorEventos::historialVacio() const {
    return historial.empty();
}
GestorEventos::~GestorEventos() {
    eventos.forEach([](Evento*& e) {
        delete e;
        e = nullptr;
        });
}
