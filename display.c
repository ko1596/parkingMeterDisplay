#include "display.h"

int initData(void)
{
    if (initArg() || initGST())
        return -1;
    return 0;
}

int initArg(){
    PageStatus = PRINTSCREEN_PAGE_HOMEPAGE;
    hours = 1;
    LR_Block = 2;       // 0 left      1 right      2 non-select
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 2;     // 0 left      1 right      2 non-select
    displayed = 0;      // 0 close 1 open
    sprintf(parking_space_left, "%s", LEFT_SPACE_NO);
    sprintf(parking_space_right, "%s", RIGHT_SPACE_NO);
    return 0;
}

int initGST(void){
    gst_init(NULL, NULL);

    source = gst_element_factory_make ("filesrc", "source");
    sink = gst_element_factory_make ("waylandsink", "sink");
    jpdec = gst_element_factory_make ("jpegdec", "jdec");
    imgf = gst_element_factory_make ("imagefreeze", "freeze");
    filter = gst_element_factory_make ("capsfilter", "filter");
    g_assert (filter != NULL); /* should always exist */


    pipeline = gst_pipeline_new("test-pipeline");
    if (!pipeline || !source || !sink || !jpdec || !imgf) {
        g_printerr ("Not all elements could be created.\n");
        return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, jpdec, imgf, filter, sink, NULL);
    if (gst_element_link_many (source, jpdec, imgf, filter, sink, NULL) != TRUE) {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (pipeline);
        return -1;
    }

    filtercaps = gst_caps_new_simple ("video/x-raw",
               "framerate", GST_TYPE_FRACTION, 5, 1,
               NULL);

    g_object_set (G_OBJECT (filter), "caps", filtercaps, NULL);
    gst_caps_unref (filtercaps);

    /* Modify the source's properties */
    g_object_set (source, "location", IMG_PATH, NULL);
    return 0;
}

void backToHome()
{
    hours = 1;
    printf("Reset Dat.\n LR_Block: %d\n", LR_Block);
    if (PageStatus != 1)
        LR_Block = 2;   // 0 left      1 right      2 non-select
    LR_Select_Time = 2; // 0 left      1 right      2 non-select
    LR_Payment = 2;     // 0 left      1 right      2 non-select
}

void displayScreen()
{
    /* Start playing */
    ret = gst_element_set_state (pipeline, GST_STATE_READY);
    usleep(500);
    ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (pipeline);
    }
}

void displayMenu()
{

    char buf[1024];
    char temp[1024];

    memset(buf, 0, 1024);

    strcat(buf, WORK_SPACE_DIR);

    switch (PageStatus)
    {
    case PRINTSCREEN_PAGE_HOMEPAGE:
        strcat(buf, "1");
        break;
    case PRINTSCREEN_PAGE_PARK_SPACE_SELECTION:
        if (LR_Block == 0)
        {
            strcat(buf, "3");
        }
        else if (LR_Block == 1)
        {
            strcat(buf, "4");
        }
        else if (LR_Block == 2)
        {
            strcat(buf, "2");
        }
        strcat(buf, parking_space_left);
        strcat(buf, parking_space_right);
        printf("Park Space: %d\n", LR_Block);
        break;
    case PRINTSCREEN_PAGE_TIME_SELECTION:
        if (LR_Select_Time == 0)
        {
            sprintf(temp, "5 %d %d", hours, LR_Select_Time);
        }
        else if (LR_Select_Time == 1)
        {
            sprintf(temp, "5 %d %d", hours, LR_Select_Time);
        }
        else
        {
            sprintf(temp, "5 %d 2", hours);
        }
        strcat(buf, temp);
        LR_Block ? strcat(buf, parking_space_right) : strcat(buf, parking_space_left);
        printf("B LR_Block: %d\n", LR_Block);
        break;
    case PRINTSCREEN_PAGE_PAYMENT_SELECTION:
        if (LR_Payment == 0)
        {
            strcat(buf, "7");
        }
        else if (LR_Payment == 1)
        {
            strcat(buf, "8");
        }
        else if (LR_Payment == 2)
        {
            strcat(buf, "6");
        }
        printf("Payment: %d\n", LR_Payment);
        break;
    case PRINTSCREEN_PAGE_DISPLAY_PAYMENT:
        LR_Payment ? strcat(buf, "10") : strcat(buf, "9");
        break;
    case PRINTSCREEN_PAGE_DISPLAY_SUCCESSFUL:
        strcat(buf, "11");
        break;
    default:
        break;
    }
    printf("%s\n", buf);
    system(buf);
    usleep(50);
    displayScreen();
}

void processCommand(int command)
{
    switch (PageStatus)
    {
    case 0:
        if (command == 3 || command == 4)
            PageStatus = 1;
        break;
    case 1:
        if (command == 3)
        {
            LR_Block = 0;
            displayMenu();
            // usleep(BUTTON_HOVER_TIME);
            backToHome();
            PageStatus = 2;
        }
        else if (command == 4)
        {
            LR_Block = 1;
            displayMenu();
            // usleep(BUTTON_HOVER_TIME);
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
        else if (command == 4)
        {
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
        if (command == 3)
        {
            LR_Payment = 0;
            displayMenu();
            // usleep(BUTTON_HOVER_TIME);
            PageStatus = 4;
            displayMenu();
            sleep(5);
            PageStatus = 5;
            displayMenu();
            sleep(10);
            backToHome();
            PageStatus = 1;
        }
        else if (command == 4)
        {
            LR_Payment = 1;
            displayMenu();
            // usleep(BUTTON_HOVER_TIME);
            PageStatus = 4;
            displayMenu();
            sleep(5);
            PageStatus = 5;
            displayMenu();
            sleep(10);
            backToHome();
            PageStatus = 1;
        }
        else if (command == 2)
            PageStatus = 2;
        break;
    default:
        break;
    }
    displayMenu();
}