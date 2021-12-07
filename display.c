#include "display.h"

void initData(){
    PageStatus = PRINTSCREEN_PAGE_HOMEPAGE;
    hours = 0;
    LR_Block = 0;       // 0 left      1 right
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 0;     // 0 left      1 right
}

void *display(void *parm){
    char command[128];

    system("killall gst-launch-1.0");
    sprintf(command, "gst-launch-1.0 -q filesrc location=%sframe.png ! pngdec ! imagefreeze ! videoconvert ! autovideosink", COMMAND_PATH);
    system(command);
    
    pthread_exit(NULL); // 離開子執行緒
}

void displayMenu() {
    
    char buf[1024];
    char temp[1024];
    pthread_t t; // 宣告 pthread 變數
  
    memset(buf, 0, 1024);

    strcat(buf, WORK_SPACE_DIR);
    
    switch (PageStatus){
        case PRINTSCREEN_PAGE_HOMEPAGE:
            strcat(buf, "1");
            break;
        case PRINTSCREEN_PAGE_PARK_SPACE_SELECTION:
            LR_Block ? strcat(buf, "3") : strcat(buf, "2");
            printf("Park Space: %d\n",LR_Block);
            break;
        case PRINTSCREEN_PAGE_TIME_SELECTION:
            if(LR_Select_Time == 0){
                sprintf(temp, "5 %d %d", hours, LR_Select_Time);
            }else if(LR_Select_Time == 1){
                sprintf(temp, "5 %d %d", hours, LR_Select_Time);
            }else{
                sprintf(temp, "5 %d", hours);
            }
            strcat(buf, temp);
            break;
        case PRINTSCREEN_PAGE_PAYMENT_SELECTION:
            LR_Payment ? strcat(buf, "7") : strcat(buf, "6");
            printf("Payment: %d\n",LR_Payment);
            break;
        case PRINTSCREEN_PAGE_DISPLAY_PAYMENT:
            LR_Payment ? strcat(buf, "9") : strcat(buf, "8");
            break;
        default:
            break;
    }
    printf("%s\n", buf);
    system(buf);

    pthread_create(&t, NULL, display, NULL); // 建立子執行緒
    sleep(2);
    pthread_cancel(t); 
    pthread_join(t, NULL);
}

void processCommand(int command) {
    switch (PageStatus)
    {
        case 0:
            if(command == 3 || command ==4) PageStatus =  1;
            break;
        case 1:
            if(command == 3) LR_Block = 0;
            else if(command == 4) LR_Block =1;
            else if(command == 1) PageStatus = 2;
            else if(command == 2) PageStatus = 0;
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
                PageStatus = 1;
            break;
        case 3:
            if (command == 3)       LR_Payment = 0;
            else if (command == 4)  LR_Payment = 1;
            else if (command == 1)  PageStatus = 4;
            else if (command == 2)  PageStatus = 2;
            break;
        case 4:
            if(command == 1 || command == 2)    PageStatus = 0;
            break;
        default:
            break;
    }
}