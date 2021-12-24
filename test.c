#include "display.h"

int main ()
{
    // GstElement *pipeline, *source, *sink;
    // GstBus *bus;
    // GstMessage *msg;
    // GstStateChangeReturn ret;

    // /* Initialize GStreamer */
    // gst_init (&argc, &argv);
    
    initData();
    displayMenu();
    while (1){
        int buf;

        printf("enter command: ");
        scanf("%d", &buf);
        processCommand(buf);
        
    }
    return 0;
}