#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
/*
 * STRUCTURES AND TYPES
 */
const int mainMenuItemsCount = 10;
const char *mainMenu[mainMenuItemsCount] = {
        "„€‚ˆ’œ „€›…  €—…Œ",
        "‘Œ’…’œ ˆ …„€Š’ˆ‚€’œ —……„œ",
        "‘’ˆ‚€’œ —……„œ",
        "ˆ‘Š ˆ„ˆ‚ˆ„“€‹œ›•/ƒ“‚›• „€›•",
        "‘•€ˆ’œ „€…› ‚ ”€‰‹",
        "‡€ƒ“‡ˆ’œ „€›… ˆ‡ ”€‰‹€",
        "€‘—…’ ‘…„…‰ ‡€‹€’›  “—€‘’Š€Œ",
        "ƒ€ˆ‡‚€’œ —……„œ",
        "‚›•„",
        "GET_KEY"
};


const int acceptMessageItemsCount = 2;
const char *acceptMessage[acceptMessageItemsCount] = {
        "’Œ…ˆ’œ",
        "„’‚…„ˆ’œ"
};

const int saveFileMessageItemsCount = 2;
const char *saveFileMessage[saveFileMessageItemsCount] = {
        "‘•€ˆ’œ ‚ ’…Š™ˆ‰ ”€‰‹",
        "‘•€ˆ’œ ‚ „“ƒ‰ ”€‰‹"
};

const int exitMessageItemsCount = 2;
const char *exitMessage[exitMessageItemsCount] = {
        "‘•€ˆ’œ ˆ ‚›‰’ˆ",
        "‚›‰’ˆ …‡ ‘•€…ˆŸ"
};

const int searchMenuItemsCount = 5;
const char *searchMenu[searchMenuItemsCount] = {
        "ˆ‘Š €’ˆŠ€  ”€Œˆ‹ˆˆ",
        "ˆ‘Š €’ˆŠ€  …‘€‹œŒ“ Œ…“",
        "‚›Š€ €’ˆŠ‚  €‡Ÿ„“",
        "‚›Š€ €’ˆŠ‚  # –…•€",
        "‚›Š€ €’ˆŠ‚  # “—€‘’Š€"
};


const int sortMenuItemsCount = 8;
const char *sortMenu[sortMenuItemsCount] = {
        "‘’ˆ‚Š€  ”€Œˆ‹ˆˆ",
        "‘’ˆ‚Š€  …‘€‹œŒ“ Œ…“",
        "‘’ˆ‚Š€  ”…‘‘ˆˆ",
        "‘’ˆ‚Š€  # –…•“",
        "‘’ˆ‚Š€  # “—€‘’Š€",
        "‘’ˆ‚Š€  €‡Œ…“ ‡€‹€’›",
        "‘’ˆ‚Š€  ‹‚Œ“ ˆ‡€Š“",
        "‘’ˆ‚Š€  ”. €‡Ÿ„“"
};

const unsigned short int deportment_count = 10;
const unsigned short int rank_count = 3;

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

