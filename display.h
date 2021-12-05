#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

int status;
int hours;
int LR_Block;       // 0 left      1 right
int LR_Select_Time; // 0 left      1 right      2 non select 
int LR_Payment;     // 0 left      1 right

void initData(void);

void display(void);

void displayMenu(void);

void processCommand(int);