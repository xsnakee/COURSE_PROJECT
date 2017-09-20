#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;
/*
 * STRUCTURES AND TYPES
 */
const int mainMenuItemsCount = 12;
const char *mainMenu[mainMenuItemsCount] = {
        "ADD USER DATA",
        "VIEW & NAVIGATE",
        "ORGANIZE LIST",
        "VIEW LIST",
        "GET_KEY",
        "EDIT USER DATA",
        "SORT LIST",
        "SAVE IN FILE",
        "LOAD FROM FILE",
        "SEARCH USER",
        "SEARCH GROUP",
        "EXIT"
};


const int acceptMessageItemsCount = 2;
const char *acceptMessage[acceptMessageItemsCount] = {
        "DECLINE",
        "ACCEPT"
};
int GLOBAL_COUNTER = 0;
struct tableData {
    char fio[30];
    int num;
    int tokenNum;
};

struct list {
    tableData inf;
    struct list *next, *pred;
} *listHead = NULL;


/*
 * FUNCTIONS PROTOTYPES
 */
void gotoxy(short x, short y);

void SetColor(int text, int background);

void readTheKey();

tableData newRecord();

list *organizeList(list *top);

list *addPerson(list *top);

int check(list *top);

int deleteList(list *top);

void view(list *top);

void viewList(list *top);

int menu(const char **menuItems, const int itemsCount);

/*int drawInterface(char *Items);
int drawInterface(table *Items);
//*/



/*
 * MAIN FUNCTION
 */
int main() {
    cout << "Hello, World!" << std::endl;
    while (1) {
        switch (menu(mainMenu, mainMenuItemsCount)) {
            case 2: {
                listHead = organizeList(listHead);
                cout << "0";
                getch();
                break;
            }
            case 1: {
                viewList(listHead);
                cout << "1";
                getch();
                break;
            }
            case 0: {
                listHead = addPerson(listHead);
                cout << "2";
                getch();
                break;
            }
            case 3: {
                view(listHead);
                cout << "3";
                getch();
                break;
            }
            case 4: {
                cout << "4";
                readTheKey();
                getch();
                break;
            }
            case 5: {
                cout << "5";
                getch();
                break;
            }
            case 6: {
                cout << "6";
                getch();
                break;
            }
            case 7: {
                cout << "7";
                getch();
                break;
            }
            case 8: {
                cout << "8";
                getch();
                break;
            }
            case 9: {
                cout << "9";
                getch();
                break;
            }
            case 10: {
                cout << "10";
                getch();
                break;
            }
            case 11: {
                cout << "11";
                getch();
                deleteList(listHead);
                exit(0);
            }
        }
    }
    getchar();
    return 0;
}

/*
 * FUNCTION IMPLEMENTATION
 */

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
    while (int key = getch()) {
        cout << key << endl;
        if (key == 13) {
            cout << "Will exit";
            return;
        }
    }
}

/*
 * Функция создания записи
 */
tableData newRecord() {
    tableData newElement;
    cout << "FIO: ";
    cin >> newElement.fio;
    cout << "TOKEN: ";
    cin >> newElement.tokenNum;
    newElement.num = GLOBAL_COUNTER++;
    //(!newElement.num) ? newElement.num = 0 : newElement.num++;
    return newElement;
}

/*
 * Организация списка
 */
list *organizeList(list *top) {
    if (top == NULL) {
        tableData personalData = newRecord();
        struct list *newAdress = new list;
        newAdress->inf = personalData;
        newAdress->next = NULL;
        newAdress->pred = NULL;
        top = newAdress;
    }

    return top;
}

int deleteList(list *top) {

    if (!check(top)) {
        list *temp;

        int i = 0;
        for (temp = top; top != NULL; temp = top) {
            top = temp->next;
            delete temp;
            cout << "deleted" << i++ << endl;
        }
        getch();
        if (top == NULL && temp == NULL) return 1;
        else return 0;
    }

}

/*
 * Добавление записи в список
 */
list *addPerson(list *top) {
    if (!check(top)) {
        list *temp;
        for (temp = top; temp->next != NULL; temp = temp->next) {}
        tableData personalData = newRecord();
        list *New = new list;
        New->inf = personalData;
        New->next = NULL;
        New->pred = temp;
        temp->next = New;
    }
    return top;
}

int check(list *top) {
    if (top == NULL) {
        cout << "Empty list!";
        return 1;
    }
    return 0;
}

void view(list *top) {
    if (!check(top)) {
        list *temp;
        system("cls");
        for (temp = top; temp != NULL; temp = temp->next) {
            cout << temp->inf.num << " " << temp->inf.tokenNum << " " << temp->inf.fio << endl;
        }
    }
    return;
}

void viewList(list *top) {

    while (1) {
        if (!check(top)) {
            list *currentL = top, *temp, *startDisplay = top;
            int countOfDisplayRecords = 10, i, currentNum = 0, key;

            while (1) {

                system("cls");
                cout << "TABLE HEAD" << endl << endl << endl;
                for (i = 0, temp = startDisplay; (i < countOfDisplayRecords) && (temp != NULL); temp = temp->next) {
                    if (i++ == currentNum) {
                        SetColor(0, 8);
                    }
                    cout << temp->inf.num << " " << temp->inf.tokenNum << " " << temp->inf.fio << endl;
                    SetColor(7, 0);
                }

                switch (key = getch()) {
                    case 72: {
                        if (currentL->inf.num != top->inf.num) {
                            currentNum--;
                            currentL = currentL->pred;
                        }
                        break;
                    }

                    case 80: {
                        if (currentL->next != NULL) {
                            currentNum++;
                            currentL = currentL->next;
                        }
                        break;
                    }

                    case 13: {
                        //edit(currentL, currentNum+3);
                        break;
                    }

                    case 27: {
                        return;
                    }
                }
                if (currentNum < 0) {
                    currentNum = countOfDisplayRecords - 1;
                    for (i = 0, temp = currentL;
                         (i < countOfDisplayRecords) && (temp->pred != NULL); i++, temp = temp->pred);
                    startDisplay = temp;
                } else if (currentNum > countOfDisplayRecords - 1 && currentL != NULL) {
                    currentNum = 0;
                    startDisplay = currentL;
                }
            }
        } else return;
    }

}

int menu(const char **menuItems, const int itemsCount) {
    int currentItem = 0, i = 0, key;
    while (1) {
        system("cls");
        for (i = 0; i < itemsCount; i++) {

            if (i == currentItem) {
                SetColor(0, 8);
            }
            cout << menuItems[i] << endl;
            SetColor(7, 0);
        }

        switch (key = getch()) {
            case 13: {
                return currentItem;
            }
            case 80: {
                if (currentItem >= itemsCount - 1) currentItem = 0;
                else currentItem++;
                break;
            }
            case 72: {
                if (currentItem <= 0) currentItem = itemsCount - 1;
                else currentItem--;
                break;
            }
            case 27: {
                exit(0);
            }
        }
    }
}
