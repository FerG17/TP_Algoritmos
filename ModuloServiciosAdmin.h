#pragma once
#pragma once
#include "DescuentoPromocion.h"
#include "ReseñaEvento.h"
#include "Administrador.h"
#include <iostream>
#include <functional>
using namespace std;

class ModuloServiciosAdmin {
private:
    DescuentoPromocion descuentos[5] = {
        DescuentoPromocion(1, "Descuento Verano", 15.0f, true),
        DescuentoPromocion(2, "Black Friday", 30.0f, false),
        DescuentoPromocion(3, "Promo Fin de Ano", 20.0f, true),
        DescuentoPromocion(4, "Descuento Navidad", 25.0f, true),
        DescuentoPromocion(5, "Cyber Monday", 40.0f, false)
    };

    ReseñaEvento resenas[4] = {
        ReseñaEvento(1, "Excelente organizacion", 5, "Juan Perez"),
        ReseñaEvento(2, "Buen evento, pero falto comida", 3, "Maria Garcia"),
        ReseñaEvento(3, "Me encanto el lugar", 4, "Carlos Rodriguez"),
        ReseñaEvento(4, "La musica estaba muy alta", 2, "Ana Lopez")
    };

    Administrador admins[3] = {
        Administrador(1, "Admin", "Principal", "admin@evento.com", "1234567890", "admin123"),
        Administrador(2, "Super", "Usuario", "super@evento.com", "0987654321", "super456"),
        Administrador(3, "Moderador", "Sistema", "mod@evento.com", "1122334455", "mod789")
    };

