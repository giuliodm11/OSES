#include <time.h>
#include <stdio.h>
#include <math.h>
#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"

DeclareAlarm(a1200msec);
DeclareAlarm(a2000msec);
DeclareAlarm(a3000msec);

DeclareResource(Res);


void do_things(int ms=1){
    unsigned long mul = ms * 200UL;
    unsigned long i;
    for(i=0; i<mul; i++) 
        millis();
}

void setup()
{
       Serial.begin(115200); //115200 bps,
}

TASK(TaskA){
    static int a=0;
    Serial.print("\n");
    Serial.print("[taskA_");
    Serial.print(a);
    Serial.print("]");
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("-->");
    GetResource(Res); //definisci su oil
    do_things(300);
    Serial.println(millis());
    Serial.print("\n");
    a++;
    ReleaseResource(Res);
   
}

TASK(TaskB)
{
    static int b = 0;
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
    static int k=0;
    Serial.print("[taskC_");
    Serial.print(k);
    Serial.print("]");
    Serial.print("\t");
    Serial.print(millis());
    Serial.print("-->");
    do_things(200);
    GetResource(Res); //definisci su oil
    do_things(300);
    Serial.println(millis());
    Serial.print("\n");
    ReleaseResource(Res);
    k++;
    
    }
    
//Se si utilizza delay(ms) al posto di millis() per attendere un intervallo di tempo, il codice sarà in pausa durante la durata specificata da delay(ms), impedendo il funzionamento di altre parti del programma. Questo potrebbe influenzare il corretto funzionamento di altre operazioni o monitoraggi di tempo all'interno del sistema, portando a un comportamento non corretto o imprevisto.
//
