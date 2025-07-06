#pragma once
#include "Interfaz.h"
#include "ModuloEventos.h"
#include "ModuloServiciosAdmin.h"
#include "ModuloCompra.h"
#include "GeneradorDataSet.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <limits>

using namespace std;

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

class MenuPrincipal {
public:
    void iniciar();
private:
    void mostrarMensaje(string mensaje);
    void mostrarEjemplosGenerados(); // Nueva función
    GeneradorDataSet generadorDataSet; // Instancia para generar y acceder a los datos
    bool datasetGenerado = false;      // Controla si ya se generó el dataset para evitar duplicar
};

void MenuPrincipal::mostrarMensaje(string mensaje) {
    mostrarMensajeEstado(mensaje);
    Sleep(1500);
}

// Mostrar los ejemplos generados en memoria (ahora usando punteros)
void MenuPrincipal::mostrarEjemplosGenerados() {
    if (!datasetGenerado) {
        // 1. Generar 100 clientes y guardar
        generadorDataSet.generarDatasetClientes(100, "clientes.txt", "compras.txt");
        datasetGenerado = true;
        mostrarMensaje("Se generaron 100 clientes y se guardaron en clientes.txt y compras.txt.");
    }

    // 2. Mostrar SOLO LOS PRIMEROS 10 CLIENTES
    cout << "=== PRIMEROS 10 CLIENTES GENERADOS ===" << endl;
    const auto& clientes = generadorDataSet.getClientesGenerados();
    int mostrarCantidad = min(10, (int)clientes.size());
    for (int i = 0; i < mostrarCantidad; ++i) {
        const Cliente* c = clientes[i];
        cout << "DNI: " << c->getId()
            << " | Nombre: " << c->getNombre() << " " << c->getApellido()
            << " | Email: " << c->getEmail()
            << " | Telefono: " << c->getTelefono()
            << " | Direccion: " << c->getDireccion()
            << " | Puntos: " << c->getPuntosLealtad() << endl;
    }
    cout << endl;

    // 3. Mostrar SOLO LAS COMPRAS DE ESOS 10 CLIENTES (opcional)
    cout << "=== COMPRAS DE LOS 10 PRIMEROS CLIENTES ===" << endl;
    const auto& compras = generadorDataSet.getComprasGeneradas();
    for (int i = 0; i < mostrarCantidad; ++i) {
        const Cliente* c = clientes[i];
        cout << "Compras de " << c->getNombre() << " " << c->getApellido() << " (DNI: " << c->getId() << "):" << endl;
        for (const Compra* com : compras) {
            if (com->getClienteId() == c->getId()) {
                cout << "  ID Compra: " << com->getId()
                    << " | Fecha: " << com->getFechaCompra()
                    << " | Subtotal: " << com->getSubtotal()
                    << " | Desc: " << com->getDescuentoAplicado()
                    << " | Total: " << com->getTotal()
                    << " | MetodoPago: " << com->getMetodoPago()
                    << " | Estado: " << static_cast<int>(com->getEstado()) << endl;
            }
        }
        cout << endl;
    }
    pausar();
}

void MenuPrincipal::iniciar() {
    int opcion;
    ArbolB<Cliente*> arbolClientes(imprimirNombre, compararCliente);
    ModuloEventos moduloEventos;
    ModuloServiciosAdmin moduloServiciosAdmin(&arbolClientes);
    ModuloCompra moduloCompra(moduloEventos.getGestorEventosPtr(), &arbolClientes);
    bool primeraVez = true;

    do {
        if (primeraVez) {
            configurarConsola();
            primeraVez = false;
        }

        mostrarInterfaz();
        mostrarMenu();

        cout << "4. Mostrar ejemplos generados (dataset)" << endl;

        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 100;
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        cin >> opcion;

        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        switch (opcion) {
        case 1:
            limpiarYCentrarPantalla();
            moduloEventos.ejecutar();
            break;
        case 2:
            limpiarYCentrarPantalla();
            moduloCompra.ejecutar();
            break;
        case 3:
            limpiarYCentrarPantalla();
            moduloServiciosAdmin.ejecutar();
            break;
        case 4:
            limpiarYCentrarPantalla();
            mostrarEjemplosGenerados();
            break;
        case 0:
            mostrarMensaje("Gracias por usar Ticketek. ¡Hasta pronto!");
            exit(0);
        default:
            mostrarMensaje("Opcion invalida. Intente nuevamente.");
        }

    } while (opcion != 0);
}

