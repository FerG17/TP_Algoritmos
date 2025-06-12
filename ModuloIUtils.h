#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Interfaz.h"
#include <conio.h>
using namespace std;

void limpiarYCentrarPantalla() {
    system("cls");
    dibujarSoloBordes(); 
}

void mostrarTituloModulo(const string& titulo) {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);
    gotoxy((anchoConsola - titulo.length()) / 2, 6);
    setColor(AZUL_CLARO, COLOR_FONDO);
    cout << titulo;
    setColor(COLOR_TEXTO, COLOR_FONDO);  
}

void mostrarOpcionMenu(const string& opcion, int lineaY) {
    gotoxy(45, lineaY);
    cout << opcion;
}

void pausarContinuar() {
    int anchoConsola, altoConsola;
    getConsoleSize(anchoConsola, altoConsola);
    gotoxy((anchoConsola - 40) / 2, 22);  
    setColor(MAGENTA, COLOR_FONDO);
    cout << "Presione cualquier tecla para continuar...";
    setColor(COLOR_TEXTO, COLOR_FONDO);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    getch();  
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    limpiarYCentrarPantalla();
}
