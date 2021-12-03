#include "display.h"

void* display(void* data){
	int exit_status;
    pid_t PID = fork();
    char pidstr[1024];
	char *str = (char*) data; // 取得輸入資料
	char command[1024];
    
    switch(PID){
        case -1:
            perror("fork()");
            exit(-1);
        case 0:
            system("killall gst-launch-1.0");
			sprintf(command, "gst-launch-1.0 -q filesrc location=%s.png ! pngdec ! imagefreeze ! videoconvert ! autovideosink", str);
			printf("%s\n", command);
            system(command);
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
	
	pthread_exit(NULL); // 離開子執行緒
}
