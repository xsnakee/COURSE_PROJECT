#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

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

const int saveFileMessageItemsCount = 2;
const char *saveFileMessage[saveFileMessageItemsCount] = {
        "SAVE",
        "SAVE AS"
};

const int saveRequestItemsCount = 2;
const char *saveRequest[saveFileMessageItemsCount] = {
        "BINARY FILE(.bin)",
        "TEXT FILE(.txt)"
};

const int FIO_LENGTH = 20;
const int PROF_LENGTH = 10;
const int FILE_NAME_LENGTH = 256;
char openFileName[FILE_NAME_LENGTH];
const short int countOfDisplayRecords = 10;

int GLOBAL_COUNTER_ID = 0;
int key;
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

const int TABLE_DATA_SIZE = sizeof(tableData);

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

int saveFile(list *top, char *fileName, bool mode = 1);

int loadFile(list *&top, char *fileName);

list *organizeList(list *&top, tableData personalData);

list *addPerson(list *&top, tableData personalData);

int check(list *top);

int deleteList(list *top);

list *deletePersonalData(list *&current);

void view(list *top);

void viewList(list *&listHead);

int showAndEditList (list *&top);

list *viewOnePage(list *firstRec);

int menu(const char **menuItems, const int itemsCount);

long int checkNumeral(short X = 0, short Y = 0, long int num = 0, int maxDigitCount = 4);

char *strToFormat(char *str, const int length);

void helpMenu();

/*
 * MAIN FUNCTION
 */
