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
const unsigned countOfDisplayRecords = 10;

int key;
struct tableData {
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
} *listHead = NULL, *listEnd = NULL;


/*
 * FUNCTIONS PROTOTYPES
 */
void gotoxy(short x, short y);

void SetColor(int text, int background);

void readTheKey();

void readTheAplpha();

tableData newRecord();

int saveFile(list *top, char *fileName, bool mode = 1);

int loadFile(list *&top, list *&end, char *fileName);

list *organizeList(list *&top, list *&end, tableData personalData);

list *addPerson(list *&end, tableData personalData);

int check(list *&top);

int deleteList(list *top);

int deletePersonalData(list *&listHead, list *&listEnd, list *current);

void view(list *&top);

void viewList(list *&listHead, list *&end);

int menu(const char **menuItems, const int itemsCount);

unsigned int checkNumeral(short X = 0, short Y = 0, long int num = 0, int maxDigitCount = 2);

char *strToFormat(char *str, const int length);

unsigned checkTableNum(int num, list *top);

void helpMenu();

/*
 * MAIN FUNCTION
 */
int main() {

    cout << setprecision(2) << fixed;
    while (1) {
        switch (menu(mainMenu, mainMenuItemsCount)) {
            case 2: {
                if (check(listHead)) {
                    organizeList(listHead, listEnd, newRecord());
                    cout << "DATA ADD!" << endl;
                } else {
                    cout << "LIST WAS CREATED!" << endl;
                }
                cout << "0";
                getch();
                break;
            }
            case 1: {
                viewList(listHead, listEnd);
                //showAndEditList(listHead);
                cout << "1";
                getch();
                break;
            }
            case 0: {
                if (!check(listHead)) {
                    addPerson(listEnd, newRecord());
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
                readTheAplpha();
                cout << "5";
                getch();
                break;
            }
            case 6: {
                system("cls");
                char fio[FIO_LENGTH];
                cin.getline(fio, FIO_LENGTH);
                cout << fio << endl;
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
                if (!loadFile(listHead, listEnd, /*openFileName*/ "2.bin")) {
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
 * Функция проверки кода клавиш
 */
void readTheAplpha() {
    while (char key = getch()) {
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

    gotoxy(0, coordY);
    cout << "FIO: ";
    char fio[FIO_LENGTH];
    cin.getline(fio, FIO_LENGTH);
    if (cin.fail()) {             //ПРИ ПЕРЕПОЛНЕНИИ БУФЕРА ВХОДНОГО ПОТОКА
        cin.clear();            //СБОРС ОШИБКА ПОТОКА
        cin.ignore(256, '\n');   //ИГНОРИРОВАНИЕ ОСТАВШИХСЯ В ПОТОКУ СИМВОЛОВ
    }

    strcpy(newElement.fio, strToFormat(fio, FIO_LENGTH));
    coordY++;

    gotoxy(0, coordY);
    cout << "TABLE: ";
    coordX = 7;
    int table_number;
    int checkResult = 0;
    do {
        if (checkResult){
            gotoxy(coordX+11,coordY);
            cout << "RECORD WITH SUCH DATA EXISTS!";
            getch();
        }
        table_number = checkNumeral(coordX, coordY, 0, 6);
    } while (checkResult = checkTableNum(table_number, listHead));
    gotoxy(coordX+11,coordY);
    cout << "                                           ";
    newElement.tableNumber = table_number;
    coordY++;


    gotoxy(0, coordY);
    cout << "BIRTH YEAR(1940..2050): ";
    coordX = 25;
    unsigned year = 0;
    while ((year < 1940) || (year > 2050)) {
        year = checkNumeral(coordX, coordY, 0, 4);
    }
    newElement.birth_year = year;
    coordY++;


    gotoxy(0, coordY);
    cout << "SEX(0-male,1-female): ";
    coordX = 24;
    short int sex = -1;
    while ((sex < 0) || (sex > 1)) {
        sex = checkNumeral(coordX, coordY, 0, 1);
    }
    newElement.sex = sex;
    coordY++;


    gotoxy(0, coordY);
    cout << "PROF: ";
    char prof[PROF_LENGTH];
    cin.getline(prof, PROF_LENGTH);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
    }
    strcpy(newElement.prof, strToFormat(prof, PROF_LENGTH));
    coordY++;


    gotoxy(0, coordY);
    cout << "EXPERIENCE: ";
    coordX = 12;
    newElement.exp = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    cout << "RANG: ";
    coordX = 6;
    newElement.rang = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    cout << "ROOM: ";
    coordX = 6;
    newElement.roomNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    cout << "LARGE ROOM: ";
    coordX = 12;
    newElement.bigRoomNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    cout << "PLACE: ";
    coordX = 7;
    newElement.placeNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
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

int loadFile(list *&top, list *&end, char *fileName) {

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
                    organizeList(top, end, tempInfo);
                } else {
                    addPerson(end, tempInfo);
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
list *organizeList(list *&top, list *&end, tableData personalData) {
    if (top == NULL) {
        struct list *newAdress = new list;
        newAdress->inf = personalData;
        newAdress->next = NULL;
        newAdress->pred = NULL;
        end = top = newAdress;
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

int deletePersonalData(list *&listHead, list *&listEnd, list *current) {
    if ((current == listHead) && (current == listEnd)) //удаление единственного элемента
    {
        listHead = NULL;
        listEnd = NULL;
        delete current;
        return 0;
    } else if (current == listHead) { //удаление из начала списка

        listHead = listHead->next;
        listHead->pred = NULL;
        delete current;
        return 1;
    } else if (current == listEnd) {//удаление с конца
        listEnd = listEnd->pred;
        listEnd->next = NULL;
        delete current;
        return 2;
    } else { //удаление из середины
        current->pred->next = current->next; //связать предыдущий со следующим
        current->next->pred = current->pred; //связать следующий с предыдущим
        delete current;
        return 3;
    }
}

/*
 * Добавление записи в список
 */
list *addPerson(list *&end, tableData personalData) {
    if (end != NULL) {
        list *New = new list;
        New->inf = personalData;
        New->next = NULL;
        New->pred = end;
        end->next = New;
        end = New;
    }
    return end;
}

/*
 * РЕДАКТИРОВАНИЕ ЗАПИСИ
 */
tableData *editData(tableData current) {
    unsigned currentNum;
}


int check(list *&top) {
    if (top == NULL) {
        return 1;
    }
    return 0;
}

void view(list *&top) {
    if (!check(top)) {
        list *temp;
        system("cls");
        for (temp = top; temp != NULL; temp = temp->next) {
            cout << temp->inf.fio << " " << temp->inf.tableNumber << " "
                 << temp->inf.birth_year
                 << " " << temp->inf.sex << " " << temp->inf.prof << " " << temp->inf.salary << endl;
        }
    }
    return;
}

void viewList(list *&listHead, list *&listEnd) {
    if (!check(listHead)) {
        list *currentL, *temp, *startDisplay;
        int i, currentNum = 1;
        startDisplay = currentL = listHead;
        short int delResult;

        while (listHead != NULL) {

            system("cls");
            temp = startDisplay;

            for (i = 1; (i <= countOfDisplayRecords) && (temp != NULL); temp = temp->next, i++) {
                if (i == currentNum) {
                    SetColor(0, 8);
                }
                cout << temp->inf.tableNumber << " " << temp->inf.fio << " " << temp->inf.salary << endl;
                SetColor(7, 0);
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

                case 75: {
                    currentNum = 1;
                    temp = startDisplay;
                    for (i = 1; (i++ <= countOfDisplayRecords) && (temp != NULL); temp = temp->pred);
                    if (check(temp)) {
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }

                case 77: {
                    currentNum = 1;
                    temp = startDisplay;
                    for (i = 1; (i++ <= countOfDisplayRecords) && (temp != NULL); temp = temp->next);
                    if (check(temp)) {
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }
                case 83: {
                    if (currentL == listHead) {
                        delResult = deletePersonalData(listHead, listEnd, currentL);
                        currentL = startDisplay = listHead;
                        currentNum = 1;
                    } else {
                        if (currentL == startDisplay) {
                            temp = startDisplay;
                            for (i = 1; (i++ <= countOfDisplayRecords) && (temp != NULL); temp = temp->pred);
                            startDisplay = temp;
                        }
                        currentL = currentL->pred;
                        delResult = deletePersonalData(listHead, listEnd, currentL->next);
                        currentNum--;

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

            if (currentNum > countOfDisplayRecords) {
                currentNum = 1;
                startDisplay = currentL;
            } else if ((currentNum < 1)) {

                currentNum = countOfDisplayRecords;


                temp = startDisplay;
                for (i = 1; (i <= countOfDisplayRecords) && (temp != NULL); temp = temp->pred, i++);
                if (check(temp)) {
                    temp = startDisplay;
                }
                startDisplay = temp;
            }
        }

        cout << "EMPTY" <<
             endl;
    } else return;

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
unsigned int checkNumeral(short X, short Y, long int num, int maxDigitCount) {

    long int tempNum = num;
    int currentDigitCount, minDigitCount = 0;

    for (currentDigitCount = 0; tempNum >= 1; currentDigitCount++) {
        tempNum = tempNum / 10;
    }

    tempNum = num;

    while (1) {
        gotoxy(X, Y);
        cout << "         ";


        if ((tempNum) || (maxDigitCount == 1)) {
            gotoxy(X, Y);
            cout << tempNum << endl;
        }


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

unsigned checkTableNum(int num, list *top){

    if (!check(top)){
        list *temp;
        for(temp = top; temp != NULL; temp = temp->next){
            if (temp->inf.tableNumber == num){
                return 1;
            }
        }
    }
    return 0;
}