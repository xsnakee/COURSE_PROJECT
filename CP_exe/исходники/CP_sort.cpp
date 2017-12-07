//
// Created by ¨ª®« © on 19.11.2017.
//

#include "CP_types.h"

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
        cleanStatusBar();
        emptyMessage();
        return -1;
    }
}

/*
 * ”“Š–ˆŸ „‹Ÿ ˆ‘Š€ „€›•  Š‹—…‚Œ“ ‹
 * ‚‡‚€™€…’ 1 - ‚ ‘‹“—€… “‘’ƒ ‘ˆCŠ€
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