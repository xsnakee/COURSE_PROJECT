#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
/*
 * STRUCTURES AND TYPES
 */
struct tableData{
    char fio[30];
    int num;
    int tokenNum;
};

struct list {
    tableData inf;
    struct list *next, *pred;
}*listTop=NULL,*listEnd=NULL,*listCurrent=NULL, *listTemp=NULL;;


/*
 * FUNCTIONS PROTOTYPES
 */
void gotoxy(short x, short y);
void SetColor(int text, int background);
void readTheKey();
tableData newRecord();
list *organizeList(list &Top,list &End);

/*int drawInterface(char *Items);
int drawInterface(table *Items);
//*/



/*
 * MAIN FUNCTION
 */
int main() {
    cout << "Hello, World!" << std::endl;
    getchar();
    return 0;
}

/*
 * FUNCTION IMPLEMENTATION
 */

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

/*
 * Функция проверки кода клавиш
 */
void readTheKey(){
    while (int key=getch()) {
        cout << key << endl;

        if (key == 13) {
            cout<<"Will exit";
            return;
        }
    }
}

/*
 * Функция создания записи
 */
tableData newRecord(){
    tableData newElement;
    cin>>newElement.fio;
    cin>>newElement.tokenNum;
    (!newElement.num) ? newElement.num = 0 : newElement.num++;
    return newElement;
}

/*list *organizeList(list &Top,list &End){

}*/
