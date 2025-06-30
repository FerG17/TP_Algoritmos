#pragma once
#include <iostream>

class HashEntidad {
private:	
	int key;
	int value;
public:
	HashEntidad(int key, int value) {
		this->key = key;
		this->value = value;
	}
	int getKey() { return key; }
	int getValue() { return value; }
};


class HashTabla {
private:
	HashEntidad** tabla;
	int numElementos;
	int TABLE_SIZE;

public:
	HashTabla(int TABLE_SIZE = 128) {
		this->TABLE_SIZE = TABLE_SIZE;
		tabla = new HashEntidad * [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i) {
			tabla[i] = nullptr;
		}
		numElementos = 0;
	}
	~HashTabla()
	{
		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}

	void insertar(int key, int value) {
		int base, step, hash;
		if (numElementos == TABLE_SIZE)return;
		base = key % TABLE_SIZE;
		hash = base;
		step = 0;
		while (tabla[hash] != nullptr)
		{
			hash = (base + step) % TABLE_SIZE;
			step++;
		}
		tabla[hash] = new HashEntidad(key, value);
		numElementos++;
	}
	int size() {
		return TABLE_SIZE;
	}
	int sizeactual() {
		return numElementos;
	}
	int buscar(int key) {
		int step = 0;
		int i, base;
		i = base = key % TABLE_SIZE; 
		while (true)
		{
			if (tabla[i] == nullptr)return -1;
			else if (tabla[i]->getKey() == key) {
				return i;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
};
