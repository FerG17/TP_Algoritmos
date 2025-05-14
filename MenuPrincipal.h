#pragma once
#include "Interfaz.h"
#include "ModuloEventos.h"
#include "ModuloServiciosAdmin.h"
#include "ModuloCompra.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

class MenuPrincipal {
public:
    void iniciar();
private:
    void mostrarMensaje(string mensaje);
};

void MenuPrincipal::mostrarMensaje(string mensaje) {
    mostrarMensajeEstado(mensaje);
    Sleep(1500);
}

void MenuPrincipal::iniciar() {
    int opcion;
    ModuloEventos moduloEventos;
    ModuloServiciosAdmin moduloServiciosAdmin;
    ModuloCompra moduloCompra;
    bool primeraVez = true;

    do {
        if (primeraVez) {
            configurarConsola();  
            primeraVez = false;
        }

        mostrarInterfaz();  
        mostrarMenu();      

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
        case 0:
            mostrarMensaje("Gracias por usar Ticketek. ¡Hasta pronto!");
            exit(0);
        default:
            mostrarMensaje("Opcion invalida. Intente nuevamente.");
        }

    } while (opcion != 0);
}
