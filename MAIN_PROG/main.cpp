#include <iostream>
#include <conio.h>
#include "prototypes.h"

using namespace std;

int readTheKey();
/*int drawInterface(char *Items);
int drawInterface(table *Items);
//*/
int main() {
    std::cout << "Hello, World!" << std::endl;
    readTheKey();

    getchar();
    return 0;
}


int readTheKey(){
    while (int key=getch()) {
        cout << key << endl;

        if (key == 13) {
            cout<<"Will exit";
            return 0;
        }
    }
}

