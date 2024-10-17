#include <time.h>
#include <stdio.h>
#include <math.h>
#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"


DeclareAlarm(a500msec);
DeclareAlarm(a100msec);
DeclareAlarm(aLED);

DeclareMessage(Message_send_taskC);
DeclareMessage(Message_rec_taskM);
DeclareMessage(Message_send_taskM);
DeclareMessage(Message_rec_taskV);

void setup()
{
    StartOS(OSDEFAULTAPPMODE);
    pinMode(13, OUTPUT);
    pinMode(12, INPUT_PULLUP);
    Serial.begin(115200);
}

TASK(TaskC)
{
  
    static int numero=0;
    static int output=0;
    static int contatore=0;
    
    numero = analogRead(A0);
    if(digitalRead(12)== HIGH){
        contatore++;
    }else if (digitalRead(12)== LOW){
        contatore=0;
    }
    
    if(contatore<10){
        
        output=numero;// switch off
    }else{
        
        output=numero+4096;
        contatore=0;
    }
    
        SendMessage(Message_send_taskC,&output);
    
    
    TerminateTask();
}

TASK(TaskM){
    static int count =0;
    static int input=0;
    static int R=0;
    static int X=0;
    static int messaggio=3;
    
    if(ReceiveMessage(Message_rec_taskM, &input) != E_OK) {
      Serial.print("Task M: Message from C is not received\n");
    }
    
    
//    if (count==0) {
//        messaggio=3;
//    }
    if (input>=1024){
        R=input-4096;
        count=1;
    }
    else if(count==1){
        X=abs(R-input);
        if (X<100) {
            messaggio=0;
        }else if(X>=100 && X<200){
            messaggio=1;
        }else if(X>200){
            messaggio=2;
        }
    }
    
    
    SendMessage(Message_send_taskM, &messaggio);
    
    Serial.print("Voltage = ");
    Serial.print(input);
    Serial.print("\t R = ");
    Serial.print(R);
    Serial.print("\t mode = ");
    Serial.println(messaggio);



    TerminateTask();
}


TASK(TaskV)
{
    static unsigned int blink = 0;
    static int data = 0;
    
 if(ReceiveMessage(Message_rec_taskV, &data) != E_OK) {
      Serial.print("Task V: Message from M not received\n");
    }
    if(data == 0) {
      digitalWrite(13, LOW);
    } else if(data == 1) {
      blink++;
      if (blink%4 == 0){
        if(blink%8 == 0) digitalWrite(13, HIGH); //odd
        else digitalWrite(13, LOW);        //even
      }
    } else if(data == 2) {
      blink++;
      if(blink & 1) digitalWrite(13, HIGH); //odd
      else digitalWrite(13, LOW);        //even  
    } else if(data == 3) {
      digitalWrite(13, HIGH);
    }
    fflush(stdout);
    TerminateTask();
}





