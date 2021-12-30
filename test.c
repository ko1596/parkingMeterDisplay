#include "display_for_HK.h"

int main()
{
    int buf, retu;

    retu = initData();
    if(retu == -1) {
        printf("Initial fail.\n");
        return -1;
    }

    while (1)
    {
        printf("enter command: ");
        scanf("%d", &buf);
        if(buf == 999) break;
        retu = display(buf);

        if(retu == -1) {
            printf("Display fail.\n");
            freeResources();
        }
    }

    freeResources();

    return 0;
}