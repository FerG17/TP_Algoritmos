#pragma once
#include <iostream>
#include <string>
#include <conio.h> 
#include "Compra.h"
#include "Cliente.h"
#include "Entrada.h"
#include "ModuloUtils.h" 
using namespace std;

class ModuloCompra {
private:
    Cliente cliente;
    Compra compra;

    void registrarCliente() {
        int id;
        string nombre, apellido, email, telefono, direccion;

        limpiarYCentrarPantalla();
        mostrarTituloModulo("REGISTRO DE CLIENTE");

        int y = 18;

        gotoxy(45, y++);
        cout << "Ingrese ID (DNI): ";
        cin >> id;
        cin.ignore();

        gotoxy(45, y++);
        cout << "Nombre: ";
        getline(cin, nombre);

        gotoxy(45, y++);
        cout << "Apellido: ";
        getline(cin, apellido);

        gotoxy(45, y++);
        cout << "Email: ";
        getline(cin, email);

        while (!cliente.validarEmail(email)) {
            setColor(ROJO_CLARO, COLOR_FONDO);
            gotoxy(45, y++);
            cout << "Email invalido. Ingrese un correo valido: ";
            setColor(COLOR_TEXTO, COLOR_FONDO);
            getline(cin, email);
        }

        gotoxy(45, y++);
        cout << "Telefono: ";
        getline(cin, telefono);

        gotoxy(45, y++);
        cout << "Direccion: ";
        getline(cin, direccion);

        cliente = Cliente(id, nombre, apellido, email, telefono, direccion);

        ofstream archivoClientes("clientes.txt", ios::app);
        if (archivoClientes.is_open()) {
            cliente.guardarEnArchivo(archivoClientes);
            archivoClientes.close();
        }
        else {
            gotoxy(45, y++);
            setColor(ROJO_CLARO, COLOR_FONDO);
            cout << "Error al guardar cliente en archivo.";
            setColor(COLOR_TEXTO, COLOR_FONDO);
        }

        gotoxy(45, y + 1);
        setColor(VERDE_CLARO, COLOR_FONDO);
        cout << "Cliente registrado exitosamente.";
        setColor(COLOR_TEXTO, COLOR_FONDO);

        Sleep(1500);
    }

    void agregarEvento() {
        int eventoId, asientoId;
        double precio;

        limpiarYCentrarPantalla();
        gotoxy(45, 18);
        mostrarTituloModulo("AGREGAR EVENTO");

        int y = 19;

        gotoxy(45, y++);
        cout << "Ingrese ID del evento: ";
        cin >> eventoId;

        gotoxy(45, y++);
        cout << "Ingrese ID del asiento: ";
        cin >> asientoId;

        gotoxy(45, y++);
        cout << "Ingrese precio del evento: ";
        cin >> precio;

        Entrada entrada(eventoId, asientoId, precio);
        compra.agregarEntrada(entrada);

        cliente.sumarPuntos(20);

        gotoxy(45, y + 1);
        setColor(VERDE_CLARO, COLOR_FONDO);
        cout << "Evento agregado a la compra. Puntos actuales: " << cliente.getPuntosLealtad();
        setColor(COLOR_TEXTO, COLOR_FONDO);

        Sleep(1500);
    }

    void mostrarCompra() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("RESUMEN DE COMPRA");
        int y = 18;
        if (compra.getCantidadEntradas() == 0) {
            gotoxy(45, y++);
            setColor(ROJO_CLARO, COLOR_FONDO);
            cout << "No hay eventos registrados en la compra.";
            setColor(COLOR_TEXTO, COLOR_FONDO);
            Sleep(1500);
            return;
        }
        compra.getEntradas().ordenarQuick([](const Entrada& a, const Entrada& b) {
            return a.getPrecio() < b.getPrecio();
            });
        gotoxy(45, y);
        compra.mostrarResumen();
        pausarContinuar();
    }


    void consultarPrecios() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("CONSULTA DE PRECIOS");

        int y = 18;

        gotoxy(45, y++);
        cout << "Subtotal sin descuento: S/. " << compra.calcularSubtotal();

        gotoxy(45, y++);
        cout << "Total con descuento aplicado: S/. " << compra.calcularTotal();

        pausarContinuar();
    }

    void mostrarPuntos() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("PUNTOS DE LEALTAD");

        int y = 18;

        int puntos = cliente.getPuntosLealtad();

        gotoxy(45, y++);
        cout << "Puntos de lealtad acumulados: " << puntos;

        gotoxy(45, y++);
        cout << "Descuento disponible: " << (puntos / 20) * 5 << "%";

        pausarContinuar();
    }

public:
    void ejecutar() {
        int opcion;
        registrarCliente();

        do {
            limpiarYCentrarPantalla();
            mostrarTituloModulo("MODULO COMPRA");

            int y = 18;

            gotoxy(45, y++);
            cout << "1. Registrarse en evento";

            gotoxy(45, y++);
            cout << "2. Mostrar compra";

            gotoxy(45, y++);
            cout << "3. Consultar precios";

            gotoxy(45, y++);
            cout << "4. Ver puntos de lealtad";

            gotoxy(45, y++);
            cout << "5. Ver detalles del cliente";

            gotoxy(45, y++);
            cout << "6. Imprimir entradas compradas";

            gotoxy(45, y++);
            cout << "0. Volver al menu principal";

            gotoxy(45, y + 2);
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                agregarEvento();
                break;
            case 2:
                mostrarCompra();
                break;
            case 3:
                consultarPrecios();
                break;
            case 4:
                mostrarPuntos();
                break;
            case 5:
                limpiarYCentrarPantalla();
                cliente.mostrarDetalles();
                pausarContinuar();
                break;
            case 6:
                limpiarYCentrarPantalla();
                compra.getEntradas().ordenarQuick([](const Entrada& a, const Entrada& b) {
                    return a.getPrecio() < b.getPrecio();
                    });
                for (size_t i = 0; i < compra.getCantidadEntradas(); i++) {
                    Entrada e = compra.getEntradas().obtener(i);
                    e.imprimirEntrada();
                }
                pausarContinuar();
                break;
            case 0:
                gotoxy(45, y + 4);
                cout << "Volviendo al menu principal...";
                Sleep(1000);
                break;
            default:
                gotoxy(45, y + 4);
                setColor(ROJO_CLARO, COLOR_FONDO);
                cout << "Opcion invalida. Intente nuevamente.";
                setColor(COLOR_TEXTO, COLOR_FONDO);
                Sleep(1500);
            }
        } while (opcion != 0);
    }
};
