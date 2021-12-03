#include "display.h"

void* display(void* data){
	int exit_status;
    pid_t PID = fork();
    char pidstr[1024];
    
    switch(PID){
        case -1:
            perror("fork()");
            exit(-1);
        case 0:
            system("killall gst-launch-1.0");
            system("gst-launch-1.0 -q filesrc location=01.png ! pngdec ! imagefreeze ! videoconvert ! autovideosink");
            break;
        default:
            sleep(1);
            printf("%d\n",PID);
            sprintf(pidstr, "kill %d", PID);
            system(pidstr);
            wait(&exit_status);
            // WEXITSTATUS is an macro
            printf("[Parent] Child's exit status is [%d]\n", WEXITSTATUS(exit_status));
    }
	
	pthread_exit(NULL); // 離開子執行緒
}
