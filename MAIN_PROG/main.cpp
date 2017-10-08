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
        "ADD PERSONAL DATA",
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

const int exitMessageItemsCount = 2;
const char *exitMessage[exitMessageItemsCount] = {
        "SAVE AND EXIT",
        "EXIT"
};

const int searchMenuItemsCount = 5;
const char *searchMenu[searchMenuItemsCount] = {
        "SEARCH BY FIO",
        "SEARCH BY ID NUMBER",
        "SEARCH RANK GROUP",
        "SEARCH FACTORY GROUP",
        "SEARCH DEPORTMENT GROUP"
};


const int sortMenuItemsCount = 8;
const char *sortMenu[sortMenuItemsCount] = {
        "SORT BY FIO",
        "SORT BY ID",
        "SORT BY PROF",
        "SORT BY FACTORY",
        "SORT BY DEPORTMENT",
        "SORT BY SALARY",
        "SORT BY SEX",
        "SORT BY PROF RANK"
};


const int FIO_LENGTH = 21;
const int PROF_LENGTH = 11;
const int MAX_STR_LENGTH = 256;
unsigned console_row_length = 80;
char openFileName[MAX_STR_LENGTH];
const unsigned countOfDisplayRecords = 10;
int key, main_menu_current_item = 0;
short int sort_mode = 1;

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

//FILE
int saveFile(list *top, char *fileName, bool mode = 1);

int loadFile(list *&top, list *&end, char *fileName);

void saveFileInterface();

void loadFileInterface();

//LIST MANIPULATION

tableData newRecord();

int organizeList(list *&top, list *&end, tableData personalData);

int addPerson(list *&end, tableData personalData);

tableData editData(tableData current);

int deleteList(list *&top);

int deletePersonalData(list *&listHead, list *&listEnd, list *current);

void outData(list *temp);

void viewList(list *&listHead, list *&end, unsigned mode = 0);


//INTERFACE
int menu(const char **menuItems, const int itemsCount, int currentItem = 0);

int menuInterface(const char **menuItems, const int itemsCount = 2);

void drawHelpMenu(unsigned mode = 0);

void drawTableHead(unsigned X = 0, unsigned Y = 0);

void cleanPlace();

void cleanStatusBar();

void emptyMessage();


//CHECK AND FORMAT
unsigned int checkNumeral(short X = 0, short Y = 0, long int num = 0, int maxDigitCount = 2);

char *strToFormat(char *str, const int length);

int rewriteString(unsigned X, unsigned Y, const int length, char *tempStr);

unsigned checkPersonalNumber(int num, list *top);

//SORT
int sort(list *&head, list *&end, short int mode = 1);

int searchData(list *&head, short int mode = 0);


/*
 * MAIN FUNCTION
 */
int main() {

    SetConsoleCP(866);
    SetConsoleOutputCP(866);

    while (1) {
        switch (main_menu_current_item = menu(mainMenu, mainMenuItemsCount, main_menu_current_item)) {

            case 0: {
                if (listHead != NULL) {
                    if (!addPerson(listEnd, newRecord())) {
                        printf("\nDATA ADDED!");
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
                    emptyMessage();
                }

                break;
            }

            case 2: {
                if (listHead == NULL) {
                    if (!organizeList(listHead, listEnd, newRecord())) {
                        printf("\nDATA ADDED!");
                        getch();
                    }
                } else {
                    printf("\nLIST WAS CREATED! USE ADD FUNCTION!");
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
                int sortMode = menu(sortMenu, sortMenuItemsCount);

                if ((sort_mode = sort(listHead, listEnd, sortMode)) >= 0) {
                    viewList(listHead, listEnd, 0);
                }
                break;
            }

            case 7: {
                saveFileInterface();
                getch();
                break;
            }


            case 8: {
                loadFileInterface();
                getch();
                sort_mode = sort(listHead, listEnd);
                break;
            }

            case 9: {
                int searchMode = menu(searchMenu, searchMenuItemsCount);
                searchData(listHead, searchMode);
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
                if (listHead != NULL) {
                    unsigned exitChange = menuInterface(exitMessage, exitMessageItemsCount);

                    if (exitChange == 0) {
                        cleanStatusBar();
                        SetColor(12, 0);
                        printf("REWRITE?:");
                        SetColor(7, 0);
                        if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                            cleanStatusBar();
                            if (!saveFile(listHead, openFileName)) {
                                printf("FILE SAVED");
                            } else {
                                printf("FILE NOT SAVED!");
                            }
                            getch();
                        }
                        deleteList(listHead);
                        exit(0);
                    }

                } else {
                    if (menuInterface(acceptMessage, acceptMessageItemsCount) == 1) {
                        deleteList(listHead);
                        exit(0);
                    }
                    break;
                }


            }
        }
    }

}

/*
 * FUNCTION IMPLEMENTATION
 */

/*‘ÛÌÍˆËˇ ÔÓÁËˆËÓÌËÓ‚‡ÌËˇ ÍÛÒÓ‡ ‚ ÍÓÌÒÓÎË*/
void gotoxy(short x, short y) {
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

/*‘ÛÌÍˆËˇ ‚˚·Ó‡ ˆ‚ÂÚ‡ ÚÂÍÒÚ‡ Ë ÙÓÌ‡ ‚ ÍÓÌÒÓÎË*/
void SetColor(int text, int background) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD) ((background << 4) | text));
}

