//
// Created by ������� on 19.11.2017.
//

#include "CP_types.h"

/*�㭪�� ����樮��஢���� ����� � ���᮫�*/
void gotoxy(short x, short y) {
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

/*�㭪�� �롮� 梥� ⥪�� � 䮭� � ���᮫�*/
void SetColor(int text, int background) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD) ((background << 4) | text));
}

/*
 * �㭪�� �஢�ન ���� ������
 */
void readTheKey() {
    char key2;
    while (int key = getch()) {
        key2 = key;
        cout << key << " = " << key2 << endl;
        if (key == 13) {
            printf("�����");
            return;
        }
    }
}