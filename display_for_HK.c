#include "display_for_HK.h"

int initData(void)
{
    return initArg() || initGST();
}

int initArg(){
    PageStatus = PRINTSCREEN_EMPTY;
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
    g_object_set (source, "location", FRAME_PATH, NULL);
    return 0;
}

int displayScreen(void) {
    /* Start playing */
    ret = gst_element_set_state (pipeline, GST_STATE_READY);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (pipeline);
        return -1;
    }
    usleep(500);
    ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (pipeline);
        return -1;
    }

    return 0;
}

int display(int command) {
    char buffer[1024];
    int retu;

    printf("process command: %d\n",command);

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%s%d", FRAME_GENERATOR_PATH, command);
    printf("%s\n", buffer);

    retu = system(buffer);
    if(retu == -1){
        printf("Fail to generate image.")
        return -1;
    }
    
    usleep(50);
    displayScreen();

    return 0;
}

int freeResources(void){
    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg =
        gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                   GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* Parse message */
    if (msg != NULL)
    {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg))
        {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &err, &debug_info);
            g_printerr("Error received from element %s: %s\n",
                       GST_OBJECT_NAME(msg->src), err->message);
            g_printerr("Debugging information: %s\n",
                       debug_info ? debug_info : "none");
            g_clear_error(&err);
            g_free(debug_info);
            break;
        case GST_MESSAGE_EOS:
            g_print("End-Of-Stream reached.\n");
            break;
        default:
            /* We should not reach here because we only asked for ERRORs and EOS */
            g_printerr("Unexpected message received.\n");
            break;
        }
        gst_message_unref(msg);
    }

    /* Free resources */
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}