    void limpiarPantalla() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pausar() {
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    void menuDescuentos() {
        int opcion;
        do {
            cout << "\n==== MENU DE DESCUENTOS Y PROMOCIONES ====\n";
            cout << "1. Mostrar todos los descuentos\n";
            cout << "2. Filtrar por descuentos vigentes\n";
            cout << "3. Buscar descuentos con porcentaje minimo\n";
            cout << "4. Aumentar porcentaje a descuentos vigentes\n";
            cout << "0. Volver al menu anterior\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1: {
                cout << "\n=== TODOS LOS DESCUENTOS ===\n";
                for (int i = 0; i < 5; i++) {
                    descuentos[i].mostrar();
                }
                break;
            }
            case 2: {
                cout << "\n=== DESCUENTOS VIGENTES ===\n";
                auto estaVigente = [](const DescuentoPromocion& d) {
                    return d.estaVigente();
                    };
                DescuentoPromocion::filtrarMostrar(descuentos, 5, estaVigente);
                break;
            }
            case 3: {
                float minimo;
                cout << "Ingrese el porcentaje minimo a buscar: ";
                cin >> minimo;

                cout << "\n=== DESCUENTOS CON " << minimo << "% O MAS ===\n";
                // LAMBDA
                auto superaMinimo = [minimo](const DescuentoPromocion& d) {
                    return d.getPorcentaje() >= minimo;
                    };
                DescuentoPromocion::filtrarMostrar(descuentos, 5, superaMinimo);
                break;
            }
            case 4: {
                float incremento;
                cout << "Ingrese el incremento para los descuentos vigentes: ";
                cin >> incremento;

                // LAMBDA
                auto estaVigente = [](const DescuentoPromocion& d) {
                    return d.estaVigente();
                    };

                // LAMBDA
                auto aplicarIncremento = [incremento](DescuentoPromocion& d) {
                    d.setPorcentaje(d.getPorcentaje() + incremento);
                    };

                DescuentoPromocion::aplicarCambio(descuentos, 5, estaVigente, aplicarIncremento);

                cout << "\n=== DESCUENTOS ACTUALIZADOS ===\n";
                for (int i = 0; i < 5; i++) {
                    descuentos[i].mostrar();
                }
                break;
            }
            case 0:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }

            if (opcion != 0) {
                pausar();
            }
        } while (opcion != 0);
    }

    void menuResenas() {
        int opcion;
        do {
            cout << "\n==== MENU DE RESE"<<char(165)<<"AS DE EVENTOS ====\n";
            cout << "1. Mostrar todas las rese"<<char(164)<<"as\n";
            cout << "2. Filtrar rese"<<char(164)<<"as por calificacion minima\n";
            cout << "3. Calcular promedio de calificaciones\n";
            cout << "4. Mejorar comentarios negativos\n";
            cout << "0. Volver al menu anterior\n";
            cout << "Seleccione una opcion ";
            cin >> opcion;

            switch (opcion) {
            case 1: {
                cout << "\n=== TODAS LAS RESE"<<char(165)<<"AS ===\n";
                for (int i = 0; i < 4; i++) {
                    resenas[i].mostrar();
                }
                break;
            }
            case 2: {
                int minima;
                cout << "Ingrese la calificación minima (1-5): ";
                cin >> minima;

                cout << "\n=== RESE"<<char(165)<<"AS CON CALIFICACION >= " << minima << " ===\n";
                // LAMBDA
                auto calificacionMinima = [minima](const ReseñaEvento& r) {
                    return r.getCalificacion() >= minima;
                    };

                ReseñaEvento::filtrarReseñas(resenas, 4, calificacionMinima);
                break;
            }
            case 3: {
                cout << "\n=== PROMEDIO DE CALIFICACIONES ===\n";

                // LAMBDA
                auto extraerCalificacion = [](const ReseñaEvento& r) {
                    return static_cast<float>(r.getCalificacion());
                    };

                // LAMBDA
                auto sumar = [](float acum, float valor) {
                    return acum + valor;
                    };

                float suma = ReseñaEvento::calcularEstadistica(resenas, 4, extraerCalificacion, sumar);
                float promedio = suma / 4;

                cout << "Calificacion promedio: " << promedio << "/5\n";
                [promedio]() {
                    if (promedio >= 4.5) {
                        cout << "Excelente nivel de satisfaccion!\n";
                    }
                    else if (promedio >= 3.5) {
                        cout << "Buen nivel de satisfaccion.\n";
                    }
                    else if (promedio >= 2.5) {
                        cout << "Nivel de satisfaccion regular.\n";
                    }
                    else {
                        cout << "Atencion, Bajo nivel de satisfaccion.\n";
                    }
                    }();

                break;
            }
            case 4: {
                cout << "\n=== MEJORANDO COMENTARIOS NEGATIVOS ===\n";

                // LAMBDA
                auto esCalificacionBaja = [](const ReseñaEvento& r) {
                    return r.getCalificacion() <= 2;
                    };

                // LAMBDA
                auto mejorarComentario = [](ReseñaEvento& r) {
                    string comentarioActual = r.getComentario();
                    r.setComentario(comentarioActual + " [Se ha tomado nota para mejorar]");
                    };

                ReseñaEvento::buscarYModificar(resenas, 4, esCalificacionBaja, mejorarComentario);

                cout << "Comentarios actualizados para rese"<<char(164)<<"as con baja calificacion:\n";
                for (int i = 0; i < 4; i++) {
                    if (resenas[i].getCalificacion() <= 2) {
                        resenas[i].mostrar();
                    }
                }
                break;
            }
            case 0:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }

            if (opcion != 0) {
                pausar();
            }
        } while (opcion != 0);
    }

    void menuAdministradores() {
        int opcion;
        do {
            cout << "\n==== MENU DE ADMINISTRADORES ====\n";
            cout << "1. Mostrar todos los administradores\n";
            cout << "2. Validar acceso de administrador\n";
            cout << "3. Cambiar clave de administrador\n";
            cout << "4. Filtrar administradores por termino de busqueda\n";
            cout << "0. Volver al menu anterior\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1: {
                cout << "\n=== LISTA DE ADMINISTRADORES ===\n";
                for (int i = 0; i < 3; i++) {
                    admins[i].mostrarInformacion();
                    cout << "-------------------------\n";
                }
                break;
            }
            case 2: {
                int id;
                string clave;
                cout << "Ingrese ID del administrador (1-3): ";
                cin >> id;

                if (id < 1 || id > 3) {
                    cout << "ID invalido.\n";
                    break;
                }

                cout << "Ingrese la clave: ";
                cin >> clave;

                // LAMBDA
                auto manejarResultado = [&id](bool exitoso) {
                    cout << "Intento de acceso " << (exitoso ? "EXITOSO" : "FALLIDO") << endl;
                    if (exitoso) {
                        cout << "Se ha registrado el acceso exitoso en el sistema.\n";
                    }
                    else {
                        cout << "Se registrara este intento fallido por seguridad.\n";
                    }
                    };

                admins[id - 1].intentarAcceso(clave, manejarResultado);
                break;
            }
            case 3: {
                int id;
                string claveActual, nuevaClave;

                cout << "Ingrese ID del administrador (1-3): ";
                cin >> id;

                if (id < 1 || id > 3) {
                    cout << "ID invalido.\n";
                    break;
                }

                cout << "Ingrese clave actual: ";
                cin >> claveActual;

                cout << "Ingrese nueva clave: ";
                cin >> nuevaClave;

                // LAMBDA
                auto validarClave = [](const string& clave) -> bool {
                    if (clave.length() < 6) return false;

                    bool tieneNumero = false;
                    for (char c : clave) {
                        if (isdigit(c)) {
                            tieneNumero = true;
                            break;
                        }
                    }

                    return tieneNumero;
                    };

                bool resultado = admins[id - 1].cambiarClaveCondicional(
                    claveActual, nuevaClave, validarClave
                );

                if (resultado) {
                    cout << "Clave actualizada exitosamente.\n";
                }
                else {
                    cout << "No se pudo actualizar la clave. Verifique la clave actual "
                        << "y que la nueva tenga al menos 6 caracteres y un numero.\n";
                }
                break;
            }
            case 4: {
                string termino;
                cout << "Ingrese termino de busqueda (nombre o email): ";
                cin.ignore();
                getline(cin, termino);

                cout << "\nResultados de busqueda para '" << termino << "':\n";

                // LAMBDA
                auto contieneTérmino = [termino](const Administrador& admin) -> bool {
                    string nombreCompleto = admin.getNombre() + " " + admin.getApellido();
                    string email = admin.getEmail();
                    string terminoLower = termino;
                    string nombreLower = nombreCompleto;
                    string emailLower = email;
                    for (auto& c : terminoLower) c = tolower(c);
                    for (auto& c : nombreLower) c = tolower(c);
                    for (auto& c : emailLower) c = tolower(c);

                    return nombreLower.find(terminoLower) != string::npos ||
                        emailLower.find(terminoLower) != string::npos;
                    };

                // LAMBDA
                auto mostrarAdmin = [](const Administrador& admin) {
                    admin.mostrarInformacion();
                    cout << "-------------------------\n";
                    };
                Administrador::filtrarAdministradores(admins, 3, contieneTérmino, mostrarAdmin);
                break;
            }
            case 0:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }

            if (opcion != 0) {
                pausar();
            }
        } while (opcion != 0);
    }

public:
    void ejecutar() {
        int opcion;
        do {
            cout << "\n==== MODULO DE FUNCIONES SERVICIOS Y ADMINISTRACION ====\n";
            cout << "1. Gestion de Descuentos y Promociones\n";
            cout << "2. Analisis de Rese"<<char(164)<<"as de Eventos\n";
            cout << "3. Administracion de Usuarios\n";
            cout << "0. Volver al menu principal\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                menuDescuentos();
                system("cls");
                break;
            case 2:
                menuResenas();
                system("cls");

                break;
            case 3:
                menuAdministradores();
                system("cls");

                break;
            case 0:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                pausar();
            }
        } while (opcion != 0);
    }
};
