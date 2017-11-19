//
// Created by Николай on 19.11.2017.
//

#include "CP_types.h"

/*Функция позиционирования курсора в консоли*/
void gotoxy(short x, short y) {
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

/*Функция выбора цвета текста и фона в консоли*/
void SetColor(int text, int background) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD) ((background << 4) | text));
}

/*
 * Функция проверки кода клавиш
 */
void readTheKey() {
    char key2;
    while (int key = getch()) {
        key2 = key;
        cout << key << " = " << key2 << endl;
        if (key == 13) {
            printf("КОНЕЦ");
            return;
        }
    }
}