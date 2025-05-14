#pragma once
#ifndef __PILA_H__
#define __PILA_H__

#include <iostream>
#include <functional>
#include "Nodo.h"
using namespace std;

template<class T>
class Pila {
private:
    Nodo<T>* tope;
    size_t tamanio;

public:
    Pila() {
        tope = nullptr;
        tamanio = 0;
    }

    ~Pila();


    void push(T v);
    T pop();
    T peek() const;
    bool estaVacia() const;
    size_t longitud() const;

    void vaciar();
    T buscar(function<bool(T)> condicion);
    Pila<T> filtrar(function<bool(T)> condicion);
    void forEach(function<void(T&)> accion);
    void mostrar(function<void(T)> mostrarElemento = nullptr);
};

template<class T>
Pila<T>::~Pila() {
    vaciar();
}

template<class T>
void Pila<T>::push(T v) {
    if (estaVacia()) {
        tope = new Nodo<T>(v);
    }
    else {
        tope = new Nodo<T>(v, tope);
    }
    tamanio++;
}

template<class T>
T Pila<T>::pop() {
    if (estaVacia()) {
        cerr << "Error: pila vacia" << endl;
        return T();
    }

    T elemento = tope->valor;
    Nodo<T>* temp = tope;
    tope = tope->siguiente;
    delete temp;
    tamanio--;

    return elemento;
}

template<class T>
T Pila<T>::peek() const {
    if (estaVacia()) {
        cerr << "Error: pila vacia" << endl;
        return T();
    }

    return tope->valor;
}

template<class T>
bool Pila<T>::estaVacia() const {
    return tope == nullptr;
}

template<class T>
size_t Pila<T>::longitud() const {
    return tamanio;
}

template<class T>
void Pila<T>::vaciar() {
    Nodo<T>* temp;
    while (tope != nullptr) {
        temp = tope;
        tope = tope->siguiente;
        delete temp;
    }
    tamanio = 0;
}

template<class T>
T Pila<T>::buscar(function<bool(T)> condicion) {
    Pila<T> temp;
    T encontrado = T();
    bool hallado = false;

    while (!estaVacia() && !hallado) {
        T elemento = pop();
        if (condicion(elemento) && !hallado) {
            encontrado = elemento;
            hallado = true;
        }
        temp.push(elemento);
    }

    while (!temp.estaVacia()) {
        push(temp.pop());
    }

    return encontrado;
}

template<class T>
Pila<T> Pila<T>::filtrar(function<bool(T)> condicion) {
    Pila<T> resultado;
    Pila<T> temp;

    while (!estaVacia()) {
        T elemento = pop();
        temp.push(elemento);

        if (condicion(elemento)) {
            resultado.push(elemento);
        }
    }

    while (!temp.estaVacia()) {
        push(temp.pop());
    }

    temp = Pila<T>();
    while (!resultado.estaVacia()) {
        temp.push(resultado.pop());
    }

    return temp;
}

template<class T>
void Pila<T>::forEach(function<void(T&)> accion) {
    Pila<T> temp;

    while (!estaVacia()) {
        T elemento = pop();
        accion(elemento);
        temp.push(elemento);
    }
    while (!temp.estaVacia()) {
        push(temp.pop());
    }
}

template<class T>
void Pila<T>::mostrar(function<void(T)> mostrarElemento) {
    if (estaVacia()) {
        cout << "Pila vacia" << endl;
        return;
    }

    Pila<T> temp;
    cout << "Pila (tope -> base): " << endl;
    while (!estaVacia()) {
        T elemento = pop();
        temp.push(elemento);

        cout << "| ";
        if (mostrarElemento) {
            mostrarElemento(elemento);
        }
        else {
            cout << elemento;
        }
        cout << " |" << endl;
    }

    cout << "---------" << endl;


    while (!temp.estaVacia()) {
        push(temp.pop());
    }
}
#endif