void registerOfWorkers(list *head);

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
                        printf("\n„€›… „€‚‹…›");
                        getch();
                    }
                } else {
                    printf("…•„ˆŒ €ˆ‡‚€’œ —……„œ!");
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
                 int sortMode = menu(sortMenu, sortMenuItemsCount);

                if ((sort_mode = sort(listHead, listEnd, sortMode)) >= 0) {
                    viewList(listHead, listEnd, 0);
                }
                break;
            }


            case 3: {
                int searchMode = menu(searchMenu, searchMenuItemsCount);
                searchData(listHead, searchMode);
                getch();
                break;
            }


            case 4: {
                saveFileInterface();
                getch();
                break;
            }


            case 5: {
                loadFileInterface();
                getch();
                sort_mode = sort(listHead, listEnd);
                break;
            }

            

            case 6: {
                if (listHead != NULL){
                    printf("”€‰‹ ‘ „€›Œˆ “„…’ ……‡€ˆ‘€, „‹†ˆ’œ?");
                    if (menuInterface(acceptMessage,acceptMessageItemsCount)){
                        registerOfWorkers(listHead);
                    } else {
                        printf("‡€ˆ‘œ ’Œ……€");
                    }
                } else {
                    emptyMessage();
                }
                getch();
                break;
            }


            case 7: {
                if (listHead == NULL) {
                    if (!organizeList(listHead, listEnd, newRecord())) {
                        printf("\n„€›… „€‚‹…›! —……„œ ƒ€ˆ‡‚€€!");
                        getch();
                    }
                } else {
                    printf("\n—……„œ “†… ƒ€ˆ‡‚€€, ˆ‘„‡“‰’… ”“Š–ˆ „€‚‹…ˆŸ");
                    getch();
                }
                break;
            }


            case 9: {
                readTheKey();
                getch();
                break;
            }


            case 8:
            case 27: {
                printf("‚›‰’ˆ?");
                if (listHead != NULL) {
                    unsigned exitChange = menuInterface(exitMessage, exitMessageItemsCount);

                    if (exitChange == 0) {
                        cleanStatusBar();
                        SetColor(12, 0);
                        printf("……‡€ˆ‘€’œ ”€‰‹?:");
                        SetColor(7, 0);
                        if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                            cleanStatusBar();
                            if (!saveFile(listHead, openFileName)) {
                                printf("”€‰‹ ‘•€…");
                            } else {
                                printf("”€‰‹ … ‘•€…!");
                            }
                            getch();
                        }
                    }
                    deleteList(listHead);
                    exit(0);

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

/*”ã­ªæ¨ï ¯®§¨æ¨®­¨à®¢ ­¨ï ªãàá®à  ¢ ª®­á®«¨*/
void gotoxy(short x, short y) {
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

/*”ã­ªæ¨ï ¢ë¡®à  æ¢¥â  â¥ªáâ  ¨ ä®­  ¢ ª®­á®«¨*/
void SetColor(int text, int background) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD) ((background << 4) | text));
}

/*
 * ”ã­ªæ¨ï ¯à®¢¥àª¨ ª®¤  ª« ¢¨è
 */
void readTheKey() {
    char key2;
    while (int key = getch()) {
        key2 = key;
        cout << key << " = " << key2 << endl;
        if (key == 13) {
            printf("Š…–");
            return;
        }
    }
}


/*
 * ”“Š–ˆŸ „‹Ÿ ‡€‹…ˆŸ „€›• ‘’“Š’“› ‹…Œ…’€
 * ‚‡‚€™€…’ ‡€‹…“ ‘’“Š’““
 * …‘‹ˆ „€›… ‹Ÿ … ‚‚…„…›:
        ’…Š‘’‚… == "\0":
        —ˆ‘‹‚… == 0;
 */
tableData newRecord() {


    tableData newElement;

    system("cls");
    printf("‚‚…„ˆ’… „€›… ˆ‹ˆ €†Œˆ’… ESC „‹Ÿ ‚‡‚€’€ ‚ ‘‚… Œ…: \n");
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
            printf("‡€ˆ‘œ ‘ ’€ŠˆŒˆ Œ…Œ “†… ‘“™…‘’‚“…’!");
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
    printf("RANK(1-%d): ", rank_count);
    coordX = 11;
    short int rank = 0;
    while ((rank < 1) || (rank > 3)) {
        rank = checkNumeral(coordX, coordY, 0, 1);
    }
    newElement.rank = rank;
    coordY++;

    gotoxy(0, coordY);
    printf("FACTORY #: ");
    coordX = 11;
    newElement.factoryNumber = checkNumeral(coordX, coordY, 0);
    coordY++;

    gotoxy(0, coordY);
    printf("DEPORTMENT #(1-%d): ", deportment_count);
    coordX = 19;
    short int deportment = 0;
    while ((deportment < 1) || (deportment > 10)) {
        deportment = checkNumeral(coordX, coordY, 0, 2);
    }
    newElement.deportmentNumber = deportment;
    coordY++;

    gotoxy(0, coordY);
    printf("SALARY: ");
    coordX = 8;
    newElement.salary = (float) checkNumeral(coordX, coordY, 0, 7);

    return newElement;
}

/*
 * ”“Š–ˆŸ ‘•€…ˆŸ —……„ˆ ‚ ”€‰‹
 * mode:
    * 0 - â¥ªáâ®¢ë© ä ©« ¨«¨ ¥á«¨ ä ©« ¨¬¥¥â à áè¨à¥­¨¥ ".txt"
        * ‘‹… ’…Š‘’‚›• ‹…‰ „€‚‹Ÿ…’ ‘ˆŒ‚‹ '\n'
        * ‘‹… —ˆ‘‹‚›• " "

    * 1 - ¡¨­ à­ë© ä ©« ¨«¨ ¥á«¨ ä ©« ¨¬¥¥â à áè¨à¥­¨¥ ".bin"
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
 * ”“Š–ˆŸ ‡€ƒ“‡Šˆ —……„ˆ ˆ‡ ”€‰‹€
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
 * ”“–ˆŸ „‹Ÿ ‚›‡‚€ ”“Š–ˆˆ ‡€ˆ‘ˆ ‚ ”€‰‹
 */
