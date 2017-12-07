//
// Created by ¨ª®« © on 19.11.2017.
//

#include "CP_types.h"

/*
 * ”“– ‚… —‘‹€ € ‚‚„, ‘ ‚‡‹†‘’ ‚›€ „€’
 *  ……„€—… X < 0  Y < 0 - „€’› … “—’›‚€’‘
 *  €†€’ ESC - ‚‡€™€…’‘ 0,  €—€‹… ‡€—…… ……„€… ”“– ‹ 0
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
 * ‚…„…… ‘‚‹‚ ”€‹  –€‹‚  ‚…•…“ …ƒ‘’“(“—’›‚€ “‘‘… ‘‚‹›)
 */
char *strToFormat(char *str, const int length) {
    int i;
    int k;


    for (i = 0; (i < length) && (str[i] != '\0'); i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //¥α«¨ i-βλ© ν«¥¬¥­β ―ΰ®΅¥« ¨«¨ §­ ª - ―ΰ®―γαª

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
    //„‹ ‚…„… ‘‚‹‚  †…“ ……‘’“

    /*bool spaceCheck = true;

    for (i = 0; i < length; i++) {

        if ((isspace(str[i])) || (ispunct(str[i]))) { //¥α«¨ i-βλ© ν«¥¬¥­β ―ΰ®΅¥« ¨«¨ §­ ª - ―ΰ®―γαª
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
 * ”“– ‚… ‘‚‹‚ € ‚‚„, ‘ ‚‡‹†‘’ ‚›€ „€’
 *  ……„€—… X<0  Y <0 - „€’› … “—’›‚€’‘
 *  €†€’ ESC - ‚‡€™€…’‘ 0  €—€‹… ‡€—…… ‘’ … ‡……’‘
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
 * ”“– ‚… ‘‚€„… „‚„“€‹ƒ …€  ‚‚„… „€›•
 * ‚‡‚€™€…’ 1 -  ‘‚€„… …‚, 0 - ‚ ’‚ ‘‹“—€…
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