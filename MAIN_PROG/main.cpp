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


const int searchMenuItemsCount = 5;
const char *searchMenu[searchMenuItemsCount] = {
        "SEARCH BY FIO",
        "SEARCH BY ID NUMBER",
        "SEARCH RANK GROUP",
        "SEARCH FACTORY GROUP",
        "SEARCH DEPORTMENT GROUP"
};


const int FIO_LENGTH = 20;
const int PROF_LENGTH = 10;
const int MAX_STR_LENGTH = 256;
unsigned console_row_length = 80;
char openFileName[MAX_STR_LENGTH];
const unsigned countOfDisplayRecords = 10;
const unsigned personalNumberMaxLength = 6;
const unsigned anyNumeralFieldLength = 2;
const unsigned salaryLength = 8;
int key;

struct tableData {
    int personalNumber;
    char fio[FIO_LENGTH];
    int birth_year;
    bool sex;
    char prof[PROF_LENGTH];
    int exp;
    int rank;
    int factoryNumber;
    int deportmentNumber;
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

tableData newRecord();

int saveFile(list *top, char *fileName, bool mode = 1);

int loadFile(list *&top, list *&end, char *fileName);

int organizeList(list *&top, list *&end, tableData personalData);

int addPerson(list *&end, tableData personalData);

int deleteList(list *&top);

int deletePersonalData(list *&listHead, list *&listEnd, list *current);

tableData editData(tableData current);

void outData(list *temp);

void viewList(list *&listHead, list *&end, unsigned mode = 0);

int menu(const char **menuItems, const int itemsCount);

int menuInterface(const char **menuItems, const int itemsCount = 2);

unsigned int checkNumeral(short X = 0, short Y = 0, long int num = 0, int maxDigitCount = 2);

char *strToFormat(char *str, const int length);

void cleanPlace();

void cleanStatusBar();

int rewriteString(unsigned X, unsigned Y, const int length, char *tempStr);

unsigned checkPersonalNumber(int num, list *top);

unsigned numberCount(long int Num);

void drawHelpMenu(unsigned mode = 0);

void drawTableHead();

int groupSearch(list *&head);

/*
 * MAIN FUNCTION
 */
int main() {

    while (1) {
        switch (menu(mainMenu, mainMenuItemsCount)) {

            case 0: {
                if (listHead != NULL) {
                    if (!addPerson(listEnd, newRecord())) {
                        printf("DATA ADDED!");
                        getch();
                    }
                } else {
                    printf("LIST NOT CREATED!");
                    getch();
                }
                break;
            }

            case 1: {
                if (listHead != NULL) {
                    viewList(listHead, listEnd, 0);
                } else {
                    printf("EMPTY LIST");
                    getch();
                }

                break;
            }

            case 2: {
                if (listHead == NULL) {
                    if (!organizeList(listHead, listEnd, newRecord())) {
                        printf("DATA ADDED!");
                        getch();
                    }
                } else {
                    printf("LIST WAS CREATED!");
                    getch();
                }
                break;
            }

            case 3: {
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
                cleanStatusBar();
                if (listHead != NULL) {
                    if (!menuInterface(saveFileMessage, saveFileMessageItemsCount) && (strlen(openFileName) > 1)) {
                        cleanStatusBar();
                        printf("REWRITE?:");
                        if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                            cleanStatusBar();
                            if (!saveFile(listHead, openFileName)) {
                                printf("FILE SAVED");
                            } else {
                                printf("FILE NOT SAVED!");
                            }
                        }
                    } else {
                        cleanStatusBar();
                        if (strlen(openFileName) < 3) {
                            printf("FILE WILL BE CREATE");
                        }
                        char newFileName[MAX_STR_LENGTH];
                        printf("ENTER FILE NAME(*.bin - binary, *.txt - text): ");
                        cin.getline(newFileName, MAX_STR_LENGTH);
                        if (cin.fail()) {             //ПРИ ПЕРЕПОЛНЕНИИ БУФЕРА ВХОДНОГО ПОТОКА
                            cin.clear();            //СБРОС ОШИБКИ ПОТОКА
                            cin.ignore(1000, '\n');   //ИГНОРИРОВАНИЕ ОСТАВШИХСЯ В ПОТОКЕ СИМВОЛОВ
                        }
                        if (!saveFile(listHead, newFileName)) {
                            printf("FILE SAVED");
                            strcpy(openFileName, newFileName);
                        } else {
                            printf("FILE NOT SAVED!");
                        }

                    }
                } else {
                    printf("EMPTY LIST");
                }

                getch();
                break;
            }


            case 8: {
                printf("DO YOU WANT OPEN FILE(CURRENT DATA WILL BE CLEARED)?");
                if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                    deleteList(listHead);
                    cleanStatusBar();

                    printf("ENTER FILE NAME: ");
                    cin.getline(openFileName, MAX_STR_LENGTH);
                    if (cin.fail()) {             //ПРИ ПЕРЕПОЛНЕНИИ БУФЕРА ВХОДНОГО ПОТОКА
                        cin.clear();            //СБРОС ОШИБКИ ПОТОКА
                        cin.ignore(1000, '\n');   //ИГНОРИРОВАНИЕ ОСТАВШИХСЯ В ПОТОКЕ СИМВОЛОВ
                    }
                    if (!loadFile(listHead, listEnd, openFileName)) {
                        printf("FILE IS OPENED!");
                    } else {
                        printf("FILE NOT OPENED!");
                    }
                }
                getch();
                break;
            }

            case 9: {
                groupSearch(listHead);
                cout << "9";
                getch();
                break;
            }

            case 10: {
                cout << "10";
                getch();
                break;
            }

            case 11:
            case 27: {
                printf("EXIT?");
                if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                    deleteList(listHead);
                    exit(0);
                } else {
                    break;
                }
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
            printf("Will exit");
            return;
        }
    }
}