int main() {

    while (1) {
        switch (menu(mainMenu, mainMenuItemsCount)) {
            case 2: {
                if (check(listHead)) {
                    organizeList(listHead, newRecord());
                    cout << "DATA ADD!" << endl;
                } else {
                    cout << "LIST WAS CREATED!" << endl;
                }
                cout << "0";
                getch();
                break;
            }
            case 1: {
                viewList(listHead);
                //showAndEditList(listHead);
                cout << "1";
                getch();
                break;
            }
            case 0: {
                if (!check(listHead)) {
                    addPerson(listHead, newRecord());
                    cout << "DATA ADD!" << endl;
                } else {
                    cout << "LIST NOT CREATED!" << endl;
                }
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
                if (strlen(openFileName) > 1) {
                    if (!saveFile(listHead, openFileName)) {
                        cout << "FILE SAVED" << endl;
                    } else {
                        cout << "FILE NOT SAVED!" << endl;
                    }
                } else {
                    char newFileName[FILE_NAME_LENGTH];
                    cout << "ENTER FILE NAME: ";
                    cin.getline(newFileName, FILE_NAME_LENGTH);
                    if (!saveFile(listHead, newFileName, 1)) {
                        cout << "FILE SAVED" << endl;
                        strcpy(openFileName, newFileName);
                    } else {
                        cout << "FILE NOT SAVED!" << endl;
                    }
                }
                getch();
                break;


                cout << "7";
                getch();
                break;
            }
            case 8: {
                //cout << "ENTER FILE NAME: ";
                //cin.getline(openFileName, FILE_NAME_LENGTH);
                if (!loadFile(listHead, /*openFileName*/ "2.bin")) {
                    cout << "FILE IS OPENED!" << endl;
                } else {
                    cout << "FILE NOT OPENED!" << endl;
                }
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
    newElement.salary = (float) checkNumeral(coordX, coordY, 0, 8);

    return newElement;
}


/*
 * СОХРАНЕНИЕ В ФАЙЛ
 * mode:
    * 0 - текстовый файл
    * 1 - бинарный
 */
int saveFile(list *top, char *fileName, bool mode) {
    system("cls");
    if (!check(top)) {
        list *temp;
        ofstream outFile;

        if (strstr(fileName, ".txt")) {
            outFile.open(fileName, ios::out);
        } else {
            strstr(fileName, ".bin");
            outFile.open(fileName, ios::out | ios::binary);
        }

        if (outFile) {
            for (temp = top; temp != NULL; temp = temp->next) {
                outFile.write((char *) &temp->inf, TABLE_DATA_SIZE);
            }

            outFile.close();
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }

}

/*
 * ЗАГРУЗКА ИЗ ФАЙЛА
 * mode:
    * 0 - текстовый файл
    * 1 - бинарный файл
 */

int loadFile(list *&top, char *fileName) {

    if (check(top)) {
        ifstream InFile;

        if (strstr(fileName, ".txt") != NULL) {
            InFile.open(fileName, ios::in);
        } else {
            InFile.open(fileName, ios::in | ios::binary);
        }

        if (InFile) {
            tableData tempInfo;
            while (InFile.readsome((char *) &tempInfo, TABLE_DATA_SIZE)) {
                if (check(top)) {
                    organizeList(top, tempInfo);
                } else {
                    addPerson(top, tempInfo);
                }
            }
            InFile.close();
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}


/*
 * Организация списка
 */
list *organizeList(list *&top, tableData personalData) {
    if (top == NULL) {
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

list *deletePersonalData(list *&current) {

    if (!check(current)) {
        if ((current->pred == NULL) && (current->next == NULL)) {
            delete current;
            current = NULL;
        } else if ((current->pred == NULL) && (current->next != NULL)) {
            list *temp = current;
            current = current->next;
            current->pred = NULL;
            delete temp;
        } else if (current->next == NULL) {
            list *temp = current;
            current = current->pred;
            delete temp;
        } else {
            list *temp = current;
            current->pred->next = current->next;
            current = temp->pred;
            delete temp;
        }
    }

    return current;
}


/*
 * Добавление записи в список
 */
list *addPerson(list *&top, tableData personalData) {
    if (!check(top)) {
        list *temp;
        for (temp = top; temp->next != NULL; temp = temp->next);
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
            cout << temp->inf.ID << " " << temp->inf.fio << " " << temp->inf.tableNumber << " "
                 << temp->inf.birth_year
                 << " " << temp->inf.sex << " " << temp->inf.prof << " " << temp->inf.salary << endl;
        }
    }
    return;
}

void viewList(list *&listHead) {
    if (!check(listHead)) {
        list *currentL, *temp, *startDisplay;
        int i, currentNum = 0;
        currentL = listHead;
        startDisplay = currentL;

        while (listHead != NULL) {

            system("cls");
            temp = startDisplay;

            for (i = 0; (i++ < countOfDisplayRecords) && (temp != NULL); temp = temp->next){
                if (i == currentNum){
                    SetColor(0, 7);
                }
                cout << temp->inf.ID << " " << temp->inf.fio << " " << temp->inf.tableNumber << endl;
                SetColor(8, 0);
            };

            helpMenu();


            switch (key = getch()) {
                case 72: {
                    if (currentL->pred != NULL) {
                        --currentNum;
                        currentL = currentL->pred;
                    }
                    break;
                }

                case 80: {
                    if (currentL->next != NULL) {
                        ++currentNum;
                        currentL = currentL->next;
                    }
                    break;
                }

                case 75:{
                    currentNum = 0;
                    temp = startDisplay;
                    for (i = 0; (i++ < countOfDisplayRecords) && (temp != NULL); temp = temp->pred);
                    if (check(temp)){
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }

                case 77:{
                    currentNum = 0;
                    temp = startDisplay;
                    for (i = 0; (i++ < countOfDisplayRecords) && (temp != NULL); temp = temp->next);
                    if (check(temp)){
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }
                case 83: {
                    deletePersonalData(currentL);
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

            if (currentNum > countOfDisplayRecords - 1){
                currentNum = 0;
                startDisplay = currentL;

            } else if (currentNum < 0){
                currentNum = countOfDisplayRecords;

                temp = startDisplay;
                for (i = 0; (i++ < countOfDisplayRecords) && (temp != NULL); temp = temp->pred);
                if (check(temp)){
                    temp = startDisplay;
                }
                startDisplay = temp;
            }

            /*if (currentNum < 0 && currentL != NULL) {
                currentNum = countOfDisplayRecords - 1;

                for (i = 1, temp = currentL;
                     (i < countOfDisplayRecords+1) && (temp->pred != NULL); i++, temp = temp->pred);
                startDisplay = temp;
            } else if (currentNum > countOfDisplayRecords && currentL != NULL) {
                currentNum = 0;
                startDisplay = currentL;
            }*/
        }
        cout << "EMPTY" << endl;
    } else return;

}

int showAndEditList(list *&top){
    int i;
    list *currentRec, *startRec;

    if (check(top)){
        cout << "EMPTY LIST" << endl;
        return -1;
    }

    currentRec = top;

    while (1){
        startRec = currentRec;

        currentRec = viewOnePage(currentRec);

        switch (key = getch()){
            case 27: {
                return 0;
            }
            case 13: case 72: case 80:{
                if (check(currentRec)) {
                    currentRec = startRec;
                }
                break;
            }
            case 75:{
                currentRec = startRec;
                for (i=1; (i<countOfDisplayRecords) && (!check(currentRec)); i++){
                    currentRec = currentRec->pred;
                }
                if (check(currentRec)) currentRec = top;
                break;
            }
            case 77:{
                currentRec = startRec;
                for (i=1; (i<countOfDisplayRecords) && (!check(currentRec)); i++){
                    currentRec = currentRec->next;
                }
                if (check(currentRec)) currentRec = top;
                break;
            }
        }
    }
}

list *viewOnePage(list *currentRec){
    int i = 0;
    system("cls");
    cout << "TABLE HEAD" << endl << endl << endl;
    while (!check(currentRec)) {
        cout << currentRec->inf.ID << " " << currentRec->inf.fio << " " << currentRec->inf.tableNumber << endl;
        currentRec = currentRec->next;
        i++;
        if (i>countOfDisplayRecords) {
            break;
        }
    }
    return currentRec;
}

void helpMenu() {
    SetColor(7, 1);
    cout << endl << endl << "ESC - MENU | ENTER - EDIT | DEL - DELETE | UP,DOWN - NAVIGATE | <-,-> SLIDE PAGE";
    SetColor(7, 0);
}

int menu(const char **menuItems, const int itemsCount) {
    int currentItem = 0, i = 0;
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
                return 27;
            }
        }
    }
}


//*/
long int checkNumeral(short X, short Y, long int num, int maxDigitCount) {

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