/*
 * ‘ÛÌÍˆËˇ ÔÓ‚ÂÍË ÍÓ‰‡ ÍÎ‡‚Ë¯
 */
void readTheKey() {
    char key2;
    while (int key = getch()) {
        key2 = key;
        cout << key << " = " << key2 << endl;
        if (key == 13) {
            printf("Will exit");
            return;
        }
    }
}


/*
 * ‘”Õ ÷»ﬂ ƒÀﬂ «¿œŒÀÕ≈Õ»ﬂ ƒ¿ÕÕ€’ —“–” “”–€ ›À≈Ã≈Õ“¿
 * ¬Œ«¬–¿Ÿ¿≈“ «¿œŒÀÕ≈ÕÕ”ﬁ —“–” “”–”
 * ≈—À» ƒ¿ÕÕ€≈ œŒÀﬂ Õ≈ ¬¬≈ƒ≈Õ€:
        “≈ —“Œ¬Œ≈ == "\0":
        ◊»—ÀŒ¬Œ≈ == 0;
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

    strcpy(newElement.fio, fio);
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
    strcpy(newElement.prof, prof);
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
    newElement.salary = (float) checkNumeral(coordX, coordY, 0, 7);

    return newElement;
}

/*
 * ‘”Õ ÷»ﬂ —Œ’–¿Õ≈Õ»ﬂ Œ◊≈–≈ƒ» ¬ ‘¿…À
 * mode:
    * 0 - ÚÂÍÒÚÓ‚˚È Ù‡ÈÎ ËÎË ÂÒÎË Ù‡ÈÎ ËÏÂÂÚ ‡Ò¯ËÂÌËÂ ".txt"
        * œŒ—À≈ “≈ —“Œ¬€’ œŒÀ≈… ƒŒ¡¿¬Àﬂ≈“ —»Ã¬ŒÀ '\n'
        * œŒ—À≈ ◊»—ÀŒ¬€’ " "

    * 1 - ·ËÌ‡Ì˚È Ù‡ÈÎ ËÎË ÂÒÎË Ù‡ÈÎ ËÏÂÂÚ ‡Ò¯ËÂÌËÂ ".bin"
 */
