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
using namespace std;

class MenuPrincipal {
public:
    void iniciar();
private:
    void mostrarMensaje(string mensaje);
    void mostrarEjemplosGenerados(); 
    GeneradorDataSet generadorDataSet;
    bool datasetGenerado = false;
};

void MenuPrincipal::mostrarMensaje(string mensaje) {
    mostrarMensajeEstado(mensaje);
    Sleep(1500);
}

// Mostrar los ejemplos generados en memoria
void MenuPrincipal::mostrarEjemplosGenerados() {
    if (!datasetGenerado) {
        // Genera el dataset solo la primera vez (puedes modificar la cantidad de clientes)
        generadorDataSet.generarDatasetClientes(10, "clientes.txt", "compras.txt");
        datasetGenerado = true;
        mostrarMensaje("Se generaron los datos de ejemplo y se guardaron en clientes.txt y compras.txt.");
    }

    // Mostrar clientes generados
    cout << "=== CLIENTES GENERADOS ===" << endl;
    const auto& clientes = generadorDataSet.getClientesGenerados();
    for (const Cliente& c : clientes) {
        // Puedes personalizar el formato de impresión según lo que tenga la clase Cliente
        cout << "DNI: " << c.getId() << " | Nombre: " << c.getNombre() << " " << c.getApellido()
            << " | Email: " << c.getEmail() << " | Telefono: " << c.getTelefono()
            << " | Direccion: " << c.getDireccion() << " | Puntos: " << c.getPuntosLealtad() << endl;
    }
    cout << endl << "=== COMPRAS GENERADAS ===" << endl;
    const auto& compras = generadorDataSet.getComprasGeneradas();
    for (const Compra& com : compras) {
        cout << "ID Compra: " << com.getId() << " | ClienteID: " << com.getClienteId()
            << " | Fecha: " << com.getFechaCompra() << " | Subtotal: " << com.getSubtotal()
            << " | Desc: " << com.getDescuentoAplicado() << " | Total: " << com.getTotal()
            << " | MetodoPago: " << com.getMetodoPago() << " | Estado: " << static_cast<int>(com.getEstado()) << endl;
    }
    cout << endl;

    mostrarMensaje("Fin de la muestra de ejemplos generados.");
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
