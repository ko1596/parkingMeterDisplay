#include "display.h"

void initData(void){
    PageStatus = PRINTSCREEN_PAGE_HOMEPAGE;
    hours = 1;
    LR_Block = 2;       // 0 left      1 right      2 non-select
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 2;     // 0 left      1 right      2 non-select
    displayed = 0;      // 0 close 1 open
    sprintf(parking_space_left, "%s", LEFT_SPACE_NO);
    sprintf(parking_space_right, "%s", RIGHT_SPACE_NO);
}

void backToHome(){
    hours = 1;
    printf("A LR_Block: %d\n", LR_Block);
    if(PageStatus != 1)
        LR_Block = 2;       // 0 left      1 right      2 non-select
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 2;     // 0 left      1 right      2 non-select
}

void *displayScreen(void *parm){
    void* null = (void *)parm;
    char command[128];

    system("killall gst-launch-1.0");
    sprintf(command, "gst-launch-1.0 -q filesrc location=%sframe.png ! pngdec ! imagefreeze ! videoconvert ! autovideosink", COMMAND_PATH);
    system(command);
    
    pthread_exit(NULL); // 離開子執行緒
}

void displayMenu() {

    char buf[1024];
    char temp[1024];
  
    memset(buf, 0, 1024);

    strcat(buf, WORK_SPACE_DIR);
    
    switch (PageStatus){
        case PRINTSCREEN_PAGE_HOMEPAGE:
            strcat(buf, "1");
            break;
        case PRINTSCREEN_PAGE_PARK_SPACE_SELECTION:
            if(LR_Block == 0){
                strcat(buf, "3");
            }else if(LR_Block == 1){
                strcat(buf, "4");
            }else if (LR_Block == 2){
                strcat(buf, "2");
            }
            strcat(buf, parking_space_left);
            strcat(buf, parking_space_right);
            printf("Park Space: %d\n",LR_Block);
            break;
        case PRINTSCREEN_PAGE_TIME_SELECTION:
            if(LR_Select_Time == 0){
                sprintf(temp, "5 %d %d", hours, LR_Select_Time);
            }else if(LR_Select_Time == 1){
                sprintf(temp, "5 %d %d", hours, LR_Select_Time);
            }else{
                sprintf(temp, "5 %d 2", hours);
            }
            strcat(buf, temp);
            LR_Block ? strcat(buf, parking_space_right) : strcat(buf, parking_space_left);
            printf("B LR_Block: %d\n", LR_Block);
            break;
        case PRINTSCREEN_PAGE_PAYMENT_SELECTION:
            if(LR_Payment == 0) {
                strcat(buf, "7");
            } else if (LR_Payment == 1) {
                strcat(buf, "8");
            } else if (LR_Payment == 2) {
                strcat(buf, "6");
            }
            printf("Payment: %d\n",LR_Payment);
            break;
        case PRINTSCREEN_PAGE_DISPLAY_PAYMENT:
            LR_Payment ? strcat(buf, "10") : strcat(buf, "9");
            break;
        case PRINTSCREEN_PAGE_DISPLAY_SUCCESSFUL:
            strcat(buf, "11");
            break;
        case 6:
            strcat(buf, "999");
        default:
            break;
    }
    printf("%s\n", buf);
    system(buf);
    if(displayed){
        pthread_cancel(displayThread); 
        pthread_join(displayThread, NULL);
        displayed = 1;
    }
    
    pthread_create(&displayThread, NULL, displayScreen, NULL); // 建立子執行緒
}

int processCommand(int command) {

    if(command == 5){
        PageStatus = 6;
        printf("display\n");
        displayMenu();
        return 0;
    }
    switch (PageStatus)
    {
        case 0:
            if(command == 3 || command ==4) PageStatus =  1;
            break;
        case 1:
            if(command == 3) {
                LR_Block = 0;
                displayMenu();
                sleep(1);
                backToHome();
                PageStatus = 2;
            }
            else if(command == 4) {
                LR_Block = 1;
                displayMenu();
                sleep(1);
                backToHome();
                PageStatus = 2;
            }
            break;
        case 2:
            if (command == 3)
            {
                if (hours > 0)
                    hours--;
                LR_Select_Time = 0;
            }
            else if (command == 4){
                hours++;
                LR_Select_Time = 1;
            }
            else if (command == 1)
                PageStatus = 3;
            else if (command == 2)
            {
                backToHome();
                PageStatus = 1;
            }
            break;
        case 3:
            if (command == 3)       {
                LR_Payment = 0;
                displayMenu();
                sleep(1);
                PageStatus = 4;
                displayMenu();
                sleep(5);
                PageStatus = 5;
                displayMenu();
                sleep(10);
                backToHome();
                PageStatus = 1;
            }
            else if (command == 4)  {
                LR_Payment = 1;
                displayMenu();
                sleep(1);
                PageStatus = 4;
                displayMenu();
                sleep(5);
                PageStatus = 5;
                displayMenu();
                sleep(10);
                backToHome();
                PageStatus = 1;
            }
            else if (command == 2)  PageStatus = 2;
            break;
        default:
            break;
    }
    displayMenu();
    return 0;
}