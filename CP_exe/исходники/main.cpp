#include "CP_types.h"

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
                        printf("\n������ ���������");
                        getch();
                    }
                } else {
                    printf("���������� ����������� �������!");
                    getch();
                }
                break;
            }


            case 1: {
                if (listHead != NULL) {
                    viewList(listHead, listEnd, 0);
                } else {
                    cleanStatusBar();
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
                    printf("���� ��������� ����� �����������, ����������?");
                    if (menuInterface(acceptMessage,acceptMessageItemsCount)){
                        registerOfWorkers(listHead);
                    } else {
                        printf("������ ��������");
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
                        printf("\n������ ���������! ������� ������������!");
                        getch();
                    }
                } else {
                    printf("\n������� ��� �������������, ����������� ������� ����������");
                    getch();
                }
                break;
            }

            case 8:{
                if (listHead != NULL){
                    printf("������ �� �� �������� ������?");
                    if (menuInterface(acceptMessage,acceptMessageItemsCount)){
                        cleanStatusBar();
                        bool result = deleteList(listHead);
                        if(result) {
                            printf("������ ������");
                        } else {
                            emptyMessage();
                        }
                    } else {
                        cleanStatusBar();
                        printf("��������");
                    }
                } else {
                    emptyMessage();
                }
                getch();
                break;
            }
            case 9:
            case 27: {
            	cout << sizeof(listHead->inf) << endl;
            	cout << sizeof(listHead->next) << endl;
            	cout << sizeof(listHead->pred) << endl;
            	getch();
                printf("�����?");
                if (listHead != NULL) {
                    unsigned exitChange = menuInterface(exitMessage, exitMessageItemsCount);

                    if (exitChange == 0) {
                        cleanStatusBar();
                        SetColor(12, 0);
                        printf("������������ ����?:");
                        SetColor(7, 0);
                        if (menuInterface(acceptMessage, acceptMessageItemsCount)) {
                            cleanStatusBar();
                            if (!saveFile(listHead, openFileName)) {
                                printf("���� ��������");
                            } else {
                                printf("���� �� ��������!");
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





















