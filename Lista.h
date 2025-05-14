#pragma once
#ifndef __LISTA_H__
#define __LISTA_H__
#include <iostream>
#include <functional>
#include "Nodo.h"
using namespace std;
template<class T>
class Lista {

private:
    Nodo<T>* inicio;
    size_t longitud;

public:
    Lista() {
        inicio = nullptr;
        longitud = 0;
    }

    ~Lista();

    void insertarInicio(T v);
    void insertarFinal(T v);
    void insertarOrdenado(T v, function<bool(T, T)> comparador);
    void insertar(T v, size_t pos);
    T obtener(size_t pos) const;
    void eliminar(size_t pos);
    void eliminarValor(T v);
    size_t tamaño() const;
    bool estaVacia() const;
    void mostrar(function<void(T)> mostrarElemento = nullptr);
    void ordenar(function<bool(T, T)> comparador);
    T buscar(function<bool(T)> condicion);
    Lista<T> filtrar(function<bool(T)> condicion);
    void modificar(size_t pos, T nuevoValor);
    void forEach(function<void(T&)> accion);
};
template<class T>
Lista<T>::~Lista() {
    Nodo<T>* temp;
    while (inicio != nullptr) {
        temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
    longitud = 0;
}
template<class T>
void Lista<T>::insertarInicio(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v);

    if (inicio == nullptr) {
        inicio = nuevo;
    }
    else {
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }
    longitud++;
}
template<class T>
void Lista<T>::insertarFinal(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v);

    if (inicio == nullptr) {
        inicio = nuevo;
    }
    else {
        Nodo<T>* temp = inicio;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    longitud++;
}
template<class T>
void Lista<T>::insertarOrdenado(T valor, function<bool(T, T)> comparador) {
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (inicio == nullptr || comparador(valor, inicio->valor)) {
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }
    else {
        Nodo<T>* actual = inicio;
        while (actual->siguiente && !comparador(valor, actual->siguiente->valor)) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    longitud++;
}
template<class T>
void Lista<T>::insertar(T v, size_t pos) {
    if (pos > longitud) {
        cout << "Error: posicion fuera de rango" << endl;
        return;
    }

    if (pos == 0) {
        insertarInicio(v);
        return;
    }

    if (pos == longitud) {
        insertarFinal(v);
        return;
    }

    Nodo<T>* nuevo = new Nodo<T>(v);
    Nodo<T>* temp = inicio;

    for (size_t i = 0; i < pos - 1; i++) {
        temp = temp->siguiente;
    }

    nuevo->siguiente = temp->siguiente;
    temp->siguiente = nuevo;
    longitud++;
}
template<class T>
T Lista<T>::obtener(size_t pos) const {
    if (pos >= longitud) {
        cerr << "Error: posicion fuera de rango" << endl;
        return T();
    }

    Nodo<T>* temp = inicio;
    for (size_t i = 0; i < pos; i++) {
        temp = temp->siguiente;
    }
    return temp->valor;
}
template<class T>
void Lista<T>::eliminar(size_t pos) {
    if (estaVacia() || pos >= longitud) {
        cerr << "Error: lista vacia o posicion fuera de rango" << endl;
        return;
    }

    Nodo<T>* temp;

    if (pos == 0) {
        temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
    else {
        Nodo<T>* actual = inicio;
        for (size_t i = 0; i < pos - 1; i++) {
            actual = actual->siguiente;
        }

        temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
    }

    longitud--;
}
template<class T>
void Lista<T>::eliminarValor(T v) {
    if (estaVacia()) {
        return;
    }
    if (inicio->valor == v) {
        Nodo<T>* temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
        longitud--;
        return;
    }
    Nodo<T>* actual = inicio;
    while (actual->siguiente != nullptr && actual->siguiente->valor != v) {
        actual = actual->siguiente;
    }
    if (actual->siguiente != nullptr) {
        Nodo<T>* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        longitud--;
    }
}
template<class T>
size_t Lista<T>::tamaño() const {
    return longitud;
}
template<class T>
bool Lista<T>::estaVacia() const {
    return inicio == nullptr;
}
template<class T>
void Lista<T>::mostrar(function<void(T)> mostrarElemento) {
    Nodo<T>* temp = inicio;

    cout << " -> ";
    while (temp != nullptr) {
        if (mostrarElemento) {
            mostrarElemento(temp->valor);
        }
        else {
            cout << temp->valor;
        }

        if (temp->siguiente != nullptr) {
            cout << " -> ";
        }
        temp = temp->siguiente;
    }
    cout << endl;
}
template<class T>
void Lista<T>::ordenar(function<bool(T, T)> comparador) {
    if (estaVacia() || longitud == 1) {
        return;
    }
    bool intercambio;
    Nodo<T>* actual;
    Nodo<T>* siguiente = nullptr;

    do {
        intercambio = false;
        actual = inicio;
        while (actual->siguiente != siguiente) {
            if (comparador(actual->valor, actual->siguiente->valor)) {
                T temp = actual->valor;
                actual->valor = actual->siguiente->valor;
                actual->siguiente->valor = temp;
                intercambio = true;
            }
            actual = actual->siguiente;
        }
        siguiente = actual;
    } while (intercambio);
}
template<class T>
T Lista<T>::buscar(function<bool(T)> condicion) {
    Nodo<T>* temp = inicio;

    while (temp != nullptr) {
        if (condicion(temp->valor)) {
            return temp->valor;
        }
        temp = temp->siguiente;
    }
    return T();
}
template<class T>
Lista<T> Lista<T>::filtrar(function<bool(T)> condicion) {
    Lista<T> resultado;
    Nodo<T>* temp = inicio;

    while (temp != nullptr) {
        if (condicion(temp->valor)) {
            resultado.insertarFinal(temp->valor);
        }
        temp = temp->siguiente;
    }
    return resultado;
}
template<class T>
void Lista<T>::modificar(size_t pos, T nuevoValor) {
    if (pos >= longitud) {
        cerr << "Error: posicion fuera de rango" << endl;
        return;
    }

    Nodo<T>* temp = inicio;
    for (size_t i = 0; i < pos; i++) {
        temp = temp->siguiente;
    }

    temp->valor = nuevoValor;
}
template<class T>
void Lista<T>::forEach(function<void(T&)> accion) {
    Nodo<T>* temp = inicio;
    while (temp != nullptr) {
        accion(temp->valor);
        temp = temp->siguiente;
    }
}
#endif