void saveFileInterface() {
    cleanStatusBar();
    if (listHead != NULL) {
        unsigned saveChange = menuInterface(saveFileMessage, saveFileMessageItemsCount);
        if ((!saveChange) && (strlen(openFileName) > 1)) {
            cleanStatusBar();
            SetColor(12, 0);
            printf("……‡€ˆ‘€’œ?");
            SetColor(7, 0);
            if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                cleanStatusBar();
                if (!saveFile(listHead, openFileName)) {
                    printf("”€‰‹ ‘•€…");
                } else {
                    printf("”€‰‹ … ‘•€…!");
                }
            }
        } else if (saveChange == 1) {
            cleanStatusBar();
            if (strlen(openFileName) < 3) {
                printf("”€‰‹ “„…’ ‘‡„€");
            }
            char newFileName[MAX_STR_LENGTH];
            printf("‚‚…„ˆ’… ˆŒŸ ”€‰‹€(*.bin - binary, *.txt - text): ");
            cin.getline(newFileName, MAX_STR_LENGTH);
            if (cin.fail()) {             //ˆ ……‹…ˆˆ “”…€ ‚•„ƒ ’Š€
                cin.clear();            //‘‘ ˜ˆŠˆ ’Š€
                cin.ignore(1000, '\n');   //ˆƒˆ‚€ˆ… ‘’€‚˜ˆ•‘Ÿ ‚ ’Š… ‘ˆŒ‚‹‚
            }
            if (!saveFile(listHead, newFileName)) {
                printf("”€‰‹ ‘•€…");
                strcpy(openFileName, newFileName);
            } else {
                printf("”€‰‹ … ‘•€…!");
            }

        } else if (saveChange == 27) {
            return;
        }
    } else {
        emptyMessage();
    }
}

/*
 * ”“–ˆŸ „‹Ÿ ‚›‡‚€ ”“Š–ˆˆ ‡€Šƒ“‡Šˆ ”€‰‹€
 */
void loadFileInterface() {
    SetColor(12, 0);
    printf("’…Š“™ˆ… „€›… “„“’ ’…Ÿ›, •’ˆ’… ‹ˆ ‚› „‹†ˆ’œ?");
    SetColor(7, 0);
    unsigned loadChange = menuInterface(acceptMessage, acceptMessageItemsCount);
    if (loadChange == 1) {
        deleteList(listHead);
        cleanStatusBar();

        printf("‚‚…„ˆ’… ˆŒŸ ”€‰‹€: ");
        cin.getline(openFileName, MAX_STR_LENGTH);
        if (cin.fail()) {             //ˆ ……‹…ˆˆ “”…€ ‚•„ƒ ’Š€
            cin.clear();            //‘‘ ˜ˆŠˆ ’Š€
            cin.ignore(1000, '\n');   //ˆƒˆ‚€ˆ… ‘’€‚˜ˆ•‘Ÿ ‚ ’Š… ‘ˆŒ‚‹‚
        }
        if (!loadFile(listHead, listEnd, openFileName)) {
            printf("”€‰‹ ’Š›’");
        } else {
            printf("… “„€‹‘œ ’Š›’œ ”€‰‹!");
        }
    }
};


/*
 * ”“Š–ˆŸ ƒ€ˆ‡€–ˆˆ —……„ˆ
 * ‡‚‹Ÿ…’ „€‚ˆ’œ ’‹œŠ …‚›‰ ‹…Œ…’
 * ‚‡‚€™€…’:
 *            0 - ‚ ‘‹“—€… „€‚‹…ˆŸ
 *            1 - ‚ ‘‹“—€… … “‘’ƒ ‘ˆ‘Š€
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
 * ”“Š–ˆŸ „€‚‹…ˆŸ ‹…Œ…’€ ‚ —……„œ
 * „€‚‹Ÿ…’ ‹…Œ…’› ’‹œŠ, …‘‹ˆ ‘ˆ‘Š … “‘’
 * ‚‡‚€™€…’:
 *            0 - ‚ ‘‹“—€… „€‚‹…ˆŸ
 *            1 - ‚ ‘‹“—€… “‘’ƒ ‘ˆ‘Š€
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
 * ”“Š–ˆŸ …„€Š’ˆ‚€ˆ… ‡€ˆ‘ˆ
 * ˆ €†€’ˆˆ: ~ - ‚‡‚€™€…’ ˆ‡Œ…ğ“ ‘’“Š’““
 *             ESC - ‘’“Š’““ …‡ ˆ‡Œ……ˆ‰
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
 * ”“Š–ˆŸ “„€‹…ˆŸ ‘ˆ‘Š€
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
 * ”“Š–ˆŸ “„€‹…ˆŸ „ƒ ‹…Œ…’€ ‘ˆ‘Š€
 */
