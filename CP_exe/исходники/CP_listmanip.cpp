//
// Created by ¨ª®« © on 19.11.2017.
//

#include "CP_types.h"

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
    int temp_number = current.personalNumber;

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
                        //
                        bool checkResult = false;
                        do {
                            if (checkResult){
                                SetColor(4,0);
                            }
                            current.personalNumber = checkNumeral(coordX, coordY, current.personalNumber, 6);
                            SetColor(7,0);
                        } while ((temp_number != current.personalNumber) && (checkResult = checkPersonalNumber(current.personalNumber, listHead)));
                        //
                        //current.personalNumber = checkNumeral(coordX, coordY, current.personalNumber, 6);
                        break;
                    }
                    case 2: {
                        coordX = 30;
                        do{
                            if((current.birth_year < 1940) || (current.birth_year > 2050)) {
                                SetColor(4,0);
                            }
                            current.birth_year = checkNumeral(coordX, coordY, current.birth_year, 4);
                            SetColor(7,0);
                        } while ((current.birth_year < 1940) || (current.birth_year > 2050));

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
                        do{
                            if((current.rank < 1) || (current.rank > 3)) {
                                SetColor(4,0);
                            }
                            current.rank = checkNumeral(coordX, coordY, current.rank, 1);
                            SetColor(7,0);
                        } while ((current.rank < 1) || (current.rank > 3));
                        break;
                    }
                    case 7: {
                        coordX = 60;
                        current.factoryNumber = checkNumeral(coordX, coordY, current.factoryNumber, 2);
                        break;
                    }
                    case 8: {
                        coordX = 66;

                        do{
                            if((current.deportmentNumber < 1) || (current.deportmentNumber > 10)) {
                                SetColor(4,0);
                            }
                            current.deportmentNumber = checkNumeral(coordX, coordY, current.deportmentNumber, 2);
                            SetColor(7,0);
                        } while ((current.deportmentNumber < 1) || (current.deportmentNumber > 10));

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
        if ((top == NULL) && (temp == NULL)) return 1;
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

                        if (menuInterface(acceptMessage, acceptMessageItemsCount) == 1) {
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
        cleanStatusBar();
        emptyMessage();
    } else return;

}
