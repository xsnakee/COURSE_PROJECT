//
// Created by ¨ª®« © on 19.11.2017.
//

#include "CP_types.h"

/*
 * ”“– ‘•€… —……„ ‚ ”€‰‹
 * mode:
    * 0 - β¥ªαβ®Άλ© δ ©« ¨«¨ ¥α«¨ δ ©« ¨¬¥¥β ΰ αθ¨ΰ¥­¨¥ ".txt"
        * ‘‹… ’…‘’‚›• ‹…‰ „€‚‹…’ ‘‚‹ '\n'
        * ‘‹… —‘‹‚›• " "

    * 1 - ΅¨­ ΰ­λ© δ ©« ¨«¨ ¥α«¨ δ ©« ¨¬¥¥β ΰ αθ¨ΰ¥­¨¥ ".bin"
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
 * ”“– ‡€ƒ“‡ —……„ ‡ ”€‰‹€
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
 * ”“– „‹ ‚›‡‚€ ”“– ‡€‘ ‚ ”€‰‹
 */
void saveFileInterface() {
    cleanStatusBar();
    if (listHead != NULL) {
        unsigned saveChange = menuInterface(saveFileMessage, saveFileMessageItemsCount);
        if ((!saveChange) && (strlen(openFileName) > 1)) {
            cleanStatusBar();
            SetColor(12, 0);
            printf("……‡€‘€’?");
            SetColor(7, 0);
            if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                cleanStatusBar();
                if (!saveFile(listHead, openFileName)) {
                    printf("”€‰‹ ‘•€…");
                } else {
                    printf("”€‰‹ … ‘•€…!");
                }
            }
        } else if ((saveChange == 1) || strlen(openFileName) < 2) {
            cleanStatusBar();
            if (strlen(openFileName) < 3) {
                printf("”€‰‹ “„…’ ‘‡„€ \n");
            }
            char newFileName[MAX_STR_LENGTH];
            printf("‚‚…„’…  ”€‰‹€(*.bin - binary, *.txt - text): ");
            cin.getline(newFileName, MAX_STR_LENGTH);
            if (cin.fail()) {             // ……‹… “”…€ ‚•„ƒ ’€
                cin.clear();            //‘‘  ’€
                cin.ignore(1000, '\n');   //ƒ‚€… ‘’€‚•‘ ‚ ’… ‘‚‹‚
            }
            cleanStatusBar();
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
        cleanStatusBar();
        emptyMessage();
    }
}

/*
 * ”“– „‹ ‚›‡‚€ ”“– ‡€ƒ“‡ ”€‰‹€
 */
void loadFileInterface() {
    SetColor(12, 0);
    printf("’…“™… „€›… “„“’ ’…›, •’’… ‹ ‚› „‹†’?");
    SetColor(7, 0);
    unsigned loadChange = menuInterface(acceptMessage, acceptMessageItemsCount);
    if (loadChange == 1) {
        deleteList(listHead);
        cleanStatusBar();

        printf("‚‚…„’…  ”€‰‹€: ");
        cin.getline(openFileName, MAX_STR_LENGTH);
        if (cin.fail()) {             // ……‹… “”…€ ‚•„ƒ ’€
            cin.clear();            //‘‘  ’€
            cin.ignore(1000, '\n');   //ƒ‚€… ‘’€‚•‘ ‚ ’… ‘‚‹‚
        }
        if (!loadFile(listHead, listEnd, openFileName)) {
            printf("”€‰‹ ’›’");
        } else {
            printf("… “„€‹‘ ’›’ ”€‰‹!");
        }
    }
};
