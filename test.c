#include "display.h"

void main()
{
    int input;
    initData();
    while (1){
        displayMenu();
        printf("請輸入數字：");
        scanf("%d", &input);
        processCommand(input);
    }
}