/*
 * Функция создания записи
 */
tableData newRecord() {


    tableData newElement;

    system("cls");
    printf("ENTER PERSONAL DATA OR PRESS ESC to main menu: \n");
    if (getch() == 27) {
        newElement.personalNumber = -1;
        return newElement;
    }
    unsigned coordY = 1, coordX = 5;

    printf("FIO: ");
    char fio[FIO_LENGTH] = "\0";
    rewriteString(coordX, coordY, FIO_LENGTH, fio);

    /*cin.getline(fio, FIO_LENGTH);
    if (cin.fail()) {             //ПРИ ПЕРЕПОЛНЕНИИ БУФЕРА ВХОДНОГО ПОТОКА
        cin.clear();            //СБРОС ОШИБКИ ПОТОКА
        cin.ignore(1000, '\n');   //ИГНОРИРОВАНИЕ ОСТАВШИХСЯ В ПОТОКЕ СИМВОЛОВ
    }*/

    strcpy(newElement.fio, strToFormat(fio, FIO_LENGTH));
    coordY++;

    gotoxy(0, coordY);
    printf("PERSONAL NUMBER: ");
    coordX = 17;
    int personal_number;
    bool checkResult = false;
    do {
        if (checkResult) {
            gotoxy(coordX + 11, coordY);
            printf("RECORD WITH SUCH DATA EXISTS!");
            getch();
        }
        personal_number = checkNumeral(coordX, coordY, 0, 6);
    } while (checkResult = checkPersonalNumber(personal_number, listHead));
    gotoxy(coordX + 11, coordY);
    printf("                                           ");
    newElement.personalNumber = personal_number;
    coordY++;


    gotoxy(0, coordY);
    printf("BIRTH YEAR(1940..2050): ");
    coordX = 25;
    unsigned year = 0;
    while ((year < 1940) || (year > 2050)) {
        year = checkNumeral(coordX, coordY, 0, 4);
    }
    newElement.birth_year = year;
    coordY++;


    gotoxy(0, coordY);
    printf("SEX(0-male,1-female): ");
    coordX = 24;
    short int sex = -1;
    while ((sex < 0) || (sex > 1)) {
        sex = checkNumeral(coordX, coordY, 0, 1);
    }
    newElement.sex = sex;
    coordY++;


    gotoxy(0, coordY);
    printf("PROF: ");
    char prof[PROF_LENGTH] = "\0";
    coordX = 6;
    rewriteString(coordX, coordY, PROF_LENGTH, prof);
    /*cin.getline(prof, PROF_LENGTH);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
    }*/
    strcpy(newElement.prof, strToFormat(prof, PROF_LENGTH));
    coordY++;


    gotoxy(0, coordY);
    printf("EXPERIENCE: ");
    coordX = 12;
    newElement.exp = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    printf("RANK: ");
    coordX = 6;
    newElement.rank = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    printf("FACTORY #: ");
    coordX = 11;
    newElement.factoryNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    printf("DEPORTMENT #: ");
    coordX = 14;
    newElement.deportmentNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    printf("SALARY: ");
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

    if (top != NULL) {
        list *temp;
        ofstream outFile;

        if ((strstr(fileName, ".txt")) || (mode == 0)) {
            outFile.open(fileName, ios::out);
            if (outFile) {
                unsigned counter;
                for (temp = top; temp != NULL; temp = temp->next) {
                    outFile << temp->inf.fio << "\n";
                    for (counter = 0; counter < personalNumberMaxLength - numberCount(
                            temp->inf.personalNumber); counter++) {//6 МАКСИМАЛЬНОЕ КОЛ-ВО ЦИФР В ПОЛЕ personalNumber
                        outFile << 0;
                    }
                    outFile << temp->inf.personalNumber << " ";
                    outFile << temp->inf.birth_year << " ";

                    for (counter = 0; counter < anyNumeralFieldLength - numberCount(temp->inf.rank); counter++) {
                        outFile << 0;
                    }
                    outFile << temp->inf.rank << " ";

                    outFile << temp->inf.sex << " ";

                    for (counter = 0; counter < anyNumeralFieldLength - numberCount(temp->inf.exp); counter++) {
                        outFile << 0;
                    }
                    outFile << temp->inf.exp << " ";

                    outFile << temp->inf.prof << "\n";

                    for (counter = 0;
                         counter < anyNumeralFieldLength - numberCount(temp->inf.factoryNumber); counter++) {
                        outFile << 0;
                    }
                    outFile << temp->inf.factoryNumber << " ";

                    for (counter = 0;
                         counter < anyNumeralFieldLength - numberCount(temp->inf.deportmentNumber); counter++) {
                        outFile << 0;
                    }
                    outFile << temp->inf.deportmentNumber << " ";

                    for (counter = 0; counter < salaryLength - numberCount((long int) temp->inf.salary); counter++) {
                        outFile << 0;
                    }
                    outFile << temp->inf.salary << "\n";
                }

                outFile.close();
                return 0;
            } else {
                return 1;
            }


        } else if ((strstr(fileName, ".bin")) || (mode == 1)) {
            outFile.open(fileName, ios::out | ios::binary);

            if (outFile) {
                for (temp = top; temp != NULL; temp = temp->next) {
                    outFile.write((char *) &temp->inf, TABLE_DATA_SIZE);
                }

                outFile.close();
                return 0;
            } else {
                return 1;
            }
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

    if (top == NULL) {
        ifstream InFile;

        if (strstr(fileName, ".txt") != NULL) {
            InFile.open(fileName, ios::in);
            if (InFile) {
                tableData tempData;
                int i = 0;
                while (!InFile.eof()) {
                    InFile >> tempData.fio;
                    InFile >> tempData.personalNumber;
                    InFile >> tempData.birth_year;
                    InFile >> tempData.rank;
                    InFile >> tempData.sex;
                    InFile >> tempData.exp;
                    InFile >> tempData.prof;
                    InFile >> tempData.factoryNumber;
                    InFile >> tempData.deportmentNumber;
                    InFile >> tempData.salary;

                    if (top == NULL) {
                        organizeList(top, end, tempData);
                    } else {
                        addPerson(end, tempData);
                    }
                    cout << ++i << endl;
                }
                InFile.close();
                return 0;
            } else {
                return -1;
            }

        } else {
            InFile.open(fileName, ios::in | ios::binary);

            if (InFile) {
                tableData tempData;
                while (InFile.read((char *) &tempData, TABLE_DATA_SIZE)) {
                    if (top == NULL) {
                        organizeList(top, end, tempData);
                    } else {
                        addPerson(end, tempData);
                    }
                }
                InFile.close();
                return 0;
            } else {
                return -1;
            }
        }


    } else {
        return 1;
    }
}


/*
 * Организация списка
 */
int organizeList(list *&top, list *&end, tableData personalData) {
    if ((top == NULL) && (personalData.personalNumber != -1)) {
        struct list *newAdress = new list;
        newAdress->inf = personalData;
        newAdress->next = NULL;
        newAdress->pred = NULL;
        end = top = newAdress;
        return 0;
    }
    return 1;
}

/*
 * Добавление записи в список
 */
int addPerson(list *&end, tableData personalData) {
    if ((end != NULL) && (personalData.personalNumber != -1)) {
        list *New = new list;
        New->inf = personalData;
        New->next = NULL;
        New->pred = end;
        end->next = New;
        end = New;
        return 0;
    }
    return 1;
}

int deleteList(list *&top) {

    if (top != NULL) {
        list *temp;

        int i = 0;
        for (temp = top; top != NULL; temp = top) {
            top = temp->next;
            delete temp;
        }
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
    } else if (current == listHead) { //из начала списка

        listHead = listHead->next;
        listHead->pred = NULL;
        delete current;
        return 1;
    } else if (current == listEnd) {//с конца
        listEnd = listEnd->pred;
        listEnd->next = NULL;
        delete current;
        return 2;
    } else { //удаление из середины
        current->pred->next = current->next;
        current->next->pred = current->pred;
        delete current;
        return 3;
    }
}


/*
 * РЕДАКТИРОВАНИЕ ЗАПИСИ
 */
tableData editData(tableData mainData) {

    unsigned countOfFields = 10;
    unsigned currentField = 0, i;
    unsigned coordX = 0, coordY = 17;
    tableData current = mainData;
    drawHelpMenu(1);

    while (1) {
        cleanStatusBar();
        for (i = 0; (i < countOfFields); i++) {
            if (i == currentField) {
                SetColor(0, 8);
            }
            switch (i) {

                case 0: {
                    cout << setw(20) << current.fio << " ";
                    break;
                }

                case 1: {
                    cout << setw(7) << current.personalNumber << " ";
                    break;
                }

                case 2: {
                    cout << setw(5) << current.birth_year << " ";
                    break;
                }

                case 3: {
                    cout << setw(2) << current.sex << " ";
                    break;
                }

                case 4: {
                    cout << setw(10) << current.prof << " ";
                    break;
                }

                case 5: {
                    cout << setw(3) << current.exp << " ";
                    break;
                }

                case 6: {
                    cout << setw(4) << current.rank << " ";
                    break;
                }

                case 7: {
                    cout << setw(4) << current.factoryNumber << " ";
                    break;
                }

                case 8: {
                    cout << setw(5) << current.deportmentNumber << " ";
                    break;
                }

                case 9: {
                    cout << setprecision(2) << fixed << setw(11) << current.salary;
                    break;
                }
            }
            SetColor(7, 0);
        }

        switch (key = getch()) {
            case 13: {

                switch (currentField) {
                    case 0: {
                        break;
                    }
                    case 1: {
                        current.personalNumber = checkNumeral(22, coordY, current.personalNumber, 6);
                        break;
                    }
                    case 2: {
                        current.birth_year = checkNumeral(30, coordY, current.birth_year, 4);
                        break;
                    }
                    case 3: {
                        current.sex = checkNumeral(36, coordY, current.sex, 1);
                        break;
                    }
                    case 4: {
                        //current. = checkNumeral(31, coordY, current., 4);
                        break;
                    }
                    case 5: {
                        current.exp = checkNumeral(50, coordY, current.exp, 2);
                        break;
                    }
                    case 6: {
                        current.rank = checkNumeral(56, coordY, current.rank, 2);
                        break;
                    }
                    case 7: {
                        current.factoryNumber = checkNumeral(60, coordY, current.factoryNumber, 2);
                        break;
                    }
                    case 8: {
                        current.deportmentNumber = checkNumeral(67, coordY, current.deportmentNumber, 2);
                        break;
                    }
                    case 9: {
                        current.salary = (float) checkNumeral(69, coordY, (long int) current.salary, 8);
                        break;
                    }
                }
            }
            case 77: {
                if (currentField >= countOfFields - 1) currentField = 0;
                else currentField++;
                break;
            }
            case 75: {
                if (currentField <= 0) currentField = countOfFields - 1;
                else currentField--;
                break;
            }
            case 96: {
                if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                    return current;
                }
                break;
            }
            case 27: {
                return mainData;
            }
        }
    }

}

void outData(list *temp) {
    cout << setw(20) << temp->inf.fio << " "
         << setw(7) << temp->inf.personalNumber << " "
         << setw(5) << temp->inf.birth_year << " "
         << setw(2) << temp->inf.sex << " "
         << setw(10) << temp->inf.prof << " "
         << setw(3) << temp->inf.exp << " "
         << setw(4) << temp->inf.rank << " "
         << setw(4) << temp->inf.factoryNumber << " "
         << setw(5) << temp->inf.deportmentNumber << " "
         << setprecision(2) << fixed << setw(11) << temp->inf.salary;
}

void viewList(list *&listHead, list *&listEnd, unsigned mode) {
    if (listHead != NULL) {
        list *currentL, *temp, *startDisplay;
        int i, currentNum = 1;
        startDisplay = currentL = listHead;
        short int delResult;

        while (listHead != NULL) {

            system("cls");
            temp = startDisplay;

            drawTableHead();

            for (i = 1; (i <= countOfDisplayRecords) && (temp != NULL); temp = temp->next, i++) {
                if (i == currentNum) {
                    SetColor(0, 8);
                }
                outData(temp);
                SetColor(7, 0);
            };

            drawHelpMenu(mode);


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
                    if (temp == NULL) {
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }

                case 77: {
                    currentNum = 1;
                    temp = startDisplay;
                    for (i = 1; (i++ <= countOfDisplayRecords) && (temp != NULL); temp = temp->next);
                    if (temp == NULL) {
                        temp = startDisplay;
                    }
                    startDisplay = currentL = temp;
                    break;
                }
                case 83: {
                    if (!mode) {
                        printf("DO YOU WANT DELTE THIS DATA? \n");

                        if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
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
                        }
                    }
                    break;
                }
                case 96: {
                    if (mode) {
                        cleanStatusBar();
                        printf("ENTER FILE NAME: ");
                        char file_name[MAX_STR_LENGTH];
                        char default_name[MAX_STR_LENGTH + 11] = "selection_";
                        cin.getline(file_name, MAX_STR_LENGTH);
                        if (cin.fail()) {             //ПРИ ПЕРЕПОЛНЕНИИ БУФЕРА ВХОДНОГО ПОТОКА
                            cin.clear();            //СБРОС ОШИБКИ ПОТОКА
                            cin.ignore(1000, '\n');   //ИГНОРИРОВАНИЕ ОСТАВШИХСЯ В ПОТОКЕ СИМВОЛОВ
                        }
                        strcat(default_name, file_name);

                        if (!saveFile(listHead, default_name)) {
                            printf("FILE SAVED");
                        } else {
                            printf("FILE NOT SAVED!");
                        }
                        getch();
                    }

                    break;
                }
                case 13: {
                    if (!mode) {
                        currentL->inf = editData(currentL->inf);
                    }
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
                if (temp == NULL) {
                    temp = startDisplay;
                }
                startDisplay = temp;
            }
        }

        cout << "EMPTY" <<
             endl;
    } else return;

}

