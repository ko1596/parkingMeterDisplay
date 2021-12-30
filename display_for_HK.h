#ifndef DISPLAY_FOR_HK_H
#define DISPLAY_FOR_HK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <gst/gst.h>

#define WORK_SPACE_PATH "/home/root/display_HK"
#define FRAME_GENERATOR_PATH "python3 /home/root/display_HK/frame.py "
#define FRAME_PATH "/home/root/display_HK/frame.jpg"

/** @defgroup PrintScreen_PageStatus_group Defines Page Status
 *  Defines all possible Pages
 *  @{
 */
typedef uint8_t PrintScreen_PageStatus;

/*!< Page home page>*/
#define PRINTSCREEN_EMPTY                       ((PrintScreen_PageStatus)  0)

/*!< Page mark space selection>*/
#define PRINTSCREEN_PARKING                     ((PrintScreen_PageStatus)  1)

/*!< Page time selection>*/
#define PRINTSCREEN_SHOTTING_CARD               ((PrintScreen_PageStatus)  2)

/*!< Page payment selection>*/
#define PRINTSCREEN_SHOTTING_CARD_ONE_CARD      ((PrintScreen_PageStatus)  3)

/*!< Page display payment>*/
#define PRINTSCREEN_VERIFYING                   ((PrintScreen_PageStatus)  4)

/*!< Page display payment successful>*/
#define PRINTSCREEN_VERIFY_SUCCESS              ((PrintScreen_PageStatus)  5)

/*!< Page display payment successful>*/
#define PRINTSCREEN_VERIFY_FAIL_CARD            ((PrintScreen_PageStatus)  6)

/*!< Page display payment successful>*/
#define PRINTSCREEN_VERIFY_FAILD_VEHICLE        ((PrintScreen_PageStatus)  7)
/** @} PrintScreen_PageStatus_group */

PrintScreen_PageStatus PageStatus;

GstElement *pipeline, *jpdec, *imgf, *source, *sink, *filter;
GstBus *bus;
GstMessage *msg;
GstStateChangeReturn ret;
GstCaps *filtercaps;

/**
 * @brief Initial all data
 * 
 */
int initData(void);

int initArg(void);

int initGST(void);

int displayScreen(void);

int display(int);

int freeResources(void);

#endif