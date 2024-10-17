#include "tpl_os.h"
#include "Arduino.h"
#include "tpl_com.h"

DeclareAlarm(a25msec); 


#define K 5
int circularBuffer[K];
static int itemCount = 0;
static int alarm=0;
static int error=0;
#define	Res 1
static int count=0;

void setup()
{
  pinMode(A0,INPUT);
  Serial.begin(115200);
    
}


TASK(TaskZ) {
    static unsigned int blink = 0;
    Serial.print("[task V _start:]\n");


    if (count%4==0)
    {
        Serial.print("[taskS]\n");
        // static int X=0;
        
        
        Serial.print("itemCount: ");
        Serial.print(itemCount);
        Serial.print("\t");
        int sensorValue = analogRead(A0); 
        
        if(itemCount < K){
        
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
        else{
            Serial.print("error_buffer");
        }
    }
    
    
    
    if(count%5==0)
    {


        Serial.print("[taskV]\n");


        Serial.print("error:");
        Serial.print(error);
        Serial.print("\t");
        Serial.print("alarm:");
        Serial.print(alarm);
        Serial.print("\n");
    
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
        
        Serial.print("\n");
       
    }
    if (count%20==0)
    {
        Serial.print("[taskB]\n");
        // static int mesure=0;
        static int i;
        static int M=0;
        static int N=0;
        // static int a=0;
        
        int size;
        
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
        Serial.print("\n");
    }
    count++;
}
