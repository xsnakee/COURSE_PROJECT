#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
int readTheKey();
void gotoxy(short x, short y);
void SetColor(int text, int background);

int main() {
    std::cout << "Hello, World!" << std::endl;
    readTheKey();

    getchar();
    return 0;
}


int readTheKey(){
    while (int key=getch()) {
        cout << key << endl;
        if (key == 13) {
            cout<<"Will exit";
            return 1;
        }
    }
}

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