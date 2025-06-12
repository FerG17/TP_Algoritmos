#pragma once
#ifndef __COLA_H__
#define __COLA_H__

#include <iostream>
#include <functional>
#include "Nodo.h"
template<class T>
class Cola {
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;
    size_t tamanio;

public:
    Cola() {
        inicio = nullptr;
        fin = nullptr;
        tamanio = 0;
    }

    ~Cola();
    void enqueue(T v);
    T dequeue();
    T frente() const;
    bool esVacia() const;
    size_t longitud() const;
    void vaciar();
    T buscar(function<bool(T)> condicion);
    Cola<T> filtrar(function<bool(T)> condicion);
    void forEach(function<void(T&)> accion);
    void mostrar(function<void(T)> mostrarElemento = nullptr);
};


template<class T>
Cola<T>::~Cola() {
    vaciar();
}

template<class T>
void Cola<T>::enqueue(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v);

    if (esVacia()) {
        inicio = nuevo;
        fin = nuevo;
    }
    else {
        fin->siguiente = nuevo;
        fin = nuevo;
    }

    tamanio++;
}
template<class T>
T Cola<T>::dequeue() {
    if (esVacia()) {
        cerr << "Error: cola vacia" << endl;
        return T();
    }

    T elemento = inicio->valor;
    Nodo<T>* temp = inicio;

    if (inicio == fin) {
        inicio = nullptr;
        fin = nullptr;
    }
    else {
        inicio = inicio->siguiente;
    }

    delete temp;
    tamanio--;

    return elemento;
}

template<class T>
T Cola<T>::frente() const {
    if (esVacia()) {
        cerr << "Error: cola vacia" << endl;
        return T();
    }

    return inicio->valor;
}
template<class T>
bool Cola<T>::esVacia() const {
    return inicio == nullptr;
}

template<class T>
size_t Cola<T>::longitud() const {
    return tamanio;
}
template<class T>
void Cola<T>::vaciar() {
    Nodo<T>* temp;
    while (inicio != nullptr) {
        temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
    fin = nullptr;
    tamanio = 0;
}

template<class T>
T Cola<T>::buscar(function<bool(T)> condicion) {
    Cola<T> temp;
    T encontrado = T();
    bool hallado = false;
    while (!esVacia()) {
        T elemento = dequeue();
        if (condicion(elemento) && !hallado) {
            encontrado = elemento;
            hallado = true;
        }
        temp.enqueue(elemento);
    }
    while (!temp.esVacia()) {
        enqueue(temp.dequeue());
    }

    return encontrado;
}

template<class T>
Cola<T> Cola<T>::filtrar(function<bool(T)> condicion) {
    Cola<T> resultado;
    Cola<T> temp;

    while (!esVacia()) {
        T elemento = dequeue();
        temp.enqueue(elemento);

        if (condicion(elemento)) {
            resultado.enqueue(elemento);
        }
    }
    while (!temp.esVacia()) {
        enqueue(temp.dequeue());
    }

    return resultado;
}
template<class T>
void Cola<T>::forEach(function<void(T&)> accion) {
    Cola<T> temp;
    while (!esVacia()) {
        T elemento = dequeue();
        accion(elemento);
        temp.enqueue(elemento);
    }
    while (!temp.esVacia()) {
        enqueue(temp.dequeue());
    }
}
template<class T>
void Cola<T>::mostrar(function<void(T)> mostrarElemento) {
    if (esVacia()) {
        cout << "Cola vacia" << endl;
        return;
    }

    Cola<T> temp;
    cout << "Cola (inicio -> fin): ";

    while (!esVacia()) {
        T elemento = dequeue();
        temp.enqueue(elemento);

        if (mostrarElemento) {
            mostrarElemento(elemento);
        }
        else {
            cout << elemento;
        }

        if (!esVacia()) {
            cout << " -> ";
        }
    }
    cout << endl;
    while (!temp.esVacia()) {
        enqueue(temp.dequeue());
    }
}
#endif
