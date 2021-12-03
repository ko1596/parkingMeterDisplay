#include "display.h"

void main()
{
    char buf[50];
    pthread_t t; // 宣告 pthread 變數
    int i = 1;
    while(1){
        // if(i==8) i = 1;
        // sprintf(buf, "%02d", i);
        scanf("%s", buf);
        // display(buf);
        pthread_create(&t, NULL, display, buf); // 建立子執行緒
        i++;
        sleep(3);
    }
}