int deletePersonalData(list *&listHead, list *&listEnd, list *current) {
    if ((current == listHead) && (current == listEnd)) //ã¤ «¥­¨¥ ¥¤¨­áâ¢¥­­®£® í«¥¬¥­â 
    {
        listHead = NULL;
        listEnd = NULL;
        delete current;
        return 0;
    } else if (current == listHead) { //¨§ ­ ç «  á¯¨áª 

        listHead = listHead->next;
        listHead->pred = NULL;
        delete current;
        return 1;
    } else if (current == listEnd) {//á ª®­æ 
        listEnd = listEnd->pred;
        listEnd->next = NULL;
        delete current;
        return 2;
    } else { //ã¤ «¥­¨¥ ¨§ á¥à¥¤¨­ë
        current->pred->next = current->next;
        current->next->pred = current->pred;
        delete current;
        return 3;
    }
}

/*
 * ”“Š–ˆŸ ‚›‚„€ „€›• ‚ Š‘‹œ(‚ „“ ‘’Š“)
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
 * ”“Š–ˆŸ ‘Œ’€ —……„ˆ ‘ ‚‡Œ†‘’œ €‚ˆƒ€–ˆˆ( ‡€ˆ‘ŸŒ, € ’€Š †…  ‘’€‚ˆ–€Œ)
 * mode:
 *      0 - äã­ªæ¨ï ¤«ï ã¤ «¥­¨ï í«¥¬¥­â®¢
 *      1 - ¤«ï á®åà ­¥­¨ï ¢ë¢¥¤¥­­®£® á¯¨áª  ¢ ä ©«
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
                        printf("•’ˆ’… ‹ˆ ‚› “„€‹ˆ’œ ’“ ‡€ˆ‘œ? \n");
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
                        printf("‚‚…„ˆ’… ˆŒŸ ”€‰‹€: ");
                        char file_name[MAX_STR_LENGTH];
                        char default_name[MAX_STR_LENGTH + 11] = "selection_";
                        cin.getline(file_name, MAX_STR_LENGTH);
                        if (cin.fail()) {             //ˆ ……‹…ˆˆ “”…€ ‚•„ƒ ’Š€
                            cin.clear();            //‘‘ ˜ˆŠˆ ’Š€
                            cin.ignore(1000, '\n');   //ˆƒˆ‚€ˆ… ‘’€‚˜ˆ•‘Ÿ ‚ ’Š… ‘ˆŒ‚‹‚
                        }
                        strcat(default_name, file_name);

                        if (!saveFile(listHead, default_name)) {
                            printf("‚›Š€ ‘•€…€");
                        } else {
                            printf("‚›Š€ … ‘•€…€!");
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
 * ”“Š–ˆŸ ‚›‚„€ ˆ €‚ˆƒ€–ˆˆ ‘‚ƒ Œ…
 * ‚‡‚€™€…’ Œ… “Š’€ Œ… ‚ ……„€Œ Œ€‘‘ˆ‚…
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
 * ”“Š–ˆŸ ‚›‚„€ ˆ €‚ˆƒ€–ˆˆ „‹ˆ’…‹œƒ Œ…(‘•€…ˆŸ ‚ ”€‰‹ ˆ‹ˆ „’‚…†„…ˆŸ …€–ˆ‰)
 * ‚‡‚€™€…’ Œ… “Š’€ Œ… ‚ ……„€Œ Œ€‘‘ˆ‚…
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
 * ”“Š–ˆŸ …—€’ˆ „‹ˆ’…‹œƒ Œ…
 * mode:
 *      0 - ¢ë¢®¤¨â ¯ã­ªâ "DEL - DLT";
 *      1 - ë¢®¤¨â ¯ã­ªâ " ~ - SAVE";
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
 * ”“Š–ˆŸ ‚›‚„€ ˜€Šˆ ’€‹ˆ–›
 */
