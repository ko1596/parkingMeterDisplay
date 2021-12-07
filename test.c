#include "display.h"

void main()
{
    int input;
    initData();
    while (1){
        
        sleep(5);
        displayMenu();
        processCommand(3);
        sleep(5);
        displayMenu();
        processCommand(4);
    }
}