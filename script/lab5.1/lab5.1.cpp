#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"

DeclareAlarm(a20msec); 
DeclareAlarm(a1000msec); 

#define K 137

int circularBuffer[K];
static int itemCount = 0;
static int queue = 0;

void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(115200); //115200 bps, 8N1
    
}


// la task s deve essere attivata ogni 50 Hz = 20 ms
TASK(TaskS) {
  GetResource(Sem);

  int sensorValue = analogRead(A0);
  Serial.print("itemCount: ");
  Serial.print(itemCount);
  Serial.print(" A0: ");
  Serial.print(sensorValue);
  Serial.print("\t");

  Serial.print("head:");
  Serial.println(itemCount%K);
  Serial.print("\t\t");
  
  circularBuffer[itemCount%K] = sensorValue;
  
  itemCount++;
  
  if(itemCount%K==queue%K)
    queue++;
  Serial.print("queue: ");
  Serial.print(queue%K);
  Serial.print("\n");
  ReleaseResource(Sem);
  }
  
  
  TASK(TaskD) {
  
    static int i;
    static int RR=0;
    static int HR;
    static int Max=0;
    static int Min=0; 
    static int T;
    static int index;
    
    GetResource(Sem);
     
    Max=circularBuffer[0]; 
    Min=circularBuffer[0]; 
    
    if(itemCount > K)
      T=K;
    else
      T=itemCount;
     
    for (i=0;i<T;i++) {
    
      index=(queue+i)%K;
         
      Serial.print("data:\t ");
      Serial.print(index);
      Serial.print("\n");
    
    if (circularBuffer[index]>Max)
    
      Max=circularBuffer[index];
    
    if (circularBuffer[index]<=Min)
    
      Min=circularBuffer[index];
    }
    
    
    RR=Max-Min;
    Serial.print("\nRR:");
    Serial.print(RR);
    HR=60*100/RR;
    Serial.print("\nHR%:");
    Serial.print(HR);
    Serial.print("\n");
    ReleaseResource(Sem);
    }