//ПЕЧАТЬ ДОПОЛНИТЕЛЬНОГО МЕНЮ
void drawHelpMenu(unsigned mode) {
    gotoxy(0, 15);
    SetColor(7, 1);
    printf("ESC - MENU | ENTER - SELECT |");
    (!mode) ? printf(" DEL - DLT") : printf(" ~ - SAVE ");
    printf(" | UP,DOWN - NAVIGATE | <-,-> SLIDE PAGE ");
    SetColor(7, 0);

    for (int i = 0; i < 35; i++) putch('-');
    cout << "STATUS BAR";
    for (int i = 0; i < 35; i++) putch('-');
    gotoxy(0, 19);
    for (int i = 0; i < console_row_length - 1; i++) putch('-');
    cleanStatusBar();
}

void drawTableHead() {

    gotoxy(0, 0);

    for (int i = 0; i < console_row_length; i++) {
        cout << "-";
    }

    printf("          FIO       |");
    printf("  ID   |");
    printf(" YEAR|");
    printf(" S|");
    printf("   PROF   |");
    printf("EXP|");
    printf("RANK|");
    printf("FACT|");
    printf(" DEPT|");
    printf("   SALARY  ");
    for (int i = 0; i < console_row_length; i++) {
        putch('-');
    }


};

int menu(const char **menuItems, const int itemsCount) {
    int currentItem = 0, i = 0;
    while (1) {

        system("cls");
        for (i = 0; i < itemsCount; i++) {
            if (i == currentItem) {
                SetColor(0, 8);
            }
            printf("%s \n", menuItems[i]);
            SetColor(7, 0);
        }

        drawHelpMenu();

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

int menuInterface(const char **menuItems, const int itemsCount) {
    int currentItem = 0, i = 0;
    while (1) {
        cleanPlace();
        gotoxy((40 - (strlen(menuItems[0]) / 2)), 20);
        for (i = 0; i < itemsCount; i++) {
            if (i == currentItem) {
                SetColor(7, 4);
            }
            printf("%s \n", menuItems[i]);
            SetColor(7, 0);
            gotoxy((40 - (strlen(menuItems[1]) / 2)), 21);

        }

        switch (key = getch()) {
            case 13: {
                cleanPlace();
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
                cleanPlace();
                return 0;
            }
        }
    }
}

void cleanPlace() {
    int i;
    gotoxy(0, 20);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    return;
}

void cleanStatusBar() {
    int i;
    gotoxy(0, 17);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    gotoxy(0, 17);
    return;
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
        for (int i = 0; i < maxDigitCount; i++) {
            putch(' ');
        }


        if ((tempNum) || (maxDigitCount == 1)) {
            gotoxy(X, Y);
            printf("%d \n", tempNum);
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

int rewriteString(unsigned X, unsigned Y, const int length, char *str) {

    char tempStr[length];
    strcpy(tempStr, str);
    unsigned currentPosition;

    currentPosition = strlen(str);

    while (1) {

        gotoxy(X, Y);

        for (int i = 0; i < length; i++) {
            putch(' ');
        }

        gotoxy(X, Y);
        cout << tempStr << endl;

        switch (key = getch()) {

            case 13: {
                strcpy(str, tempStr);
                return 1;
            }

            case 8: {
                if (currentPosition > 0) {
                    currentPosition--;
                }
                break;
            }

            case 27: {
                return 0;
            }
            default: {

                if (((key >= 65) && (key <= 122)) || ((key >= 128) && (key <= 175)) || ((key >= 224) && (key <= 241)) ||
                    (key == 32)) {
                    if (currentPosition < length) {
                        tempStr[currentPosition++] = (char) key;
                    }
                }

                break;
            }
        }
        tempStr[currentPosition] = '\0';
    }
}


unsigned checkPersonalNumber(int num, list *top) {

    if (top != NULL) {
        list *temp;
        for (temp = top; temp != NULL; temp = temp->next) {
            if (temp->inf.personalNumber == num) {
                return 1;
            }
        }
    }
    return 0;
}

unsigned numberCount(long int Num) {
    int count = 1;
    while (Num /= 10) {
        count++;
    }
    return count;
}

/*
 * ФУНКЦИЯ ДЛЯ ПОИСКА ДАННЫХ ПО КЛЮЧЕВОМУ ПОЛЮ
 */

int groupSearch(list *&head) {
    if (head == NULL) {
        cleanStatusBar();
        cout << "EMPTY LIST" << endl;
        return 1;
    }
    list *temp, *tempHead, *tempEnd;
    tempHead = tempEnd = NULL;

    bool searchResult = false;

    switch (menu(searchMenu, searchMenuItemsCount)) {
        case 27: {
            return 27;
        }
        case 0: {
            printf("ENTER KEY: ");
            char FIO[FIO_LENGTH];
            cin.getline(FIO, FIO_LENGTH);
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            strToFormat(FIO, FIO_LENGTH);
            for (temp = head; temp != NULL; temp = temp->next) {
                if (strstr(temp->inf.fio, FIO)) {
                    searchResult = true;
                    break;
                    //outData(temp);
                }
            }
            if (searchResult) {
                system("cls");
                drawTableHead();
                temp->inf = editData(temp->inf);
            }
            break;
        }
        case 1: {
            printf("ENTER KEY: ");
            long int tempNumber = checkNumeral(11, 0, 0, 6);
            drawTableHead();
            for (temp = head; temp != NULL; temp = temp->next) {
                if (temp->inf.personalNumber == tempNumber) {
                    searchResult = true;
                    break;
                }
            }
            if (searchResult) {
                system("cls");
                drawTableHead();
                temp->inf = editData(temp->inf);
            }
            break;
        }
        case 2: {
            printf("ENTER KEY: ");
            long int tempNumber = checkNumeral(11, 17, 0, 2);
            for (temp = head; temp != NULL; temp = temp->next) {
                if (temp->inf.rank == tempNumber) {
                    searchResult = true;
                    if (tempHead == NULL) {
                        organizeList(tempHead, tempEnd, temp->inf);
                    } else {
                        addPerson(tempEnd, temp->inf);
                    }
                }
            }
            viewList(tempHead, tempEnd, 1);
            break;
        }
        case 3: {
            printf("ENTER KEY: ");
            long int tempNumber = checkNumeral(11, 17, 0, 2);
            for (temp = head; temp != NULL; temp = temp->next) {
                if (temp->inf.factoryNumber == tempNumber) {
                    searchResult = true;
                    if (tempHead == NULL) {
                        organizeList(tempHead, tempEnd, temp->inf);
                    } else {
                        addPerson(tempEnd, temp->inf);
                    }
                }
            }
            viewList(tempHead, tempEnd, 1);
            break;
        }

        case 4: {
            printf("ENTER KEY: ");
            long int tempNumber = checkNumeral(11, 17, 0, 2);
            for (temp = head; temp != NULL; temp = temp->next) {
                if (temp->inf.deportmentNumber == tempNumber) {
                    searchResult = true;
                    if (tempHead == NULL) {
                        organizeList(tempHead, tempEnd, temp->inf);
                    } else {
                        addPerson(tempEnd, temp->inf);
                    }
                }
            }
            viewList(tempHead, tempEnd, 1);
            break;
        }
    }
    if (!searchResult) {
        cout << "DATA NOT FOUND" << endl;
    }
    deleteList(tempHead);
    return 0;
}

