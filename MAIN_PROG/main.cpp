#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
/*
 * STRUCTURES AND TYPES
 */

char *menu[]={
        "ORGANIZE LIST",
        "VIEW LIST",
        "ADD USER DATA",
        "DELETE USER DATA",
        "EDIT USER DATA",
        "SORT LIST",
        "SAVE IN FILE",
        "LOAD FROM FILE",
        "SEARCH GROUP",
        "EXIT"
};

char *acceptMessage[] = {
        "ACCEPT",
        "DECLINE"
};
struct tableData{
    char fio[30];
    int num;
    int tokenNum;
};

struct list {
    tableData inf;
    struct list *next, *pred;
}*listTop = NULL,*listEnd = NULL,*listCurrent = NULL;


/*
 * FUNCTIONS PROTOTYPES
 */
void gotoxy(short x, short y);
void SetColor(int text, int background);
void readTheKey();
tableData newRecord();
list *organizeList(list *top);
list *addPerson(list *end);

/*int drawInterface(char *Items);
int drawInterface(table *Items);
//*/



/*
 * MAIN FUNCTION
 */
int main() {
    cout << "Hello, World!" << std::endl;
    for(int i = 0; menu[i]; i++){
        cout << menu[i]<<endl;
    }
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
    cin >> newElement.fio;
    cin >> newElement.tokenNum;
    (!newElement.num) ? newElement.num = 0 : newElement.num++;
    return newElement;
}

list *organizeList(list *top){
    tableData personalData = newRecord();
    struct list *newAdress = new list;
    newAdress -> inf = personalData;
    newAdress -> next = NULL;
    newAdress -> pred = NULL;
    top = newAdress;
    return top;
}

list *addPerson(list *end){
    tableData personalData = newRecord();
    list *temp = new list;
    temp -> inf = personalData;
    temp -> next = NULL;
    temp -> pred = end;
    end=temp;
    return end;
}

void viewList(list *top){
    list *current;
    int countOfDisplayRecords;
    tableData *displayedList[countOfDisplayRecords];
    for(list *temp = top;temp -> next != NULL; temp = temp -> next){
        for(int i = 0; i < countOfDisplayRecords; i++) {
            displayedList[i] = temp -> inf;
            temp = temp -> next;
        }
    }
}
