#pragma once
#include <functional>
#include <iostream>
using namespace std;

template <class T>
class NodoArbol {
public:
    T elemento;
    NodoArbol<T>* izq;
    NodoArbol<T>* der;
    NodoArbol() : elemento(), izq(nullptr), der(nullptr) {}
    NodoArbol(T elem) : elemento(elem), izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolB {
    typedef function<int(T, T)> Comp;
    typedef function<void(T)> Proc;
    NodoArbol<T>* raiz;
    Proc procesar;
    Comp comparar;
private:
    bool _buscar(NodoArbol<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return true;
            else if (r < 0) {
                return _buscar(nodo->der, e);
            }
            else {
                return _buscar(nodo->izq, e);
            }
        }
    }
    NodoArbol<T>* _obtener(NodoArbol<T>* nodo, T e) {
        if (nodo == nullptr) return nullptr;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return nodo;
            else if (r < 0) {
                return _obtener(nodo->der, e);
            }
            else {
                return _obtener(nodo->izq, e);
            }
        }
    }
    bool _insertar(NodoArbol<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>();
            nodo->elemento = e;
            nodo->izq = nodo->der = nullptr;
            return true;
        }
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return false;
            else if (r < 0) {
                return _insertar(nodo->der, e);
            }
            else {
                return _insertar(nodo->izq, e);
            }
        }
    }
    void _enOrden(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        if (procesar) procesar(nodo->elemento);
        _enOrden(nodo->der);
    }
    void _preOrden(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return;
        if (procesar) procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }
    void _postOrden(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        if (procesar) procesar(nodo->elemento);
    }
    bool _vacio() {
        return raiz == nullptr;
    }
    int _cantidad(NodoArbol<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ci, cd;
            ci = _cantidad(nodo->izq);
            cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }
    }
    int _altura(NodoArbol<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ai, ad;
            ai = 1 + _altura(nodo->izq);
            ad = 1 + _altura(nodo->der);
            return ai > ad ? ai : ad;
        }
    }
    T _minimo(NodoArbol<T>* nodo) {
        if (nodo->izq == nullptr) return nodo->elemento;
        else
            return _minimo(nodo->izq);
    }
    T _maximo(NodoArbol<T>* nodo) {
        if (nodo->der == nullptr) return nodo->elemento;
        else
            return _maximo(nodo->der);
    }
    bool _eliminar(NodoArbol<T>*& nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r < 0) {
                return _eliminar(nodo->der, e);
            }
            else if (r > 0) {
                return _eliminar(nodo->izq, e);
            }
            else {
                if (nodo->der == nullptr && nodo->izq == nullptr) {
                    delete nodo;
                    nodo = nullptr;
                    return true;
                }
                else if (nodo->izq == nullptr) {
                    NodoArbol<T>* temp = nodo;
                    nodo = nodo->der;
                    delete temp;
                    return true;
                }
                else if (nodo->der == nullptr) {
                    NodoArbol<T>* temp = nodo;
                    nodo = nodo->izq;
                    delete temp;
                    return true;
                }
                else {
                    NodoArbol<T>* aux = nodo->der;
                    while (aux->izq != nullptr)
                    {
                        aux = aux->izq;
                    }
                    nodo->elemento = aux->elemento;
                    return _eliminar(nodo->der, aux->elemento);
                }
            }
        }
    }
    int _suma_total(NodoArbol<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ci = 0, cd = 0;
            ci = _suma_total(nodo->izq);
            cd = _suma_total(nodo->der);
            return nodo->elemento + cd + ci;
        }
    }

public:
    ArbolB(void(*otroPunteroAFuncion)(T), Comp cmp = nullptr) {
        this->procesar = otroPunteroAFuncion;
        if (cmp) {
            this->comparar = cmp;
        }
        else {
            this->comparar = [](T a, T b)->int { return a - b; };
        }
        raiz = nullptr;
    }
    ArbolB() {
        raiz = nullptr;
        procesar = nullptr;
        comparar = [](T a, T b)->int { return a - b; };
    }
    void setProcesar(void(*proc)(T)) { procesar = proc; }
    void setComparar(Comp cmp) { comparar = cmp; }

    bool insertar(T e) {
        return _insertar(raiz, e);
    }
    void enOrden() {
        _enOrden(raiz);
    }
    void preOrden() {
        _preOrden(raiz);
    }
    void postOrden() {
        _postOrden(raiz);
    }
    int cantidad() {
        return _cantidad(raiz);
    }
    int altura() {
        return _altura(raiz);
    }
    bool Buscar(T e) {
        return _buscar(raiz, e);
    }
    T Minimo() {
        return _minimo(raiz);
    }
    T Maximo() {
        return _maximo(raiz);
    }
    bool Eliminar(T e) {
        return _eliminar(raiz, e);
    }
    int suma_total() {
        return _suma_total(raiz);
    }
};
