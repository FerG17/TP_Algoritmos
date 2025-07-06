#pragma once
//todo agregado
#include <functional>
#include <iostream>
using namespace std;

template <class T>
class Nodos {
public:
    T elemento;
    Nodos* izq;
    Nodos* der;
    Nodos() : elemento(), izq(nullptr), der(nullptr) {}
    Nodos(T elem) : elemento(elem), izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolB {
    typedef function<int(T, T)> Comp;    
    typedef function<void(T)> Proc; //add     
    Nodos<T>* raiz;
    Proc procesar;
    Comp comparar;
private:
    bool _buscar(Nodos<T>* Nodos, T e) {
        if (Nodos == nullptr) return false;
        else {
            int r = comparar(Nodos->elemento, e);
            if (r == 0) return true;
            else if (r < 0) {
                return _buscar(Nodos->der, e);
            }
            else {
                return _buscar(Nodos->izq, e);
            }
        }
    }
    Nodos<T>* _obtener(Nodos<T>* Nodos, T e) {
        if (Nodos == nullptr) return nullptr;
        else {
            int r = comparar(Nodos->elemento, e);
            if (r == 0) return Nodos;
            else if (r < 0) {
                return _obtener(Nodos->der, e);
            }
            else {
                return _obtener(Nodos->izq, e);
            }
        }
    }
    bool _insertar(Nodos<T>*& Nodos, T e) {
        if (Nodos == nullptr) {
            Nodos = new Nodos<T>();
            Nodos->elemento = e;
            Nodos->izq = Nodos->der = nullptr;
            return true;
        }
        else {
            int r = comparar(Nodos->elemento, e);
            if (r == 0) return false;
            else if (r < 0) {
                return _insertar(Nodos->der, e);
            }
            else {
                return _insertar(Nodos->izq, e);
            }
        }
    }
    void _enOrden(Nodos<T>* Nodos) {
        if (Nodos == nullptr) return;
        _enOrden(Nodos->izq);
        if (procesar) procesar(Nodos->elemento);
        _enOrden(Nodos->der);
    }
    void _preOrden(Nodos<T>* Nodos) {
        if (Nodos == nullptr) return;
        if (procesar) procesar(Nodos->elemento);
        _preOrden(Nodos->izq);
        _preOrden(Nodos->der);
    }
    void _postOrden(Nodos<T>* Nodos) {
        if (Nodos == nullptr) return;
        _postOrden(Nodos->izq);
        _postOrden(Nodos->der);
        if (procesar) procesar(Nodos->elemento);
    }
    bool _vacio() {
        return raiz == nullptr;
    }
    int _cantidad(Nodos<T>* Nodos) {
        if (Nodos == nullptr)
            return 0;
        else
        {
            int ci, cd;
            ci = _cantidad(Nodos->izq);
            cd = _cantidad(Nodos->der);
            return 1 + ci + cd;
        }
    }
    int _altura(Nodos<T>* Nodos) {
        if (Nodos == nullptr)
            return 0;
        else
        {
            int ai, ad;
            ai = 1 + _altura(Nodos->izq);
            ad = 1 + _altura(Nodos->der);
            return ai > ad ? ai : ad;
        }
    }
    T _minimo(Nodos<T>* Nodos) {
        if (Nodos->izq == nullptr) return Nodos->elemento;
        else
            return _minimo(Nodos->izq);
    }
    T _maximo(Nodos<T>* Nodos) {
        if (Nodos->der == nullptr) return Nodos->elemento;
        else
            return _maximo(Nodos->der);
    }
    bool _eliminar(Nodos<T>*& Nodos, T e) {
        if (Nodos == nullptr) return false;
        else {
            int r = comparar(Nodos->elemento, e);
            if (r < 0) {
                return _eliminar(Nodos->der, e);
            }
            else if (r > 0) {
                return _eliminar(Nodos->izq, e);
            }
            else {
                if (Nodos->der == nullptr && Nodos->izq == nullptr) {
                    delete Nodos;
                    Nodos = nullptr;
                    return true;
                }
                else if (Nodos->izq == nullptr) {
                    Nodos<T>* temp = Nodos;
                    Nodos = Nodos->der;
                    delete temp;
                    return true;
                }
                else if (Nodos->der == nullptr) {
                    Nodos<T>* temp = Nodos;
                    Nodos = Nodos->izq;
                    delete temp;
                    return true;
                }
                else {
                    Nodos<T>* aux = Nodos->der;
                    while (aux->izq != nullptr)
                    {
                        aux = aux->izq;
                    }
                    Nodos->elemento = aux->elemento;
                    return _eliminar(Nodos->der, aux->elemento);
                }
            }
        }
    }
    int _suma_total(Nodos<T>* Nodos) {
        if (Nodos == nullptr)
            return 0;
        else
        {
            int ci = 0, cd = 0;
            ci = _suma_total(Nodos->izq);
            cd = _suma_total(Nodos->der);
            return Nodos->elemento + cd + ci;
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

//void imprimir(int e) {
//std::cout << " " << e;
//}
//
//int main() {
//	//srand(time(0));
//	ArbolB<int>* arbol = new ArbolB<int>(imprimir);
//}
