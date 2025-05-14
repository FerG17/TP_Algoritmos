#include "pch.h"
#include "MenuPrincipal.h"
#include <iostream>
#include <windows.h>
int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 100, 50 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SMALL_RECT windowSize = { 0, 0, 99, 49 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    MenuPrincipal menu;
    menu.iniciar();
    return 0;
}
