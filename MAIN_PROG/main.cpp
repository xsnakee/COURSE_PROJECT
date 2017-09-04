#include <iostream>
#include <conio.h>
#include "1.h"
using namespace std;
int readTheKey();

int main() {
    std::cout << "Hello, World!" << std::endl;
    readTheKey();

    getchar();
    return 0;
}


int readTheKey(){
    while (int key=getch()) {
        cout << key << endl;
        gotoxy(1,1);
        SetColor(1,1);

        if (key == 13) {
            cout<<"Will exit";
            return 1;
        }
    }
}