int saveFile(list *top, char *fileName, bool mode) {

    if (top != NULL) {
        list *temp;
        ofstream inFile;
        int j;

        if ((strstr(fileName, ".txt")) || (mode == 0)) {
            inFile.open(fileName, ios::out);
            if (inFile) {
                for (temp = top; temp != NULL; temp = temp->next) {
                    inFile << temp->inf.fio << '\n';

                    inFile << temp->inf.personalNumber << " ";

                    inFile << temp->inf.birth_year << " ";

                    inFile << temp->inf.sex;

                    inFile << temp->inf.prof << '\n';

                    inFile << temp->inf.exp << " ";

                    inFile << temp->inf.rank << " ";

                    inFile << temp->inf.factoryNumber << " ";

                    inFile << temp->inf.deportmentNumber << " ";

                    inFile << (long int) temp->inf.salary;
                }
                inFile.close();
                return 0;
            } else {
                return 1;
            }


        } else if ((strstr(fileName, ".bin")) || (mode == 1)) {
            inFile.open(fileName, ios::out | ios::binary);

            if (inFile) {
                for (temp = top; temp != NULL; temp = temp->next) {
                    inFile.write((char *) &temp->inf, TABLE_DATA_SIZE);
                }

                inFile.close();
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
 * ‘”Õ ÷»ﬂ «¿√–”« » Œ◊≈–≈ƒ» »« ‘¿…À¿
 */
int loadFile(list *&top, list *&end, char *fileName) {

    if (top == NULL) {
        ifstream outFile;

        if (strstr(fileName, ".txt") != NULL) {
            outFile.open(fileName, ios::in);
            if (outFile) {
                tableData tempData;
                int i = 0;

                while (!outFile.eof()) {
                    outFile.getline(tempData.fio, FIO_LENGTH);////

                    outFile >> tempData.personalNumber;
                    outFile >> tempData.birth_year;
                    outFile >> tempData.sex;

                    outFile.getline(tempData.prof, PROF_LENGTH);/////

                    outFile >> tempData.exp;
                    outFile >> tempData.rank;
                    outFile >> tempData.factoryNumber;
                    outFile >> tempData.deportmentNumber;
                    outFile >> tempData.salary;

                    if (top == NULL) {
                        organizeList(top, end, tempData);
                    } else {
                        addPerson(end, tempData);
                    }
                }
                outFile.close();
                return 0;
            } else {
                return -1;
            }

        } else {
            outFile.open(fileName, ios::in | ios::binary);

            if (outFile) {
                tableData tempData;
                while (outFile.read((char *) &tempData, TABLE_DATA_SIZE)) {
                    if (top == NULL) {
                        organizeList(top, end, tempData);
                    } else {
                        addPerson(end, tempData);
                    }
                }
                outFile.close();
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
 * ‘”Õ÷»ﬂ ƒÀﬂ ¬€«Œ¬¿ ‘”Õ ÷»» «¿œ»—» ¬ ‘¿…À
 */
void saveFileInterface() {
    cleanStatusBar();
    if (listHead != NULL) {
        unsigned saveChange = menuInterface(saveFileMessage, saveFileMessageItemsCount);
        if ((!saveChange) && (strlen(openFileName) > 1)) {
            cleanStatusBar();
            SetColor(12, 0);
            printf("REWRITE?:");
            SetColor(7, 0);
            if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                cleanStatusBar();
                if (!saveFile(listHead, openFileName)) {
                    printf("FILE SAVED");
                } else {
                    printf("FILE NOT SAVED!");
                }
            }
        } else if (saveChange == 1) {
            cleanStatusBar();
            if (strlen(openFileName) < 3) {
                printf("FILE WILL BE CREATE");
            }
            char newFileName[MAX_STR_LENGTH];
            printf("ENTER FILE NAME(*.bin - binary, *.txt - text): ");
            cin.getline(newFileName, MAX_STR_LENGTH);
            if (cin.fail()) {             //œ–» œ≈–≈œŒÀÕ≈Õ»» ¡”‘≈–¿ ¬’ŒƒÕŒ√Œ œŒ“Œ ¿
                cin.clear();            //—¡–Œ— Œÿ»¡ » œŒ“Œ ¿
                cin.ignore(1000, '\n');   //»√ÕŒ–»–Œ¬¿Õ»≈ Œ—“¿¬ÿ»’—ﬂ ¬ œŒ“Œ ≈ —»Ã¬ŒÀŒ¬
            }
            if (!saveFile(listHead, newFileName)) {
                printf("FILE SAVED");
                strcpy(openFileName, newFileName);
            } else {
                printf("FILE NOT SAVED!");
            }

        } else if (saveChange == 27) {
            return;
        }
    } else {
        emptyMessage();
    }
}

/*
 * ‘”Õ÷»ﬂ ƒÀﬂ ¬€«Œ¬¿ ‘”Õ ÷»» «¿ √–”« » ‘¿…À¿
 */
void loadFileInterface() {
    SetColor(12, 0);
    printf("DO YOU WANT OPEN FILE(CURRENT DATA WILL BE CLEAR)?");
    SetColor(7, 0);
    unsigned loadChange = menuInterface(acceptMessage, acceptMessageItemsCount);
    if (loadChange == 1) {
        deleteList(listHead);
        cleanStatusBar();

        printf("ENTER FILE NAME: ");
        cin.getline(openFileName, MAX_STR_LENGTH);
        if (cin.fail()) {             //œ–» œ≈–≈œŒÀÕ≈Õ»» ¡”‘≈–¿ ¬’ŒƒÕŒ√Œ œŒ“Œ ¿
            cin.clear();            //—¡–Œ— Œÿ»¡ » œŒ“Œ ¿
            cin.ignore(1000, '\n');   //»√ÕŒ–»–Œ¬¿Õ»≈ Œ—“¿¬ÿ»’—ﬂ ¬ œŒ“Œ ≈ —»Ã¬ŒÀŒ¬
        }
        if (!loadFile(listHead, listEnd, openFileName)) {
            printf("FILE IS OPENED!");
        } else {
            printf("FILE NOT OPENED!");
        }
    }
};


/*
 * ‘”Õ ÷»ﬂ Œ–√¿Õ»«¿÷»» Œ◊≈–≈ƒ»
 * œŒ«¬ŒÀﬂ≈“ ƒŒ¡¿¬»“‹ “ŒÀ‹ Œ œ≈–¬€… ›À≈Ã≈Õ“
 * ¬Œ«¬–¿Ÿ¿≈“:
 *            0 - ¬ —À”◊¿≈ ƒŒ¡¿¬À≈Õ»ﬂ
 *            1 - ¬ —À”◊¿≈ Õ≈ œ”—“Œ√Œ —œ»— ¿
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
 * ‘”Õ ÷»ﬂ ƒŒ¡¿¬À≈Õ»ﬂ ›À≈Ã≈Õ“¿ ¬ Œ◊≈–≈ƒ‹
 * ƒŒ¡¿¬Àﬂ≈“ ›À≈Ã≈Õ“€ “ŒÀ‹ Œ, ≈—À» —œ»—Œ  Õ≈ œ”—“
 * ¬Œ«¬–¿Ÿ¿≈“:
 *            0 - ¬ —À”◊¿≈ ƒŒ¡¿¬À≈Õ»ﬂ
 *            1 - ¬ —À”◊¿≈ œ”—“Œ√Œ —œ»— ¿
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

/*
 * ‘”Õ ÷»ﬂ –≈ƒ¿ “»–Œ¬¿Õ»≈ «¿œ»—»
 * œ–» Õ¿∆¿“»»: ~ - ¬Œ«¬–¿Ÿ¿≈“ »«Ã≈Õ®ÕÕ”ﬁ —“–” “”–”
 *             ESC - —“–” “”–” ¡≈« »«Ã≈Õ≈Õ»…
 */
tableData editData(tableData mainData) {

    unsigned countOfFields = 10;
    unsigned currentField = 0, i;
    unsigned coordX = 0, coordY = 19;
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
                        coordX = 0;
                        rewriteString(coordX, coordY, FIO_LENGTH, current.fio);
                        break;
                    }
                    case 1: {
                        coordX = 22;
                        current.personalNumber = checkNumeral(coordX, coordY, current.personalNumber, 6);
                        break;
                    }
                    case 2: {
                        coordX = 30;
                        current.birth_year = checkNumeral(coordX, coordY, current.birth_year, 4);
                        break;
                    }
                    case 3: {
                        coordX = 36;
                        current.sex = checkNumeral(coordX, coordY, current.sex, 1);
                        break;
                    }
                    case 4: {
                        coordX = 38;
                        rewriteString(coordX, coordY, PROF_LENGTH, current.prof);
                        break;
                    }
                    case 5: {
                        coordX = 50;
                        current.exp = checkNumeral(coordX, coordY, current.exp, 2);
                        break;
                    }
                    case 6: {
                        coordX = 55;
                        current.rank = checkNumeral(coordX, coordY, current.rank, 2);
                        break;
                    }
                    case 7: {
                        coordX = 60;
                        current.factoryNumber = checkNumeral(coordX, coordY, current.factoryNumber, 2);
                        break;
                    }
                    case 8: {
                        coordX = 66;
                        current.deportmentNumber = checkNumeral(coordX, coordY, current.deportmentNumber, 2);
                        break;
                    }
                    case 9: {
                        coordX = 69;
                        current.salary = (float) checkNumeral(coordX, coordY, (long int) current.salary, 7);
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
            case 96:
            case 241: {
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

/*
 * ‘”Õ ÷»ﬂ ”ƒ¿À≈Õ»ﬂ —œ»— ¿
 */
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

/*
 * ‘”Õ ÷»ﬂ ”ƒ¿À≈Õ»ﬂ ŒƒÕŒ√Œ ›À≈Ã≈Õ“¿ —œ»— ¿
 */
int deletePersonalData(list *&listHead, list *&listEnd, list *current) {
    if ((current == listHead) && (current == listEnd)) //Û‰‡ÎÂÌËÂ Â‰ËÌÒÚ‚ÂÌÌÓ„Ó ˝ÎÂÏÂÌÚ‡
    {
        listHead = NULL;
        listEnd = NULL;
        delete current;
        return 0;
    } else if (current == listHead) { //ËÁ Ì‡˜‡Î‡ ÒÔËÒÍ‡

        listHead = listHead->next;
        listHead->pred = NULL;
        delete current;
        return 1;
    } else if (current == listEnd) {//Ò ÍÓÌˆ‡
        listEnd = listEnd->pred;
        listEnd->next = NULL;
        delete current;
        return 2;
    } else { //Û‰‡ÎÂÌËÂ ËÁ ÒÂÂ‰ËÌ˚
        current->pred->next = current->next;
        current->next->pred = current->pred;
        delete current;
        return 3;
    }
}

/*
 * ‘”Õ ÷»ﬂ ¬€¬Œƒ¿ ƒ¿ÕÕ€’ ¬  ŒÕ—ŒÀ‹(¬ ŒƒÕ” —“–Œ ”)
 */
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

/*
 * ‘”Õ ÷»ﬂ œ–Œ—ÃŒ“–¿ Œ◊≈–≈ƒ» — ¬Œ«ÃŒ∆ÕŒ—“‹ﬁ Õ¿¬»√¿÷»»(œŒ «¿œ»—ﬂÃ, ¿ “¿  ∆≈ œŒ —“–¿¬Õ»÷¿Ã)
 * mode:
 *      0 - ÙÛÌÍˆËˇ ‰Îˇ Û‰‡ÎÂÌËˇ ˝ÎÂÏÂÌÚÓ‚
 *      1 - ‰Îˇ ÒÓı‡ÌÂÌËˇ ‚˚‚Â‰ÂÌÌÓ„Ó ÒÔËÒÍ‡ ‚ Ù‡ÈÎ
 */
void viewList(list *&listHead, list *&listEnd, unsigned mode) {
    if (listHead != NULL) {
        list *currentL, *temp, *startDisplay;
        int i, currentNum = 1;
        startDisplay = currentL = listHead;
        short int delResult;

        while (listHead != NULL) {

            system("cls");
            temp = startDisplay;

            drawTableHead(sort_mode);

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
                        SetColor(12, 0);
                        printf("DO YOU WANT DELTE THIS DATA? \n");
                        SetColor(7, 0);

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
                        if (cin.fail()) {             //œ–» œ≈–≈œŒÀÕ≈Õ»» ¡”‘≈–¿ ¬’ŒƒÕŒ√Œ œŒ“Œ ¿
                            cin.clear();            //—¡–Œ— Œÿ»¡ » œŒ“Œ ¿
                            cin.ignore(1000, '\n');   //»√ÕŒ–»–Œ¬¿Õ»≈ Œ—“¿¬ÿ»’—ﬂ ¬ œŒ“Œ ≈ —»Ã¬ŒÀŒ¬
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

        emptyMessage();
    } else return;

}

/*
 * ‘”Õ ÷»ﬂ ¬€¬Œƒ¿ » Õ¿¬»√¿÷»» Œ—ÕŒ¬ÕŒ√Œ Ã≈Õﬁ
 * ¬Œ«¬–¿Ÿ¿≈“ ÕŒÃ≈– œ”Õ “¿ Ã≈Õﬁ ¬ œ≈–≈ƒ¿ÕÕŒÃ Ã¿——»¬≈
 */
int menu(const char **menuItems, const int itemsCount, int currentItem) {
    int i = 0;
    int centerCoorOfConsole = 40, coordX = 0, coordY = 0;
    while (1) {

        system("cls");
        for (i = 0; i < itemsCount; i++) {
            coordX = centerCoorOfConsole - (strlen(menuItems[i]) / 2);
            coordY = i + 1;

            if (i == currentItem) {
                coordX -= 6;
                gotoxy(coordX, coordY);
                //SetColor(0, 8);
                SetColor(11, 0);
                printf("--->  ");
            } else {
                gotoxy(coordX, coordY);
            }

            printf("%s", menuItems[i]);

            if (i == currentItem) {
                printf("  <---");
            }
            printf("\n");

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

/*
 * ‘”Õ ÷»ﬂ ¬€¬Œƒ¿ » Õ¿¬»√¿÷»» ƒŒœŒÀÕ»“≈À‹ÕŒ√Œ Ã≈Õﬁ(—Œ’–¿Õ≈Õ»ﬂ ¬ ‘¿…À »À» œŒƒ“¬≈–∆ƒ≈Õ»ﬂ Œœ≈–¿÷»…)
 * ¬Œ«¬–¿Ÿ¿≈“ ÕŒÃ≈– œ”Õ “¿ Ã≈Õﬁ ¬ œ≈–≈ƒ¿ÕÕŒÃ Ã¿——»¬≈
 */
int menuInterface(const char **menuItems, const int itemsCount) {
    int currentItem = 0, i = 0;
    while (1) {
        cleanPlace();
        gotoxy((40 - (strlen(menuItems[0]) / 2)), 22);
        for (i = 0; i < itemsCount; i++) {
            if (i == currentItem) {
                SetColor(12, 0);
            }
            printf("%s \n", menuItems[i]);
            SetColor(7, 0);
            gotoxy((40 - (strlen(menuItems[1]) / 2)), 23);
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
                return 27;
            }
        }
    }
}

/*
 * ‘”Õ ÷»ﬂ œ≈◊¿“» ƒŒœŒÀÕ»“≈À‹ÕŒ√Œ Ã≈Õﬁ
 * mode:
 *      0 - ‚˚‚Ó‰ËÚ ÔÛÌÍÚ "DEL - DLT";
 *      1 - ˚‚Ó‰ËÚ ÔÛÌÍÚ " ~ - SAVE";
 */
void drawHelpMenu(unsigned mode) {
    gotoxy(0, 17);
    SetColor(7, 1);

    (!mode) ?
    (SetColor(7, 1), printf("ESC - MENU "), SetColor(7, 1)) :
    (SetColor(12, 1), printf("ESC - CANC "), SetColor(7, 1));

    printf("| ENTER - SELECT |");

    (!mode) ?
    (SetColor(7, 12), printf(" DEL - DLT "), SetColor(7, 1)) :
    (SetColor(9, 14), printf(" ~ - SAVE "), SetColor(7, 1));

    printf("| UP,DOWN - NAVIGATE | <-,-> SLIDE PAGE ");
    SetColor(7, 0);

    for (int i = 0; i < 35; i++) putch('-');
    cout << "STATUS BAR";
    for (int i = 0; i < 35; i++) putch('-');
    gotoxy(0, 21);
    for (int i = 0; i < console_row_length; i++) putch('-');
    cleanStatusBar();
}

/*
 * ‘”Õ ÷»ﬂ ¬€¬Œƒ¿ ÿ¿œ » “¿¡À»÷€
 */
void drawTableHead(unsigned X, unsigned Y) {

    gotoxy(X, Y);
    printf("%s \n", sortMenu[sort_mode]);

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

/*
 * ‘”Õ ÷»ﬂ Œ◊»—“ »  ŒÕ—ŒÀ» Õ»∆≈ STATUS BAR
 */
void cleanPlace() {
    int i;
    gotoxy(0, 22);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    return;
}

/*
 * ‘”Õ ÷»ﬂ Œ◊»—“ » STATUS BAR
 */
void cleanStatusBar() {
    int i;
    gotoxy(0, 19);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    gotoxy(0, 19);
    return;
}

/*
 * ‘”Õ ÷»ﬂ »Õƒ» ¿“Œ–¿ ¬ —À”◊¿≈ œ”—“Œ√Œ —œ»— ¿
 */
void emptyMessage() {
    SetColor(14, 0);
    printf("EMPTY LIST \n");
    SetColor(7, 0);
    getch();
}

/*
 * ‘”Õ ÷»ﬂ œ–Œ¬≈– » ◊»—À¿ Õ¿ ¬¬Œƒ, — ¬Œ«ÃÀ∆ÕŒ—“‹ﬁ ¬€¡Œ–¿  ŒŒ–ƒ»Õ¿“
 * œ–» œ≈–≈ƒ¿◊≈ X < 0 » Y < 0 -  ŒŒ–ƒ»Õ¿“€ Õ≈ ”◊»“€¬¿ﬁ“—ﬂ
 * œ–» Õ¿∆¿“»» ESC - ¬Œ«–¿Ÿ¿≈“—ﬂ 0, » Õ¿◊¿À‹ÕŒ≈ «Õ¿◊≈Õ»≈ œ≈–≈ƒ¿ÕÕŒ≈ ‘”Õ ÷»» »À» 0
 */
unsigned int checkNumeral(short X, short Y, long int num, int maxDigitCount) {

    long int tempNum = num;
    int currentDigitCount, minDigitCount = 0;

    for (currentDigitCount = 0; tempNum >= 1; currentDigitCount++) {
        tempNum = tempNum / 10;
    }

    tempNum = num;

    while (1) {
        if ((X >= 0) && (Y >= 0)) {
            gotoxy(X, Y);
        }

        for (int i = 0; i < maxDigitCount + 1; i++) {
            putch(' ');
        }


        if ((tempNum) || (maxDigitCount == 1)) {
            if ((X >= 0) && (Y >= 0)) {
                gotoxy(X, Y);
            }
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

            case 13:
            case 96:
            case 241: {
                return tempNum;
            }

            case 27: {
                return num;
            }
        }

    }
}

/*
 * œ–»¬≈ƒ≈Õ»≈ —»Ã¬ŒÀŒ¬ ‘¿Ã»À»» » »Õ»÷»¿ÀŒ¬   ¬≈–’Õ≈Ã” –≈√»—“–”(”◊»“€¬¿ﬂ –”—— »≈ —»Ã¬ŒÀ€)
 */
char *strToFormat(char *str, const int length) {
    int i;
    int k;


    for (i = 0; (i < length) && (str[i] != '\0'); i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //ÂÒÎË i-Ú˚È ˝ÎÂÏÂÌÚ ÔÓ·ÂÎ ËÎË ÁÌ‡Í - ÔÓÔÛÒÍ

            continue;
        } else {
            k = str[i];
            if ((k >= -96) && (k <= -81)) {
                str[i] = k - 32;
            } else if ((k >= -32) && (k <= 0)) {
                str[i] = k - 80;
            } else {
                str[i] = toupper(str[i]);
            }
        }
    }
    //ƒÀﬂ œ–»¬≈ƒ≈Õ»ﬂ —»Ã¬ŒÀŒ¬   Õ»∆Õ≈Ã” –≈≈—“–”

    /*bool spaceCheck = true;

    for (i = 0; i < length; i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //ÂÒÎË i-Ú˚È ˝ÎÂÏÂÌÚ ÔÓ·ÂÎ ËÎË ÁÌ‡Í - ÔÓÔÛÒÍ
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

/*
 * ‘”Õ ÷»ﬂ œ–Œ¬≈– » —»Ã¬ŒÀŒ¬ Õ¿ ¬¬Œƒ, — ¬Œ«ÃÀ∆ÕŒ—“‹ﬁ ¬€¡Œ–¿  ŒŒ–ƒ»Õ¿“
 * œ–» œ≈–≈ƒ¿◊≈ X<0 » Y <0 -  ŒŒ–ƒ»Õ¿“€ Õ≈ ”◊»“€¬¿ﬁ“—ﬂ
 * œ–» Õ¿∆¿“»» ESC - ¬Œ«–¿Ÿ¿≈“—ﬂ 0 » Õ¿◊¿À‹ÕŒ≈ «Õ¿◊≈Õ»≈ —“–Œ » Õ≈ »«Ã≈Õﬂ≈“—ﬂ
 */
int rewriteString(unsigned X, unsigned Y, const int length, char *str) {

    char tempStr[length];
    strcpy(tempStr, str);
    unsigned currentPosition;

    currentPosition = strlen(str);

    while (1) {


        if ((X >= 0) && (Y >= 0)) {
            gotoxy(X, Y);
        }

        for (int i = 0; i < length - 1; i++) {
            putch(' ');
        }


        if ((X >= 0) && (Y >= 0)) {
            gotoxy(X, Y);
        }
        cout << tempStr << endl;

        switch (key = getch()) {

            case 13:
            case 96:
            case 241: {
                strToFormat(tempStr, length);
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

                if ((((key >= 65) && (key <= 90)) ||
                     ((key >= 97) && (key <= 122)) ||
                     ((key >= 128) && (key <= 175)) ||
                     ((key >= 224) && (key <= 241)) ||
                     (key == 32))
                    && (currentPosition < length - 1)) {

                    tempStr[currentPosition++] = (char) key;
                }

                break;
            }
        }
        tempStr[currentPosition] = '\0';
    }
}

/*
 * ‘”Õ ÷»ﬂ œ–Œ¬≈– » —Œ¬œ¿ƒ≈Õ»ﬂ »Õƒ»¬»ƒ”¿À‹ÕŒ√Œ ÕŒÃ≈–¿ œ–» ¬¬Œƒ≈ ƒ¿ÕÕ€’
 * ¬Œ«¬–¿Ÿ¿≈“ 1 - œ–» —Œ¬œ¿ƒ≈Õ»» ÕŒÃ≈–Œ¬, 0 - ¬ œ–Œ“»¬ÕŒÃ —À”◊¿≈
 */
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

/*
 * ‘”Õ ÷»ﬂ —Œ–“»–Œ » —œ»— ¿ œŒ  –»“≈–»ﬂÃ
 * mode:
 *      0 - ÔÓ Ù‡ÏËÎËË
 *      1 - ÔÓ ËÌ‰Ë‚Ë‰Û‡Î¸ÌÓÏÛ ÌÓÏÂÛ
 *      2 - ÔÓ ÔÓÙÙÂÒÒËË Ë Ù‡ÏËÎËË
 *      3 - ÔÓ ÌÓÏÂÛ ˆÂı‡(factory) Ë Ù‡ÏËÎËË
 *      4 - ÔÓ ÌÓÏÂÛ Û˜‡ÒÚÍ‡(deportment) Ë Ù‡ÏËÎËË
 *      5 - ÔÓ Á‡‡·ÓÚÌÓÈ ÔÎ‡ÚÂ(salary) Ë Ù‡ÏËÎËË
 *      6 - ÔÓ ÔÓÎÛ(sex) Ë Ù‡ÏËÎËË
 *      7 - ÔÓ ÔÓÙÙÂÒÒËË Ë ‡Áˇ‰Û
 */
int sort(list *&head, list *&end, short int mode) {

    if (head != NULL) {

        switch (mode) {
            case 0: {
                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {
                        if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;
                        }
                    }
                }
                return mode;
            }

            case 1: {
                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {
                        if (temp1->inf.personalNumber > temp2->inf.personalNumber) {
                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;
                        }
                    }
                }
                return mode;
            }

            case 2: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (strcmp(temp1->inf.prof, temp2->inf.prof) > 0) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (strcmp(temp1->inf.prof, temp2->inf.prof) == 0) {
                            if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 3: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (temp1->inf.factoryNumber > temp2->inf.factoryNumber) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (temp1->inf.factoryNumber == temp2->inf.factoryNumber) {
                            if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 4: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (temp1->inf.deportmentNumber > temp2->inf.deportmentNumber) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (temp1->inf.deportmentNumber == temp2->inf.deportmentNumber) {
                            if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 5: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (temp1->inf.salary > temp2->inf.salary) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (temp1->inf.salary == temp2->inf.salary) {
                            if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 6: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (temp1->inf.sex > temp2->inf.sex) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (temp1->inf.sex == temp2->inf.sex) {
                            if (strcmp(temp1->inf.fio, temp2->inf.fio) > 0) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 7: {

                list *temp1, *temp2;
                tableData tempData;

                temp1 = temp2 = NULL;

                for (temp1 = head; temp1->next != NULL; temp1 = temp1->next) {
                    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {

                        if (strcmp(temp1->inf.prof, temp2->inf.prof) > 0) {

                            tempData = temp1->inf;
                            temp1->inf = temp2->inf;
                            temp2->inf = tempData;

                        } else if (strcmp(temp1->inf.prof, temp2->inf.prof) == 0) {
                            if (temp1->inf.rank > temp2->inf.rank) {
                                tempData = temp1->inf;
                                temp1->inf = temp2->inf;
                                temp2->inf = tempData;
                            }
                        }
                    }
                }
                return mode;
            }

            case 27: {
                return -2;
            }
        }
    } else {
        emptyMessage();
        return -1;
    }
}

/*
 * ‘”Õ ÷»ﬂ ƒÀﬂ œŒ»— ¿ ƒ¿ÕÕ€’ œŒ  Àﬁ◊≈¬ŒÃ” œŒÀﬁ
 * ¬Œ«¬–¿Ÿ¿≈“ 1 - ¬ —À”◊¿≈ œ”—“Œ√Œ —œ» ¿
 */
int searchData(list *&head, short int mode) {
    if (head == NULL) {
        emptyMessage();
        return 1;
    }
    list *temp, *tempHead, *tempEnd;
    tempHead = tempEnd = NULL;

    bool searchResult = false;

    cleanStatusBar();
    switch (mode) {
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
            long int tempNumber = checkNumeral(11, 19, 0, 6);
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
            long int tempNumber = checkNumeral(11, 19, 0, 2);
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
            long int tempNumber = checkNumeral(11, 19, 0, 2);
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
