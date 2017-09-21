#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <math.h>

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
        "CHECK NUMERAL",
        "EXIT"
};


const int acceptMessageItemsCount = 2;
const char *acceptMessage[acceptMessageItemsCount] = {
        "DECLINE",
        "ACCEPT"
};
int GLOBAL_COUNTER_ID = 0;
const int FIO_LENGTH = 20;
const int PROF_LENGTH = 10;
struct tableData {
    int ID;
    long int tableNumber;
    char fio[FIO_LENGTH];
    int birth_year;
    bool sex;
    char prof[PROF_LENGTH];
    int exp;
    int rang;
    int roomNumber;
    int bigRoomNumber;
    int placeNumber;
    float salary;
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

int deletePersonalData(list *&current);

void view(list *top);

void viewList(list *&top);

int menu(const char **menuItems, const int itemsCount);

long int checkNumeral(short X = 0, short Y = 0, long int num = 0, int maxDigitCount = 4);

char *strToFormat(char *str, const int length);

void helpMenu();

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

    system("cls");
    short coordY = 0, coordX = 0;

    tableData newElement;

    cout << "FIO: ";
    char fio[FIO_LENGTH];
    cin.getline(fio, FIO_LENGTH);
    strcpy(newElement.fio, strToFormat(fio, FIO_LENGTH));
    coordY++;

    newElement.ID = GLOBAL_COUNTER_ID++;

    cout << "TABLE: ";
    coordX = 7;
    newElement.tableNumber = checkNumeral(coordX, coordY, 0, 6);
    coordY++;


    cout << "BIRTH YEAR: ";
    coordX = 12;
    newElement.birth_year = checkNumeral(coordX, coordY);
    coordY++;


    cout << "SEX(0-male,1-female): ";
    coordX = 24;
    newElement.sex = checkNumeral(coordX, coordY, 0, 1);
    coordY++;


    cout << "PROF: ";
    char prof[PROF_LENGTH];
    cin.getline(prof, PROF_LENGTH);
    strcpy(newElement.prof, strToFormat(prof, PROF_LENGTH));
    coordY++;


    cout << "EXPERIENCE: ";
    coordX = 12;
    newElement.exp = checkNumeral(coordX, coordY, 0, 2);
    coordY++;

    cout << "RANG: ";
    coordX = 6;
    newElement.rang = checkNumeral(coordX, coordY, 0, 2);
    coordY++;

    cout << "ROOM: ";
    coordX = 6;
    newElement.roomNumber = checkNumeral(coordX, coordY, 0, 2);
    coordY++;

    cout << "LARGE ROOM: ";
    coordX = 12;
    newElement.bigRoomNumber = checkNumeral(coordX, coordY, 0, 2);
    coordY++;

    cout << "PLACE: ";
    coordX = 7;
    newElement.placeNumber = checkNumeral(coordX, coordY, 0, 2);
    coordY++;

    cout << "SALARY: ";
    coordX = 8;
    newElement.salary = (float)checkNumeral(coordX, coordY, 0, 8);

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

int deletePersonalData(list *&top, list *&current){

    if (!check(current)){
       if ( (current->pred == NULL) && (current->next == NULL) ){
           delete current;
           top = current = NULL;
           return 0;
       } else if (current->pred == NULL){
           list *temp = current;
           current = current->next;
           current->pred = NULL;
           top = current;
           delete temp;
           return 0;
       } else {
           list *temp = current;
           temp->pred->next = current->next;
           current = temp->pred;
           delete temp;
           return 0;
       }
    }
    return 1;
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
        return 1;
    }
    return 0;
}

void view(list *top) {
    if (!check(top)) {
        list *temp;
        system("cls");
        for (temp = top; temp != NULL; temp = temp->next) {
            cout << temp->inf.ID << " " << temp->inf.fio << " " << temp->inf.tableNumber << " " << temp->inf.birth_year
                 << " " << temp->inf.sex << " " << temp->inf.prof << " " << temp->inf.salary << endl;
        }
    }
    return;
}

void viewList(list *&top) {

    while (1) {
        if (!check(top)) {
            list *currentL = top, *temp, *startDisplay = top;
            int countOfDisplayRecords = 10, i, currentNum = 0, key;

            while (!check(top)) {

                system("cls");
                cout << "TABLE HEAD" << endl << endl << endl;
                for (i = 0, temp = startDisplay; (i < countOfDisplayRecords) && (temp != NULL); temp = temp->next) {
                    if (i++ == currentNum) {
                        SetColor(0, 8);
                    }
                    cout << temp->inf.ID << " " << temp->inf.fio << " " << temp->inf.tableNumber << endl;
                    SetColor(7, 0);
                }
                helpMenu();

                switch (key = getch()) {
                    case 72: {
                        if (currentL->inf.ID != top->inf.ID) {
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
                    case 83:{
                        deletePersonalData(top,currentL);
                        currentNum--;
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
                if (currentNum < 0 && currentL != NULL) {
                    currentNum = countOfDisplayRecords - 1;

                    for (i = 0, temp = currentL;
                         (i < countOfDisplayRecords) && (temp->pred != NULL); i++, temp = temp->pred);
                    startDisplay = temp;
                } else if (currentNum > countOfDisplayRecords - 1 && currentL != NULL) {
                    currentNum = 0;
                    startDisplay = currentL;
                }
            }
            cout << "EMPTY" << endl;
        } else return;
    }

}

void helpMenu(){
    SetColor(7,1);
    cout << endl << endl << "ESC - MENU | ENTER - EDIT | DEL - DELETE | UP,DOWN - NAVIGATE | <-,-> SLIDE PAGE";
    SetColor(7,0);
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


//*/
long int checkNumeral(short X, short Y, long int num, int maxDigitCount) {
    int key;
    long int tempNum = num;
    int currentDigitCount, minDigitCount = 0;

    for (currentDigitCount = 0; tempNum >= 1; currentDigitCount++) {
        tempNum = tempNum / 10;
    }

    tempNum = num;

    while (1) {
        switch (key = getch()) {

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                if (currentDigitCount < maxDigitCount) {
                    tempNum = tempNum * 10 + (key - '0');
                    currentDigitCount++;
                }
                break;
            }

            case 8: {
                if (currentDigitCount > minDigitCount) {
                    tempNum = tempNum / 10;
                    currentDigitCount--;
                }
                break;
            }

            case 13: {
                return num = tempNum;
            }

            case 27: {
                return num;
            }
        }

        gotoxy(X, Y);
        cout << "                   ";
        gotoxy(X, Y);
        cout << tempNum << endl;
    }
}

//*/



/*
 * ПРИВЕДЕНИЕ СИМВОЛОВ ФАМИЛИИ И ИНИЦИАЛОВ К ВЕРХНЕМУ РЕГИСТРУ
 */
char *strToFormat(char *str, const int length) {
    int i;


    for (i = 0; i < length; i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //если i-тый элемент пробел или знак - пропуск

            continue;
        } else {
            str[i] = toupper(str[i]);
        }
    }
    //ДЛЯ ПРИВЕДЕНИЯ СИМВОЛОВ К НИЖНЕМУ РЕЕСТРУ

    /*bool spaceCheck = true;

    for (i = 0; i < length; i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //если i-тый элемент пробел или знак - пропуск
            spaceCheck = true;
            continue;
        } else if (spaceCheck) {
            spaceCheck = false;
            str[i] = toupper(str[i]);
        } else {
            str[i] = tolower(str[i]);
        }
    }*/
    return str;
}
