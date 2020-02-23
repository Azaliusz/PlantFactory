//---------------------------------------- com
#include "Com.h"
//#include <SoftwareSerial.h>

#define BufferSize 10
#define ModePin 5

uint8_t SendBuffer[BufferSize];
uint8_t ReqBuffer[BufferSize];

uint16_t TimeOutCoumter = 0;
uint16_t TimeOut = 10;

uint32_t lastSend;

#define RXD2 16
#define TXD2 17

void Com::Init()
{
  pinMode(5, OUTPUT);
  Serial2.begin(112500, SERIAL_8N2, RXD2, TXD2);
  lastSend = millis();
  Com::AllPacets = 0;
  Com::LostPacets = 0;
}


void SendLastBuffer()
{
   while ( lastSend + 10 > millis() );


  digitalWrite(ModePin, HIGH);
  Serial2.write(SendBuffer, BufferSize);
  Serial2.flush();
  digitalWrite(ModePin, LOW);

  lastSend = millis();
}

void Com::Send(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType )
{
  SendBuffer[0] = address;
  SendBuffer[1] = subAddress;
  SendBuffer[2] = Packet;
  SendBuffer[3] = dataType;
  
  SendLastBuffer();
}



uint8_t Com::Req()
{
  digitalWrite(ModePin, LOW);
  for (uint8_t i = 0; i < BufferSize; i++)
  {
    ReqBuffer[i] = 0;
  }

  TimeOutCoumter = millis() + 10;
  do
  {
    digitalWrite(ModePin, LOW);
  } while (Serial2.available() != BufferSize && TimeOutCoumter > millis() );

  digitalWrite(ModePin, LOW);

  if (Serial2.available() >= BufferSize)
  {
    //  client.publish("MeasurPF", "OKÉ");
    Serial2.readBytes(ReqBuffer, BufferSize);
    return 1;

  }
  return 0;
}

uint8_t ChHeader()
{
  for(int i = 0; i<4; i++)
  {
     if(SendBuffer[i] != ReqBuffer[i])
     {
        return 0;
     }
  }  
   return 1;
}

uint8_t NumOdSend = 0;

uint8_t Com:: WaitForPacker()
{
  NumOdSend = 0;
  Com::AllPacets++;
  
  if(Req() == 1 && ChHeader() == 1)
  {   
    return 1;
  }else if(Req() == 0)
  {
    Com::LostPacets++;
    Serial2.end();
    Serial2.flush();
    Serial2.begin(115200);

    
   // return -2;
    do
    {
       NumOdSend++;
       SendLastBuffer();
       Serial2.flush();
    }while(Req() == 0 && NumOdSend < 5); 
  }
   Serial2.flush();

   if(ChHeader() == 0)
   {
     Serial2.end();
     Serial2.flush();
     Serial2.begin(115200);
    return 0;
   }
  
  return 1;
}


float Com:: GetFloat(uint8_t address, uint8_t subAddress, uint8_t packet, uint8_t dataType, float last)
{
  Send(address, subAddress, packet, dataType);
  uint32_t req;
  uint8_t error = WaitForPacker();
  if ( error  == 1)
  {
    req = ReqBuffer[4] << 24 | ReqBuffer[5] << 16 | ReqBuffer[6] << 8 | ReqBuffer[7];
  }else
  {
    return error;
  }
  return (float)req / 100;
    //return last;  
}

void Com::SetUInt16(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, uint16_t parameter)
{
   SendBuffer[4] = parameter << 8;
   SendBuffer[5] = parameter;
   Send(address, subAddress, Packet, dataType);
}

void Com::SetFloat(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, float parameter)
{
  uint32_t u32 = parameter*100;
  SendBuffer[4] = u32 << 24;
  SendBuffer[5] = u32 << 16;
  SendBuffer[6] = u32 << 8;
  SendBuffer[7] = u32 ;
  Send(address, subAddress, Packet, dataType);
}

void Com::SetFloat3(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, float parameter1,float parameter2,float parameter3) // nem a legszebb de most istenem
{
  uint32_t u16 = parameter1*100;
  SendBuffer[4] = u16 << 8;
  SendBuffer[5] = u16;
  
  u16 = parameter2*100;
  SendBuffer[6] = u16 << 8;
  SendBuffer[7] = u16;

  u16 = parameter3*100;
  SendBuffer[8] = u16 << 8;
  SendBuffer[9] = u16;
  
  Send(address, subAddress, Packet, dataType);
}
