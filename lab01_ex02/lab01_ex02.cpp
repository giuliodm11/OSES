#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(115200);
}

DeclareAlarm(a500msec);
DeclareAlarm(a750msec);

TASK(TaskA)
{
    digitalWrite(13, HIGH);
    int currentMillis = millis()+1;  // Get the current time when TaskA is executed
    Serial.print("TaskA\t");
    Serial.print(currentMillis);
    Serial.print("\n");
    TerminateTask();
}

TASK(TaskB)
{
    digitalWrite(13, LOW);
    int currentMillis = millis()+1;  // Get the current time when TaskB is executed
    Serial.print("TaskB\t");
    Serial.print(currentMillis);
    Serial.print("\n");
    TerminateTask();
}

TASK(stop)
{
    CancelAlarm(a500msec);
    CancelAlarm(a750msec);
    ShutdownOS(E_OK);
    TerminateTask();
}
