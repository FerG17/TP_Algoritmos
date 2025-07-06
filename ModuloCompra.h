#pragma once
#include <iostream>
#include <string>
#include <conio.h> 
#include "Compra.h"
#include "Cliente.h"
#include "Entrada.h"
#include "ModuloUtils.h" 
#include "ArbolB.h"
using namespace std;

int compararCliente(Cliente* a, Cliente* b) {
    if (a->getId() < b->getId()) return -1;
    if (a->getId() > b->getId()) return 1;
    return 0;
}
void imprimirNombre(Cliente* c) {
    cout << c->getNombre() << endl;
}

class ModuloCompra {
private:
    Cliente cliente;
    Compra compra;
    GestorEventos* gestorEventos;
    ArbolB<Cliente*> arbolClientes;

    //ANALISIS 6

    void registrarCliente() {
        int id;
        string nombre, apellido, email, telefono, direccion;

        limpiarYCentrarPantalla();
        mostrarTituloModulo("REGISTRO DE CLIENTE");

        int y = 18;//1

        gotoxy(45, y++);
        cout << "Ingrese ID (DNI): ";//1
        cin >> id;//1
        cin.ignore();

        gotoxy(45, y++);//1
        cout << "Nombre: ";//1
        getline(cin, nombre);//1

        gotoxy(45, y++);//1
        cout << "Apellido: ";//1
        getline(cin, apellido);//1

        gotoxy(45, y++);//1
        cout << "Email: ";//1
        getline(cin, email);//1

        while (!cliente.validarEmail(email)) {//n
            setColor(ROJO_CLARO, COLOR_FONDO);
            gotoxy(45, y++);//1
            cout << "Email invalido. Ingrese un correo valido: ";//1
            setColor(COLOR_TEXTO, COLOR_FONDO);
            getline(cin, email);//1
        }

        gotoxy(45, y++);//1
        cout << "Telefono: ";//1
        getline(cin, telefono);//1

        gotoxy(45, y++);//1
        cout << "Direccion: ";//1
        getline(cin, direccion);//1

        cliente = Cliente(id, nombre, apellido, email, telefono, direccion);//1
        Cliente* nuevoCliente = new Cliente(id, nombre, apellido, email, telefono, direccion);
        arbolClientes.insertar(nuevoCliente);

        ofstream archivoClientes("clientes.txt", ios::app);
        if (archivoClientes.is_open()) {//1
            cliente.guardarEnArchivo(archivoClientes);
            archivoClientes.close();
        }
        else {//1
            gotoxy(45, y++);//1
            setColor(ROJO_CLARO, COLOR_FONDO);
            cout << "Error al guardar cliente en archivo.";//1
            setColor(COLOR_TEXTO, COLOR_FONDO);
        }

        gotoxy(45, y + 1);//1
        setColor(VERDE_CLARO, COLOR_FONDO);
        cout << "Cliente registrado exitosamente.";//1
        setColor(COLOR_TEXTO, COLOR_FONDO);

        Sleep(1500);
    } //n+28 = O(n)

    void agregarEvento() {
        limpiarYCentrarPantalla();
        mostrarTituloModulo("SELECCIONAR EVENTO");

        int y = 20;
        auto& eventos = gestorEventos->getEventos();
        if (eventos.tamaño() == 0) {
            gotoxy(45, y++); cout << "No hay eventos disponibles.";
            pausarContinuar();
            return;
        }
        for (size_t i = 0; i < eventos.tamaño(); ++i) {
            gotoxy(45, y++);
            cout << i + 1 << ". ";
            eventos.obtener(i)->mostrar();
        }
        int seleccion;
        gotoxy(45, y + 1); cout << "Seleccione el evento (numero): ";
        cin >> seleccion;

        if (seleccion < 1 || seleccion > eventos.tamaño()) {
            gotoxy(45, y + 3); cout << "Opcion invalida.";
            pausarContinuar();
            return;
        }

        Evento* eventoSeleccionado = eventos.obtener(seleccion - 1);

        gotoxy(45, y + 4); cout << "Precio del evento: S/. " << eventoSeleccionado->getPrecio();

        int asientoId;
        gotoxy(45, y + 5); cout << "Ingrese ID del asiento: ";
        cin >> asientoId;
        Entrada entrada(eventoSeleccionado->getId(), asientoId, eventoSeleccionado->getPrecio());
        compra.agregarEntrada(entrada);
        cliente.sumarPuntos(20);

        gotoxy(45, y + 6);
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

    ModuloCompra(GestorEventos* gestor)
        : gestorEventos(gestor),
        arbolClientes(imprimirNombre, compararCliente) {} //agregado el arbol a modulo compra para agregar

    ArbolB<Cliente*>* getArbolClientes() { return &arbolClientes; }

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
