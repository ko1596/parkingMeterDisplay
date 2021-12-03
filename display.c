#include "display.h"

void* display(void* data){
	char *str = (char*) data; // 取得輸入資料
	system("killall gst-launch-1.0");

	char command[1024] = "gst-launch-1.0 -q filesrc location=";
	strcat(command, str);
	strcat(command, ".png ! pngdec ! imagefreeze ! videoconvert ! autovideosink");
	printf("%s\n",command);
	system(command);
	pthread_exit(NULL); // 離開子執行緒
}
