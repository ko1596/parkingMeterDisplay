/**
  ******************************************************************************
  * File Name          : display.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2021 Joey Ke
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DISPLAY_H
#define DISPLAY_H

  /* Includes ------------------------------------------------------------------*/
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

#define WORK_SPACE_DIR "python3 /home/root/UI_ENG_for_python/frame.py "
#define COMMAND_PATH "/home/root/UI_ENG_for_python/"
#define LEFT_SPACE_NO " 001"
#define RIGHT_SPACE_NO " 002"

/** @defgroup PrintScreen_PageStatus_group Defines Page Status
 *  Defines all possible Pages
 *  @{
 */
typedef uint8_t PrintScreen_PageStatus;

/*!< Page home page>*/
#define PRINTSCREEN_PAGE_HOMEPAGE                   ((PrintScreen_PageStatus)  0)

/*!< Page mark space selection>*/
#define PRINTSCREEN_PAGE_PARK_SPACE_SELECTION       ((PrintScreen_PageStatus)  1)

/*!< Page time selection>*/
#define PRINTSCREEN_PAGE_TIME_SELECTION             ((PrintScreen_PageStatus)  2)

/*!< Page payment selection>*/
#define PRINTSCREEN_PAGE_PAYMENT_SELECTION          ((PrintScreen_PageStatus)  3)

/*!< Page display payment>*/
#define PRINTSCREEN_PAGE_DISPLAY_PAYMENT            ((PrintScreen_PageStatus)  4)

/*!< Page display payment successful>*/
#define PRINTSCREEN_PAGE_DISPLAY_SUCCESSFUL         ((PrintScreen_PageStatus)  5)
/** @} PrintScreen_PageStatus_group */

PrintScreen_PageStatus PageStatus;

/************************************************
 * Number of hours in the current
 * the screen will display [ (hour) * 0.5 ]
 ************************************************/
int hours;  

/************************************************
 * 0: left parking space
 * 1: right parking space
 ************************************************/
int LR_Block;   

/************************************************
 * 0: light up left reduce time bottom
 * 1: light up right add time bottom
 * 2: non-selected bottom
 ************************************************/
int LR_Select_Time;

/************************************************
 * 0: Card payment
 * 1: QRCode payment
 ************************************************/
int LR_Payment;

char parking_space_left[5];
char parking_space_right[5];

/**
 * @brief display thread
 * 
 */
pthread_t displayThread; // 宣告 pthread 變數

int displayed;

GstElement *pipeline, *jpdec, *imgf, *source, *sink;
GstBus *bus;
GstMessage *msg;
GstStateChangeReturn ret;

/**
 * @brief Initial all data
 * 
 */
int initData(void);

/**
 * @brief Create a fork to display the page of the status
 * 
 */
void displayScreen(void);

/**
 * @brief Generate the page of the status "frame.png"
 * 
 */
void displayMenu(void);

/**
 * @brief Use commands to switch page status 
 * 
 * @param command           the switch command
 */
void processCommand(int);

#endif /*DISPLAY_H*/
/************************ (C) COPYRIGHT Joey Ke *****END OF FILE****/