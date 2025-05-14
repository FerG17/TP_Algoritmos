#pragma once

class Asiento {
    int numero;
    bool disponible;
public:
    Asiento(int n) : numero(n), disponible(true) {}
    bool estaDisponible() const { return disponible; }
    void reservar() { disponible = false; }
    int getNumero() const { return numero; }
};
