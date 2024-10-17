//
//  lab01.es1.c
//  
//
//  Created by Giulio Di Martino on 19/10/23.
//
#include <stdio.h>
#include <math.h>
#include "tpl_os.h"
int main(void)


{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

DeclareAlarm(a500msec);
DeclareAlarm(a750msec);
DeclareAlarm(stopper);
TASK(TaskA)
{
    static int contA=0;
    printf("task A:%d\r\n",contA);
    contA += 500;
    TerminateTask();
}

TASK(TaskB)
{
    static int contB=1500;
    printf("task B:%d\r\n",contB);
    contB += 750;
    
  TerminateTask();
}

TASK(stop)
{
  CancelAlarm(a500msec);
  CancelAlarm(a750msec);
  printf("Shutdown\r\n");
  ShutdownOS(E_OK);
  TerminateTask();
}
