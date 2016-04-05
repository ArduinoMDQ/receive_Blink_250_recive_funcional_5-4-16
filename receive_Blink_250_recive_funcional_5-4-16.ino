// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int interrupcion = 8;
const int LED=5;
const int Relay_1=6;
const int Relay_2=7;
boolean ledON=1;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
    pinMode(Relay_1,OUTPUT);
    pinMode(Relay_2,OUTPUT);
    pinMode(interrupcion ,INPUT);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
           digitalWrite(LED,true);
           delay(100);
           digitalWrite(LED,false);
          
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
         digitalWrite(LED,true);
           delay(100);
           digitalWrite(LED,false);
           delay(100);
           digitalWrite(LED,true);
           delay(100);
           digitalWrite(LED,false);
            delay(100);
           digitalWrite(LED,true);
           delay(100);
           digitalWrite(LED,false);
        goto START_INIT;
    }
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(!digitalRead(interrupcion))            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("get data from ID: ");
        Serial.println(canId);
        
        if(canId==128){
        
          digitalWrite(LED,true);
          digitalWrite(Relay_1,true);
          delay(1000);
             digitalWrite(Relay_1,false);
          digitalWrite(LED,false);
            
        }
         if(canId==129){
         digitalWrite(Relay_2,true);
          digitalWrite(LED,true);
          delay(450);
          digitalWrite(LED,false);
          delay(100);
          digitalWrite(LED,true);
          delay(450);
          digitalWrite(LED,false);
           digitalWrite(Relay_2,false);
        }
        
         if(canId==130){
          digitalWrite(LED,true);
          delay(300);
          digitalWrite(LED,false);
          delay(50);
          digitalWrite(LED,true);
          delay(300);
          digitalWrite(LED,false);
          delay(50);
          digitalWrite(LED,true);
          delay(300);
          digitalWrite(LED,false);
      
        }
        
      }else{
       
      
      }
        
        
    }


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
