#include "display.h"

void initData(){
    PageStatus = PRINTSCREEN_PAGE_HOMEPAGE;
    hours = 0;
    LR_Block = 0;       // 0 left      1 right
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 0;     // 0 left      1 right
}

void display(){
	int exit_status;
    pid_t PID = fork();
    char pidstr[1024];
    
    switch(PID){
        case -1:
            perror("fork()");
            exit(-1);
        case 0:
            system("killall gst-launch-1.0");
            system("gst-launch-1.0 -q filesrc location=frame.png ! pngdec ! imagefreeze ! videoconvert ! autovideosink");
            break;
        default:
            sleep(1);
            sprintf(pidstr, "kill %d", PID);
			printf("%s\n",pidstr);
            system(pidstr);
            wait(&exit_status);
            // WEXITSTATUS is an macro
            printf("[Parent] Child's exit status is [%d]\n", WEXITSTATUS(exit_status));
    }
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

    display();
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