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

    Nodo<T>* mergeSort(Nodo<T>* head, std::function<bool(const T&, const T&)> comp) {
        if (!head || !head->siguiente) return head;
        Nodo<T>* slow = head;
        Nodo<T>* fast = head->siguiente;
        while (fast && fast->siguiente) {
            slow = slow->siguiente;
            fast = fast->siguiente->siguiente;
        }
        Nodo<T>* mid = slow->siguiente;
        slow->siguiente = nullptr;
        Nodo<T>* left = mergeSort(head, comp);
        Nodo<T>* right = mergeSort(mid, comp);
        return merge(left, right, comp);
    }

    Nodo<T>* merge(Nodo<T>* left, Nodo<T>* right, std::function<bool(const T&, const T&)> comp) {
        Nodo<T> dummy{ T() };
        Nodo<T>* tail = &dummy;
        while (left && right) {
            if (comp(left->valor, right->valor)) {
                tail->siguiente = left;
                left = left->siguiente;
            }
            else {
                tail->siguiente = right;
                right = right->siguiente;
            }
            tail = tail->siguiente;
        }
        tail->siguiente = (left ? left : right);
        return dummy.siguiente;
    }

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
    void ordenarQuick(function<bool(T, T)> comparador);
    Nodo<T>* quickSortInterno(Nodo<T>* cabeza, function<bool(T, T)> comparador);
    Nodo<T>* concatenarListas(Nodo<T>* menor, Nodo<T>* igual, Nodo<T>* mayor);
    void ordenarMerge(function<bool(const T&, const T&)> comp);
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

//ANALISIS 1

template<class T>
void Lista<T>::insertarFinal(T v) {
    Nodo<T>* nuevo = new Nodo<T>(v); //1

    if (inicio == nullptr) { //1-->+interno
        inicio = nuevo; //1
    }
    else {
        Nodo<T>* temp = inicio; //1
        while (temp->siguiente != nullptr) { //n
            temp = temp->siguiente; //1
        }
        temp->siguiente = nuevo; //1
    }
    longitud++; //1
} //7+n= O(n)

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

//ANALISIS 7

template<class T>
void Lista<T>::eliminarValor(T v) {
    if (estaVacia()) {//1
        return;
    }
    if (inicio->valor == v) {//1
        Nodo<T>* temp = inicio;//1
        inicio = inicio->siguiente;//1
        delete temp;
        longitud--;//1
        return;
    }
    Nodo<T>* actual = inicio;//1
    while (actual->siguiente != nullptr && actual->siguiente->valor != v) {//n
        actual = actual->siguiente;//1
    }
    if (actual->siguiente != nullptr) {//1
        Nodo<T>* temp = actual->siguiente;//1
        actual->siguiente = temp->siguiente;//1
        delete temp;//1
        longitud--;//1
    } 
}//n+12 = O(n)

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


//ANALISIS 2

template<class T>
void Lista<T>::ordenar(function<bool(T, T)> comparador) {
    if (estaVacia() || longitud == 1) { //1
        return;
    }
    bool intercambio;
    Nodo<T>* actual;
    Nodo<T>* siguiente = nullptr; //1

    do { //n
        intercambio = false; //1
        actual = inicio; //1
        while (actual->siguiente != siguiente) { //n*n
            if (comparador(actual->valor, actual->siguiente->valor)) { //1
                T temp = actual->valor;//1
                actual->valor = actual->siguiente->valor;//1
                actual->siguiente->valor = temp;
                intercambio = true;//1
            }
            actual = actual->siguiente;//1
        }
        siguiente = actual;//1
    } while (intercambio);//n*n
} //n*n+10 = O(n^2)


//ANALISIS 3
template<class T>
T Lista<T>::buscar(function<bool(T)> condicion) {
    Nodo<T>* temp = inicio; //1

    while (temp != nullptr) { //n
        if (condicion(temp->valor)) { //1
            return temp->valor;
        }
        temp = temp->siguiente; //1
    }
    return T();
}//n+3= O(n)



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


//ORDENAMIENTO AVANZADO QUICKSORT

template<class T>
Nodo<T>* Lista<T>::concatenarListas(Nodo<T>* menor, Nodo<T>* igual, Nodo<T>* mayor) {
    Nodo<T>* cabeza = nullptr, ** ultimo = &cabeza;

    for (Nodo<T>* lista : { menor, igual, mayor }) {
        while (lista) {
            *ultimo = lista;
            ultimo = &((*ultimo)->siguiente);
            lista = lista->siguiente;
        }
    }
    *ultimo = nullptr;
    return cabeza;
}

template<class T>
Nodo<T>* Lista<T>::quickSortInterno(Nodo<T>* cabeza, function<bool(T, T)> comparador) {
    if (!cabeza || !cabeza->siguiente) return cabeza;
    T pivote = cabeza->valor;  
    Nodo<T>* menor = nullptr;   
    Nodo<T>* igual = nullptr;  
    Nodo<T>* mayor = nullptr;    
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* siguiente = actual->siguiente;
        if (comparador(actual->valor, pivote)) {
            actual->siguiente = menor;
            menor = actual;
        }
        else if (comparador(pivote, actual->valor)) {
            actual->siguiente = mayor;
            mayor = actual;
        }
        else {
            actual->siguiente = igual;
            igual = actual;
        }
        actual = siguiente;
    }
    menor = quickSortInterno(menor, comparador);
    mayor = quickSortInterno(mayor, comparador);
    return concatenarListas(menor, igual, mayor);
}

template <class T>
void Lista<T>::ordenarQuick(function<bool(T, T)> comparador) {
    inicio = quickSortInterno(inicio, comparador);
}
template<class T>
void Lista<T>::ordenarMerge(std::function<bool(const T&, const T&)> comp) {
    inicio = mergeSort(inicio, comp);
}

#endif
