#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;
const int FILAS_LOGO = 25;
const int COLUMNAS_LOGO = 50;

const int ANCHO_CONSOLA = 150;
const int ALTO_CONSOLA = 60;

enum Color {
    NEGRO = 0,
    AZUL = 1,
    VERDE = 2,
    CIAN = 3,
    ROJO = 4,
    MAGENTA = 5,
    MARRON = 6,
    GRIS_CLARO = 7,
    GRIS_OSCURO = 8,
    AZUL_CLARO = 9,
    VERDE_CLARO = 10,
    CIAN_CLARO = 11,
    ROJO_CLARO = 12,
    MAGENTA_CLARO = 13,
    AMARILLO = 14,
    BLANCO = 15
};

const int COLOR_FONDO = GRIS_CLARO;
const int COLOR_LOGO = AZUL_CLARO;
const int COLOR_TITULO = AZUL;
const int COLOR_TEXTO = NEGRO;
const int COLOR_MENSAJE = AZUL_CLARO;

int logoTicketek[FILAS_LOGO][COLUMNAS_LOGO] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,0,1,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

};

void gotoxy(int x, int y) {
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void setColor(int colorTexto, int colorFondo = COLOR_FONDO) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorTexto | (colorFondo << 4));
}

void getConsoleSize(int& ancho, int& alto) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        ancho = 50;
        alto = 25;
    }
}

void configurarConsola() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { ANCHO_CONSOLA, ALTO_CONSOLA };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, ANCHO_CONSOLA - 1, ALTO_CONSOLA - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    SetConsoleTitle(L"Sistema Ticketec");
}
void pintarFondo() {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);

    setColor(COLOR_TEXTO, COLOR_FONDO);
    for (int y = 0; y < altoConsola; y++) {
        for (int x = 0; x < anchoConsola; x++) {
            gotoxy(x, y);
            cout << " ";
        }
    }
}

void dibujarLogo(int posX, int posY) {
    for (int i = 0; i < FILAS_LOGO; i++) {
        for (int j = 0; j < COLUMNAS_LOGO; j++) {
            if (logoTicketek[i][j] == 1) {
                gotoxy(posX + j, posY + i);
                setColor(COLOR_LOGO, COLOR_FONDO);
                cout << char(219);
            }
        }
    }
}

void dibujarBordeTicketek() {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);
    pintarFondo();
    dibujarLogo(50, 10);
    setColor(COLOR_TITULO, COLOR_FONDO);

    for (int x = COLUMNAS_LOGO; x < anchoConsola - COLUMNAS_LOGO; x++) {
        gotoxy(x, 2);
        cout << char(205);
        gotoxy(x, altoConsola - 3);
        cout << char(205);
    }

    for (int y = FILAS_LOGO; y < altoConsola - FILAS_LOGO; y++) {
        gotoxy(2, y);
        cout << char(186);
        gotoxy(anchoConsola - 3, y);
        cout << char(186);
    }

    gotoxy(2, 2);
    cout << char(201);
    gotoxy(anchoConsola - 3, 2);
    cout << char(187);
    gotoxy(2, altoConsola - 3);
    cout << char(200);
    gotoxy(anchoConsola - 3, altoConsola - 3);
    cout << char(188);

 
    setColor(COLOR_TEXTO);
}
void dibujarSoloBordes() {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);

    pintarFondo();

    setColor(COLOR_TITULO, COLOR_FONDO);

    for (int x = 0; x < anchoConsola; x++) {
        gotoxy(x, 2);
        cout << char(205);
        gotoxy(x, altoConsola - 3);
        cout << char(205);
    }

    for (int y = 3; y < altoConsola - 3; y++) {
        gotoxy(2, y);
        cout << char(186);
        gotoxy(anchoConsola - 3, y);
        cout << char(186);
    }

    gotoxy(2, 2);
    cout << char(201);
    gotoxy(anchoConsola - 3, 2);
    cout << char(187);
    gotoxy(2, altoConsola - 3);
    cout << char(200);
    gotoxy(anchoConsola - 3, altoConsola - 3);
    cout << char(188);

    setColor(COLOR_TEXTO);
}
void mostrarTextoCentrado(string texto, int desfaseY = 0) {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);

    int posX = (anchoConsola - texto.length()) / 2;
    int posY = altoConsola / 2 + desfaseY;

    gotoxy(posX, posY);
    cout << texto;
}

void mostrarCuadroMenu(int alto, int ancho, int posY) {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);

    int posX = (anchoConsola - ancho) / 2;

    setColor(COLOR_TITULO, COLOR_FONDO);

    gotoxy(posX, posY);
    cout << char(201);
    gotoxy(posX + ancho - 1, posY);
    cout << char(187);
    gotoxy(posX, posY + alto - 1);
    cout << char(200);
    gotoxy(posX + ancho - 1, posY + alto - 1);
    cout << char(188);

    for (int x = posX + 1; x < posX + ancho - 1; x++) {
        gotoxy(x, posY);
        cout << char(205);
        gotoxy(x, posY + alto - 1);
        cout << char(205);
    }

    for (int y = posY + 1; y < posY + alto - 1; y++) {
        gotoxy(posX, y);
        cout << char(186);
        gotoxy(posX + ancho - 1, y);
        cout << char(186);
    }

    setColor(COLOR_TEXTO);
}

void mostrarInterfaz() {
    configurarConsola();
    dibujarBordeTicketek();
}

void mostrarMenu() {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);

    int altoMenu = 10;
    int anchoMenu = 40;
    int posYMenu = (altoConsola - altoMenu) / 2 - 3;

    mostrarCuadroMenu(altoMenu, anchoMenu, posYMenu);

    setColor(AZUL_CLARO, COLOR_FONDO);
    mostrarTextoCentrado("=== SISTEMA TICKETEC ===", -5);

    setColor(COLOR_TEXTO, COLOR_FONDO);
    mostrarTextoCentrado("1. Modulo de Eventos", -3);
    mostrarTextoCentrado("2. Modulo de Usuarios y Compras", -2);
    mostrarTextoCentrado("3. Modulo de Servicios Administrativos", -1);
    mostrarTextoCentrado("0. Salir", 0);

    setColor(ROJO, COLOR_FONDO);
    mostrarTextoCentrado("Ingrese su opcion: ", 2);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int posX = (anchoConsola / 2) + 10;
    gotoxy(posX, altoConsola / 2 + 2);
    setColor(BLANCO, COLOR_FONDO);
}

void mostrarMensajeEstado(string mensaje) {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);
    setColor(COLOR_TEXTO, COLOR_FONDO);
    for (int i = 0; i < anchoConsola; i++) {
        gotoxy(i, altoConsola - FILAS_LOGO - 5);
        cout << " ";
    }
    setColor(COLOR_MENSAJE, COLOR_FONDO);
    mostrarTextoCentrado(mensaje, (altoConsola / 2) - (altoConsola - FILAS_LOGO - 5));
}
