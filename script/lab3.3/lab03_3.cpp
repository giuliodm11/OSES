#include <time.h>
#include <stdio.h>
#include <math.h>
#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"


DeclareAlarm(a1200msec);
DeclareAlarm(a2000msec);
DeclareAlarm(a3000msec);

DeclareMessage(Message_send_task);
DeclareMessage(Message_rec_task);



void do_things(int ms=1){
    unsigned long mul = ms * 200UL;
    unsigned long i;
    for(i=0; i<mul; i++) 
        millis();
}

void setup()
{
       Serial.begin(115200); //115200 bps, 8N1
}

TASK(TaskA){
    static int a = 0;
    static int recive_a;
    Serial.print("\n");
    Serial.print("[taskA_");
    Serial.print(a);
    Serial.print("]");
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("-->");
    while (ReceiveMessage(Message_rec_task, &recive_a) != E_OK) {
        Serial.print("[TASKA] error\n");
        }
    do_things(300);
    
    SendMessage(Message_send_task,&recive_a);
    
    
    Serial.println(millis());
    Serial.print("\n");
    a++;
        

    }


TASK(TaskB){
    static int b=0;
    Serial.print("[taskB_");
    Serial.print(b);
    Serial.print("]");
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("-->");
    do_things(600);
    Serial.println(millis());
    Serial.print("\n");
    b++;

}

TASK(TaskC){
    static int recive_c;
    static int c = 0;
    Serial.print("[taskC_");
    Serial.print(c);
    Serial.print("]");
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("\t");
    do_things(200);
    Serial.print("-->");
    while(ReceiveMessage(Message_rec_task, &recive_c) != E_OK) {
        Serial.print("[TASKC] error\n");
    }
    do_things(300);
    SendMessage(Message_send_task,&recive_c);
    Serial.print(" Finish Time : ");
    Serial.println(millis());
    Serial.print("\n");
    c++;
       
}

TASK(Initialize) {
    static int send=3;
    SendMessage(Message_send_task,&send);
    
    Serial.print("Initialize\t");
    Serial.print(send);
    
}
