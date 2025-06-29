#pragma once
#include <iostream>
#include "GestorEventos.h"
#include "Concierto.h"
#include "Lugar.h"
#include "ObraTeatral.h"
#include "Deporte.h"
#include "Festival.h"
#include "Lista.h"
#include "Evento.h"
#include "Lugar.h"
#include "ModuloUtils.h"
class ModuloEventos {
private:
    Lugar lugar;
    GestorEventos gestor;

public:
    ModuloEventos() : lugar("Estadio Nacional") {}
    void cargarEventosDeEjemplo() {
        Evento* e1 = new Concierto(1, "RockFest", "2025-06-10", 150, "Los Riffs");
        Evento* e2 = new Concierto(2, "MetalVibe", "2025-07-01", 200, "Iron Scream");
        Evento* e3 = new ObraTeatral(3, "Hamlet", "2025-08-15", 90, "Juan Perez", 120);
        Evento* e4 = new Festival(4, "Book Fest", "2025-06-07", 50, 2, "Libros");
        Evento* e5 = new Deporte(5, "El Clasico", "2025-08-12", 70, "Universitario", "Alianza Lima");
        gestor.agregarEvento(e1);
        gestor.agregarEvento(e2);
        gestor.agregarEvento(e3);
        gestor.agregarEvento(e4);
        gestor.agregarEvento(e5);

    }
    void ejecutar() {
        cargarEventosDeEjemplo();

        int opcion;
        int opcionA;
        do {
            limpiarYCentrarPantalla(); 
            mostrarTituloModulo("MODULO EVENTOS");

            int y = 50;
            gotoxy(45, y++); cout << "1. Ver todos los eventos";
            gotoxy(45, y++); cout << "2. Buscar por mes (MM)";
            gotoxy(45, y++); cout << "3. Mostrar historial";
            gotoxy(45, y++); cout << "4. Ver eventos y asientos del lugar";
            gotoxy(45, y++); cout << "5. Ver asientos en orden inverso";
            gotoxy(45, y++); cout << "0. Volver al menu principal";
            gotoxy(45, y++); cout << "Opcion: ";
            gotoxy(53, y - 1); cin >> opcion;

            system("cls");

            switch (opcion) {
            case 1:
                limpiarYCentrarPantalla();
                gestor.mostrarEventos();
                pausarContinuar();
                break;

            case 2: {
                limpiarYCentrarPantalla();
                gotoxy(45, 30); cout << "Ingrese mes (ej: 06): ";
                string mes;
                cin >> mes;
                Evento* e = gestor.buscarPorMes(mes);
                limpiarYCentrarPantalla();
                if (e) {
                    gotoxy(45, 30); cout << "Evento encontrado:";
                    gotoxy(45, 31); e->mostrar();
                    gestor.historialPush(e);
                }
                else {
                    gotoxy(45, 30); cout << "No se encontro evento para ese mes.";
                }
                pausarContinuar();
                break;
            }

            case 3:
                limpiarYCentrarPantalla();
                gestor.historialPop();
                pausarContinuar();
                break;

            case 4: {
                limpiarYCentrarPantalla();
                gotoxy(45, 28); cout << "EVENTOS DISPONIBLES";
                for (size_t i = 0; i < gestor.getEventos().tamaño(); ++i) {
                    gotoxy(45, 30 + i);
                    cout << i + 1 << ". ";
                    gestor.getEventos().obtener(i)->mostrar();
                }

                int seleccion;
                gotoxy(45, 40); cout << "Seleccione un evento: ";
                cin >> seleccion;
                if (seleccion < 1 || seleccion > gestor.getEventos().tamaño()) {
                    gotoxy(45, 42); cout << "Opcion invalida.";
                    pausarContinuar();
                    break;
                }

                Evento* evento = gestor.getEventos().obtener(seleccion - 1);
                limpiarYCentrarPantalla();
                gotoxy(45, 30); cout << "ASIENTOS PARA: " << evento->getNombre();
                gotoxy(45, 32); cout << "1. Principal";
                gotoxy(45, 33); cout << "2. VIP";
                gotoxy(45, 34); cout << "3. GOLD";
                gotoxy(45, 35); cout << "Seleccione una opcion: ";
                cin >> opcionA;
                system("cls");

                switch (opcionA) {
                case 1: evento->getSeccion()->mostrarAsientos(); break;
                case 2: evento->getSeccionGeneral()->mostrarAsientos(); break;
                case 3: evento->getSeccionVIP()->mostrarAsientos(); break;
                default:
                    gotoxy(45, 30); cout << "Opcion invalida.";
                }
                pausarContinuar();
                break;
            }

            case 5: {
                limpiarYCentrarPantalla();
                gotoxy(45, 28); cout << "EVENTOS DISPONIBLES";
                for (size_t i = 0; i < gestor.getEventos().tamaño(); ++i) {
                    gotoxy(45, 30 + i);
                    cout << i + 1 << ". ";
                    gestor.getEventos().obtener(i)->mostrar();
                }

                int seleccion;
                gotoxy(45, 40); cout << "Seleccione un evento: ";
                cin >> seleccion;
                if (seleccion < 1 || seleccion > gestor.getEventos().tamaño()) {
                    gotoxy(45, 42); cout << "Opcion invalida.";
                    pausarContinuar();
                    break;
                }

                Evento* evento = gestor.getEventos().obtener(seleccion - 1);
                limpiarYCentrarPantalla();
                gotoxy(45, 30); cout << "ASIENTOS PARA: " << evento->getNombre();
                gotoxy(45, 32); cout << "1. Principal";
                gotoxy(45, 33); cout << "2. VIP";
                gotoxy(45, 34); cout << "3. GOLD";
                gotoxy(45, 35); cout << "Seleccione una opcion: ";
                cin >> opcionA;
                system("cls");

                switch (opcionA) {
                case 1: evento->getSeccion()->mostrarAsientosInverso(); break;
                case 2: evento->getSeccionGeneral()->mostrarAsientosInverso(); break;
                case 3: evento->getSeccionVIP()->mostrarAsientosInverso(); break;
                default:
                    gotoxy(45, 30); cout << "Opcion invalida.";
                }
                pausarContinuar();
                break;
            }

            case 0:
                gotoxy(45, 30); cout << "Saliendo del modulo eventos...";
                break;

            default:
                gotoxy(45, 30); cout << "Opcion invalida.";
                pausarContinuar();
            }

        } while (opcion != 0);
    }
    GestorEventos* getGestorEventosPtr() { return &gestor; }
};
