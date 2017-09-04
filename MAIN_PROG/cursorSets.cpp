//
// Created by Николай on 04.09.2017.
//

#include <windows.h>

/*Функция позиционирования курсора в консоли*/
void gotoxy(short x, short y){
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}
/*Функция выбора цвета текста и фона в консоли*/
void SetColor(int text, int background){
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}