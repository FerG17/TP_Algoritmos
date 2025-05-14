#pragma once
#ifndef __NODO_H__
#define __NODO_H__

template<class T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente;

    Nodo(T v, Nodo<T>* sig = nullptr) : valor(v), siguiente(sig) {}
};

#endif
