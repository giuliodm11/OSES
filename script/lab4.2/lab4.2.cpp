#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"

DeclareAlarm(a125msec); 
DeclareAlarm(a100msec);

#define K 5
int circularBuffer[K];
static int itemCount = 0;
static int alarm=0;
int error=0;
#define	Res 1


void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(115200); //115200 bps, 8N1
    
}


TASK(TaskW) {
  static int i;
  static int M=0;
  static int N=0;
  static int sensorValue;
  int size;

  Serial.print("\n[taskW]\n");
  
  
  Serial.print("itemCount: ");
  Serial.print(itemCount);
  Serial.print("\t");
  sensorValue = analogRead(A0); 
  
  if(itemCount < K){
	#ifdef Res
    GetResource(Res);
	#endif
    circularBuffer[itemCount] = sensorValue;
    Serial.print("A0: ");
    Serial.print(sensorValue);
    Serial.print("\t");
    itemCount++;
    

    if(sensorValue<10 || sensorValue>1013){
    error=1;
    }else{
    error=0;
    }
    Serial.print("error_instant:");
    Serial.print(error);
    Serial.print("\n");

  } 
  else if (itemCount>K){
    Serial.print("error_buffer");
  }
  
  // Serial.print("[taskB]\n");
  
  // static int a=0;
  
  else if (itemCount==K){
  
    size=itemCount;
  
    M=circularBuffer[0]; // massimo 
    N=circularBuffer[0]; // minimo

    Serial.print("\nMax_value");
    Serial.print(M);
    Serial.print("\t");
    Serial.print("Min_value");
    Serial.print(N);
    
    for(i=0;i<size;i++){
      


      Serial.print("\ndata:");
      Serial.print(circularBuffer[i]);
      if (circularBuffer[i]>M)
      {
        M=circularBuffer[i];
      } 
      if (circularBuffer[i]<=N)
      {
        N=circularBuffer[i];
      }
      itemCount--;
      Serial.print("\n count:");
      Serial.print(itemCount);
      Serial.print("\nMax_value");
      Serial.print(M);
      Serial.print("\t");
      Serial.print("Min_value");
      Serial.print(N);
    }

    Serial.print("\nGeneral: Max_value");
    Serial.print(M);
    Serial.print("\t");
    Serial.print("Min_value");
    Serial.print(N);
    Serial.print("\n");
    Serial.print("item:");
    Serial.print(itemCount);

    

  if (M-N>500)
    alarm=0;
  else
    alarm=1;
    
  Serial.print("\talarm: ");
  Serial.print(alarm);
  #ifdef Res
   ReleaseResource(Res);
  #endif
  }
}

TASK(TaskV)
{
  Serial.print("[taskV]\n");

  static unsigned int blink = 0;
  #ifdef Res
    GetResource(Res);
  #endif
  Serial.print("error:");
  Serial.print(error);
  Serial.print("\t");
  Serial.print("alarm:");
  Serial.print(alarm);
  Serial.print("\n");
  GetResource(Res);
  if(alarm == 1 && error == 0 ) {
    Serial.print("LOW\t");
    blink++;
    if(blink & 1) digitalWrite(13, HIGH); //odd
    else digitalWrite(13, LOW);        //even  
    
  } 
  else if(error==0 && alarm==0) {
    Serial.print("OFF\t");
    digitalWrite(13, LOW);    
  } 
  else if(error == 1) {
    Serial.print("FAST\t");
    blink++;
    if (blink%4 == 0){
      if(blink%8 == 0) digitalWrite(13, HIGH); //odd
      else digitalWrite(13, LOW);        //even
    }
  }
  #ifdef Res
    ReleaseResource(Res);
  #endif

  Serial.print("\n");
}
