//
// Created by ¨ª®« © on 19.11.2017.
//

#include "CP_types.h"

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