#include "display.h"

void main()
{
    int input;
    initData();
    while (1){
        
        sleep(5);
        processCommand(3);
        displayMenu();
        
        sleep(5);
        processCommand(4);
        displayMenu();
        
    }
}