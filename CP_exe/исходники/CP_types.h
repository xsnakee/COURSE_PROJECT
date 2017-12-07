#if !defined(CP_types)
#define CP_types


/*#ifndef MAIN_PROG_CP_TYPES_H
#define MAIN_PROG_CP_TYPES_H

#endif //MAIN_PROG_CP_TYPES_H*/

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
        "„€‚ˆ’œ „€›…  ‘’“„ˆŠ…",
        "‘Œ’…’œ ˆ …„€Š’ˆ‚€’œ „€›…",
        "‘’ˆ‚€’œ „€›…",
        "ˆ‘Š ˆ„ˆ‚ˆ„“€‹œ›•/ƒ“‚›• „€›•",
        "‘•€ˆ’œ „€›E ‚ ”€‰‹",
        "‡€ƒ“‡ˆ’œ „€›… ˆ‡ ”€‰‹€",
        "€‘—…’ ‘…„…‰ ‡€‹€’› ‘’“„ˆŠ‚  “—€‘’Š€Œ",
        "ƒ€ˆ‡‚€’œ ‚“ ’€‹ˆ–“",
        "—ˆ‘’ˆ’œ „€›…",
        "‚›•„"
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
    unsigned int personalNumber;
    char fio[FIO_LENGTH];
    unsigned short birth_year;
    bool sex;
    char prof[PROF_LENGTH];
    unsigned short exp;
    unsigned short rank;
    unsigned short factoryNumber;
    unsigned short deportmentNumber;
    float salary;
};

const int TABLE_DATA_SIZE = sizeof(tableData);

struct list {
    tableData inf;
    struct list *next, *pred;
};

list *listHead = NULL, *listEnd = NULL;



/*
 * FUNCTIONS PROTOTYPES
 */

//CONSOLE MANIPULATION
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

void viewList(list *&listHead, list *&end, unsigned mode = 0);


//INTERFACE

void outData(list *temp);

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



#include "CP_consmanip.cpp"
#include "CP_listmanip.cpp"
#include "CP_filemanip.cpp"
#include "CP_sort.cpp"
#include "CP_interface.cpp"
#include "CP_checks.cpp"

#endif