void drawTableHead(unsigned X, unsigned Y) {

    gotoxy(X, Y);
    printf("%s \n", sortMenu[sort_mode]);

    for (int i = 0; i < console_row_length; i++) {
        putch('-');
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
 * ”“Š–ˆŸ —ˆ‘’Šˆ Š‘‹ˆ ˆ†… STATUS BAR
 */
void cleanPlace() {
    int i;
    gotoxy(0, 22);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    return;
}

/*
 * ”“Š–ˆŸ —ˆ‘’Šˆ STATUS BAR
 */
void cleanStatusBar() {
    int i;
    gotoxy(0, 19);
    for (i = 0; (i < (console_row_length * 2)); i++) putch(' ');
    gotoxy(0, 19);
    return;
}

/*
 * ”“Š–ˆŸ ˆ„ˆŠ€’€ ‚ ‘‹“—€… “‘’ƒ ‘ˆ‘Š€
 */
void emptyMessage() {
    SetColor(14, 0);
    printf("‘ˆ‘Š “‘’ \n");
    SetColor(7, 0);
    getch();
}

/*
 * ”“Š–ˆŸ ‚…Šˆ —ˆ‘‹€ € ‚‚„, ‘ ‚‡Œ‹†‘’œ ‚›€ Š„ˆ€’
 * ˆ ……„€—… X < 0 ˆ Y < 0 - Š„ˆ€’› … “—ˆ’›‚€’‘Ÿ
 * ˆ €†€’ˆˆ ESC - ‚‡€™€…’‘Ÿ 0, ˆ €—€‹œ… ‡€—…ˆ… ……„€… ”“Š–ˆˆ ˆ‹ˆ 0
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
 * ˆ‚…„…ˆ… ‘ˆŒ‚‹‚ ”€Œˆ‹ˆˆ ˆ ˆˆ–ˆ€‹‚ Š ‚…•…Œ“ …ƒˆ‘’“(“—ˆ’›‚€Ÿ “‘‘Šˆ… ‘ˆŒ‚‹›)
 */
char *strToFormat(char *str, const int length) {
    int i;
    int k;


    for (i = 0; (i < length) && (str[i] != '\0'); i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //¥á«¨ i-âë© í«¥¬¥­â ¯à®¡¥« ¨«¨ §­ ª - ¯à®¯ãáª

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
    //„‹Ÿ ˆ‚…„…ˆŸ ‘ˆŒ‚‹‚ Š ˆ†…Œ“ ……‘’“

    /*bool spaceCheck = true;

    for (i = 0; i < length; i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //¥á«¨ i-âë© í«¥¬¥­â ¯à®¡¥« ¨«¨ §­ ª - ¯à®¯ãáª
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
 * ”“Š–ˆŸ ‚…Šˆ ‘ˆŒ‚‹‚ € ‚‚„, ‘ ‚‡Œ‹†‘’œ ‚›€ Š„ˆ€’
 * ˆ ……„€—… X<0 ˆ Y <0 - Š„ˆ€’› … “—ˆ’›‚€’‘Ÿ
 * ˆ €†€’ˆˆ ESC - ‚‡€™€…’‘Ÿ 0 ˆ €—€‹œ… ‡€—…ˆ… ‘’Šˆ … ˆ‡Œ…Ÿ…’‘Ÿ
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
 * ”“Š–ˆŸ ‚…Šˆ ‘‚€„…ˆŸ ˆ„ˆ‚ˆ„“€‹œƒ Œ…€ ˆ ‚‚„… „€›•
 * ‚‡‚€™€…’ 1 - ˆ ‘‚€„…ˆˆ Œ…‚, 0 - ‚ ’ˆ‚Œ ‘‹“—€…
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
 * ”“Š–ˆŸ ‘’ˆŠˆ ‘ˆ‘Š€  Šˆ’…ˆŸŒ
 * mode:
 *      0 - ¯® ä ¬¨«¨¨
 *      1 - ¯® ¨­¤¨¢¨¤ã «ì­®¬ã ­®¬¥àã
 *      2 - ¯® ¯à®ää¥áá¨¨ ¨ ä ¬¨«¨¨
 *      3 - ¯® ­®¬¥àã æ¥å (factory) ¨ ä ¬¨«¨¨
 *      4 - ¯® ­®¬¥àã ãç áâª (deportment) ¨ ä ¬¨«¨¨
 *      5 - ¯® § à ¡®â­®© ¯« â¥(salary) ¨ ä ¬¨«¨¨
 *      6 - ¯® ¯®«ã(sex) ¨ ä ¬¨«¨¨
 *      7 - ¯® ¯à®ää¥áá¨¨ ¨ à §àï¤ã
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
 * ”“Š–ˆŸ „‹Ÿ ˆ‘Š€ „€›•  Š‹—…‚Œ“ ‹
 * ‚‡‚€™€…’ 1 - ‚ ‘‹“—€… “‘’ƒ ‘ˆŠ€
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
            printf("‚‚…„ˆ’… Š‹— ˆ‘Š€: ");
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
            printf("‚‚…„ˆ’… Š‹— ˆ‘Š€: ");
            long int tempNumber = checkNumeral(21, 19, 0, 6);
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
            printf("‚‚…„ˆ’… Š‹— ˆ‘Š€: ");
            long int tempNumber = checkNumeral(21, 19, 0, 2);
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
            printf("‚‚…„ˆ’… Š‹— ˆ‘Š€: ");
            long int tempNumber = checkNumeral(21, 19, 0, 2);
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
            printf("‚‚…„ˆ’… Š‹— ˆ‘Š€: ");
            long int tempNumber = checkNumeral(21, 19, 0, 2);
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
        cout << "„€›… … €‰„…›" << endl;
    }
    deleteList(tempHead);
    return 0;
}

/*
 * ”“Š–ˆŸ „‘—ğ’€ ‘…„…‰ ‡€‹€’› ˆ Š‹ˆ—…‘’‚€ €’ˆŠ‚ € “—€‘’Š…
 * ‘•€Ÿ…’ „€›… ‚ ”€‰‹ workers_register.txt
 * ‚›‚„ˆ’ ‘„…†ˆŒ… ”€‰‹€ € Š€
 */
void registerOfWorkers(list *head) {
    struct workers_register {
        double total_salary = 0, everage_salary = 0;
        unsigned int rank[3] = {0, 0, 0}, total_count_workers = 0;
    } deportments[deportment_count];

    list *temp;
    unsigned depTempNum, rankTempNum;
    for (temp = head; temp != NULL; temp = temp->next) {
        depTempNum = temp->inf.deportmentNumber - 1;
        rankTempNum = temp->inf.rank - 1;
        deportments[depTempNum].total_count_workers++;
        deportments[depTempNum].total_salary += temp->inf.salary;
        deportments[depTempNum].rank[rankTempNum]++;
    }
    system("cls");
        char out_file_name[MAX_STR_LENGTH] = "workers_register.txt";
        /*printf("ENTER FILE NAME: ");
        cin.getline(out_file_name, MAX_STR_LENGTH);
        if (cin.fail()) {             //ˆ ……‹…ˆˆ “”…€ ‚•„ƒ ’Š€
            cin.clear();            //‘‘ ˜ˆŠˆ ’Š€
            cin.ignore(1000, '\n');   //ˆƒˆ‚€ˆ… ‘’€‚˜ˆ•‘Ÿ ‚ ’Š… ‘ˆŒ‚‹‚
        }*/
        FILE *out_file = fopen(out_file_name, "wt");
        if (!out_file) {
            printf("”€‰‹ … ‘•€…");
        } else {
            for (int i = 0; i < console_row_length - 27; i++) {
                fprintf(out_file, "-");
            }
            fprintf(out_file, "\n\t|\t\t  |    EMPLOYEES    |       | ");

            fprintf(out_file, "\n DEP #  |  EVERAGE SALARY |-----------------| TOTAL |\n");
            fprintf(out_file, "\t|\t\t  |  1  |  2  |  3  |       |\n");

            for (int i = 0; i < console_row_length - 27; i++) {
                fprintf(out_file, "-");
            }
            fprintf(out_file, "\n");

            for (int i = 0; i < deportment_count; i++) {
                if (deportments[i].total_salary) {
                    deportments[i].everage_salary = deportments[i].total_salary / deportments[i].total_count_workers;
                }

                fprintf(out_file, "%7d | %14.2f | %3d | %3d | %3d | %4d   |\n", i + 1, deportments[i].everage_salary,
                        deportments[i].rank[0], deportments[i].rank[1], deportments[i].rank[2],
                        deportments[i].total_count_workers);
            }
            for (int i = 0; i < console_row_length - 27; i++) {
                fprintf(out_file, "-");
            }
            fprintf(out_file,"\n");

            fclose(out_file);
            system("copy workers_register.txt con");
            printf("‚…„Œ‘’œ ‘•€…€ ‚ ”€‰‹: workers_register.txt");
            return;
        }

}