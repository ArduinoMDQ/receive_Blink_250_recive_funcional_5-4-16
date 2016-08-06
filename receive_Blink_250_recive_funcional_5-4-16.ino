// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include <mcp_can.h>
#include <EEPROM.h>


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int interrupcion = 5;
const int LED=8;
const int Relay_1=7;
const int Relay_2=6;
boolean ledON=1;
//const int canId=127;
 unsigned char canId;
unsigned char ID_Hex;

unsigned char MsgUpOk[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char MsgUpEEprom[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char MsgLeido[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char  reg_control=0x00;
unsigned char  reg_config=0x00;
unsigned char  reg_5=0x00;
unsigned char  reg_4=0x00;
unsigned char  reg_3=0x00;
unsigned char  reg_2=0x00;
unsigned char  reg_1=0x00;
unsigned char  reg_0=0x00;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
    pinMode(Relay_1,OUTPUT);
    pinMode(Relay_2,OUTPUT);
    pinMode(interrupcion ,INPUT);
    digitalWrite(Relay_1,HIGH);
    digitalWrite(Relay_2,HIGH);
   // ID_Hex= EEPROM.read(0x00);
  

START_INIT:

    if(CAN_OK == CAN.begin(CAN_250KBPS,MCP_8MHz))                 
    {      
          CAN.sendMsgBuf(ID_Hex,0,8,MsgUpOk);
         
           digitalWrite(LED,HIGH);
           delay(200);
           digitalWrite(LED,LOW);
           delay(200);
            digitalWrite(LED,HIGH);
           delay(200);
           digitalWrite(LED,LOW);
           delay(200);
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
           digitalWrite(LED,HIGH);
           delay(200);
           digitalWrite(LED,LOW);
           delay(200);
            digitalWrite(LED,HIGH);
           delay(200);
           digitalWrite(LED,LOW);
           delay(200);
             digitalWrite(LED,HIGH);
       delay(1000);
          digitalWrite(LED,LOW);
           delay(200);
        goto START_INIT;
    }
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(!digitalRead(interrupcion))            // check if data coming
    
    {    
      digitalWrite(LED,HIGH);
      delay(20);
      digitalWrite(LED,LOW);
      CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
      
         canId = CAN.getCanId();
         ID_Hex= EEPROM.read(0x00);
          ID_Hex=0x80;
         int ID=int(ID_Hex);
         
      
           MsgLeido[7]=buf[7];
           MsgLeido[6]=buf[6];
           MsgLeido[5]=buf[5];
           MsgLeido[4]=buf[4];
           MsgLeido[3]=buf[3];
           MsgLeido[2]=buf[2];
           MsgLeido[1]=buf[1];
           MsgLeido[0]=buf[0];


          /////////////////////////////////////7


   if(  MsgLeido[2]==0x01){
        
          digitalWrite(LED,true);
          digitalWrite(Relay_1,false);
        
       
        
        }else{
        
          digitalWrite(Relay_1,true);
           digitalWrite(LED,false);
          
          }




          ////////////////////////////////77







           if( canId ==255){
         CAN.sendMsgBuf(ID_Hex,0,8,MsgUpOk);
          digitalWrite(LED,true);
          delay(200);
          digitalWrite(LED,false);
          delay(200);
          digitalWrite(LED,true);
          delay(200);
          digitalWrite(LED,false);
            delay(500);
             digitalWrite(LED,true);
          delay(200);
          digitalWrite(LED,false);
          delay(200);
          digitalWrite(LED,true);
          delay(200);
          digitalWrite(LED,false);
        }
     
           
       if(ID==canId){
      
           
    
      
        if(  MsgLeido[1]==0x01){
        
          digitalWrite(LED,true);
          digitalWrite(Relay_1,false);
          delay(1000);
          digitalWrite(Relay_1,true);
           digitalWrite(LED,false);
       
            MsgUpEEprom[1]=ID_Hex;
           CAN.sendMsgBuf(canId,0,8,MsgUpEEprom);
        }
         if(MsgLeido[1]==0x02){
         digitalWrite(Relay_2,true);
          digitalWrite(LED,true);
          delay(200);
           digitalWrite(LED,false);
          delay(500);
           digitalWrite(LED,true);
          delay(200);
           digitalWrite(LED,false);
           digitalWrite(Relay_2,false);
        }
        
         if(MsgLeido[1]==0x03){
          digitalWrite(LED,true);
          delay(200);
           digitalWrite(LED,false);
          delay(200);
           digitalWrite(LED,true);
          delay(200);
           digitalWrite(LED,false);
           delay(200);
           digitalWrite(LED,true);
          delay(200);
          digitalWrite(LED,false);
      
        }
          if(0xFF==MsgLeido[0]){
            
            EEPROM.write(0x00, MsgLeido[7]);// escribe en la dir 0x00 el id del dispositivo
            CAN.sendMsgBuf(canId,0,8,MsgLeido);
           
        }
       }
   
      }
        
    }
    

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
