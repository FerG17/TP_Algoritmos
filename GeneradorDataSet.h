#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <set>
#include <sstream>
#include <iomanip>
#include <limits>
#include "Cliente.h"
#include "Compra.h"
#include "Entrada.h"
#include "Hash.h"

using namespace std;

static vector<string> nombres = { "Juan", "Ana", "Pedro", "Lucia", "Carlos", "Maria", "Luis", "Sofia", "Diego", "Elena" };
static vector<string> apellidos = { "Perez", "Gomez", "Rodriguez", "Lopez", "Fernandez", "Garcia", "Martinez", "Diaz", "Sanchez", "Morales" };
static vector<string> emails = { "@gmail.com", "@hotmail.com", "@yahoo.com", "@outlook.com" };
static vector<string> calles = { "Av. Siempre Viva", "Calle Falsa", "Jr. Los Olivos", "Av. Principal", "Calle Luna", "Calle Sol" };
static vector<string> ciudades = { "Lima", "Cusco", "Trujillo", "Arequipa", "Piura" };
static vector<string> metodosPago = { "Tarjeta", "Efectivo", "Yape", "Plin" };

class GeneradorDataSet {
public:
    GeneradorDataSet(int hashTableSize = 128) : hashTablaClientes(hashTableSize) {}

    ~GeneradorDataSet() {
        limpiarMemoria();
    }

    // Genera y almacena clientes y compras aleatorias; los guarda también en archivos .txt
    void generarDatasetClientes(int cantidadClientes, const string& archivoClientes, const string& archivoCompras) {
        limpiarMemoria();
        hashTablaClientes = HashTabla(hashTablaClientes.size()); // reset hash table

        ofstream outClientes(archivoClientes);
        ofstream outCompras(archivoCompras);
        if (!outClientes || !outCompras) {
            cerr << "No se pudieron abrir los archivos de salida.\n";
            return;
        }

        mt19937 gen(static_cast<unsigned int>(time(0)));
        set<int> dnisUsados;
        vector<Compra*> comprasTemp;

        for (int i = 0; i < cantidadClientes; ++i) {
            Cliente* c = generarClienteAleatorio(gen, dnisUsados, comprasTemp);
            clientesGenerados.push_back(c);
            hashTablaClientes.insertar(c->getId(), i); // Relacionar DNI con índice
            c->guardarEnArchivo(outClientes);
        }
        // Copiar las compras a la variable global de la clase
        for (Compra* compra : comprasTemp)
            comprasGeneradas.push_back(compra);

        for (const Compra* compra : comprasGeneradas) {
            outCompras << compra->getId() << "," << compra->getClienteId() << "," << compra->getFechaCompra() << "," << compra->getSubtotal()
                << "," << compra->getDescuentoAplicado() << "," << compra->getTotal() << "," << compra->getMetodoPago() << "," << static_cast<int>(compra->getEstado()) << endl;
        }
        outClientes.close();
        outCompras.close();
    }

    // Acceso a los datos generados en memoria
    const vector<Cliente*>& getClientesGenerados() const { return clientesGenerados; }
    const vector<Compra*>& getComprasGeneradas() const { return comprasGeneradas; }
    const HashTabla& getHashTablaClientes() const { return hashTablaClientes; }

private:
    vector<Cliente*> clientesGenerados;
    vector<Compra*> comprasGeneradas;
    HashTabla hashTablaClientes;

    void limpiarMemoria() {
        for (Cliente* c : clientesGenerados) delete c;
        clientesGenerados.clear();
        for (Compra* comp : comprasGeneradas) delete comp;
        comprasGeneradas.clear();
    }

    string randomTelefono(mt19937& gen) {
        uniform_int_distribution<> dis(0, 99999999);
        int resto = dis(gen);
        ostringstream oss;
        oss << "9" << setw(8) << setfill('0') << resto;
        return oss.str();
    }

    string randomDireccion(mt19937& gen) {
        uniform_int_distribution<> disCalle(0, calles.size() - 1);
        uniform_int_distribution<> disNum(1, 999);
        uniform_int_distribution<> disCiudad(0, ciudades.size() - 1);
        return calles[disCalle(gen)] + " " + to_string(disNum(gen)) + ", " + ciudades[disCiudad(gen)];
    }

    string randomNombre(mt19937& gen) {
        uniform_int_distribution<> dis(0, nombres.size() - 1);
        return nombres[dis(gen)];
    }

    string randomApellido(mt19937& gen) {
        uniform_int_distribution<> dis(0, apellidos.size() - 1);
        return apellidos[dis(gen)];
    }

    string randomEmail(const string& nombre, const string& apellido, mt19937& gen) {
        uniform_int_distribution<> dis(0, emails.size() - 1);
        return nombre + "." + apellido + emails[dis(gen)];
    }

    string randomMetodoPago(mt19937& gen) {
        uniform_int_distribution<> dis(0, metodosPago.size() - 1);
        return metodosPago[dis(gen)];
    }

    EstadoCompra randomEstado(mt19937& gen) {
        uniform_int_distribution<> dis(0, 3);
        return static_cast<EstadoCompra>(dis(gen));
    }

    double randomPrecio(mt19937& gen) {
        uniform_real_distribution<> dis(10.0, 200.0);
        return dis(gen);
    }

    Entrada generarEntradaAleatoria(mt19937& gen) {
        int eventoId = uniform_int_distribution<>(1, 20)(gen);
        int asientoId = uniform_int_distribution<>(1, 300)(gen);
        double precio = randomPrecio(gen);
        return Entrada(eventoId, asientoId, precio);
    }

    Compra* generarCompraAleatoria(int clienteId, mt19937& gen) {
        string metodoPago = randomMetodoPago(gen);
        Compra* compra = new Compra(clienteId, metodoPago);
        int numEntradas = uniform_int_distribution<>(1, 5)(gen);
        for (int i = 0; i < numEntradas; ++i) {
            Entrada e = generarEntradaAleatoria(gen);
            compra->agregarEntrada(e);
        }
        compra->aplicarDescuento(uniform_int_distribution<>(0, 20)(gen));
        if (numEntradas > 2) compra->finalizarCompra();

        return compra;
    }

    int randomDni(mt19937& gen, set<int>& usados) {
        int dni;
        uniform_int_distribution<> dis(10000000, 99999999);
        do {
            dni = dis(gen);
        } while (usados.count(dni) > 0);
        usados.insert(dni);
        return dni;
    }

    Cliente* generarClienteAleatorio(mt19937& gen, set<int>& dnisUsados, vector<Compra*>& comprasGeneradasLocal) {
        int dni = randomDni(gen, dnisUsados);
        string nombre = randomNombre(gen);
        string apellido = randomApellido(gen);
        string email = randomEmail(nombre, apellido, gen);
        string telefono = randomTelefono(gen);
        string direccion = randomDireccion(gen);

        Cliente* cliente = new Cliente(dni, nombre, apellido, email, telefono, direccion);
        cliente->setPuntosLealtad(uniform_int_distribution<>(0, 500)(gen));
        int numCompras = uniform_int_distribution<>(2, 4)(gen); 
        for (int i = 0; i < numCompras; ++i) {
            Compra* compra = generarCompraAleatoria(cliente->getId(), gen);
            comprasGeneradasLocal.push_back(compra);
            cliente->agregarCompraAlHistorial(compra->getId());
        }
        return cliente;
    }
};
