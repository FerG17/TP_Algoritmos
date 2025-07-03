#ifndef __ArbolB_HPP__
#define __ArbolB_HPP__

#include <functional>
using namespace std;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
};

template <class T>
class ArbolB {
	typedef function<int(T, T)> Comp; //Lambda
	Nodo<T>* raiz;
	void(*procesar)(T);
	Comp comparar;
private:
	bool _buscar(Nodo<T>* nodo, T e) {
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
	Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>();
			nodo->elemento = e;
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
	void _enOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
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
	int _altura(Nodo<T>* nodo) {
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

	int _minimo(Nodo<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);
	}
	int _maximo(Nodo<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}
	bool _eliminar(Nodo<T>*& nodo, T e) {
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
					nodo = nullptr;
					delete nodo;
					return true;
				}
				else if (nodo->izq == nullptr) {
					nodo = nodo->der;
					return true;
				}
				else if (nodo->der == nullptr) {
					nodo = nodo->izq;
					return true;
				}
				else {
					Nodo<T>* aux = nodo->der;
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
	int _suma_total(Nodo<T>* nodo) {
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
	ArbolB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = [](T a, T b)->int {return a - b; };
		raiz = nullptr;
	}
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
	int Minimo() {
		return _minimo(raiz);
	}
	int Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}

	int suma_total() {
		return _suma_total(raiz);
	}
};
#endif

//void imprimir(int e) {
//std::cout << " " << e;
//}
//
//int main() {
//	//srand(time(0));
//	ArbolB<int>* arbol = new ArbolB<int>(imprimir);
//}
