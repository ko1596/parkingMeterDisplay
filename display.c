#include "display.h"

void initData(){
    status = 0;
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
    switch (status){
        case 0:
            system("python3 frame.py 1");
            break;
        case 1:
            LR_Block ? system("python3 frame.py 2") : system("python3 frame.py 3");
            break;
        case 2:
            if(LR_Select_Time == 0){
                sprintf(buf, "python3 frame.py 5 %d %d", hours, LR_Select_Time);
            }else if(LR_Select_Time == 1){
                sprintf(buf, "python3 frame.py 5 %d %d", hours, LR_Select_Time);
            }else{
                sprintf(buf, "python3 frame.py 5 %d", hours);
            }
            system(buf);
            break;
        case 3:
            LR_Payment ? system("python3 frame.py 6") : system("python3 frame.py 7");
            break;
        case 4:
            LR_Payment ? system("python3 frame.py 8") : system("python3 frame.py 9");
            break;
        default:
            break;
    }

    display();
}

void processCommand(int command) {
    switch (status)
    {
        case 0:
            if(command == 3 || command ==4) status =  1;
            break;
        case 1:
            if(command == 3) LR_Block = 0;
            else if(command == 4) LR_Block =1;
            else if(command == 1) status = 2;
            else if(command == 2) status = 0;
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
                status = 3;
            else if (command == 2)
                status = 1;
            break;
        case 3:
            if (command == 3)   LR_Payment = 0;
            else if (command == 4)   LR_Payment = 1;
            else if (command == 1) status = 4;
            else if (command == 2) status = 2;
            break;
        case 4:
            if(command == 1 || command == 2)    status = 0;
            break;
        default:
            break;
    }
}