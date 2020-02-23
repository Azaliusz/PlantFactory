//#ifndef __COM_H__
#define __COM_H__
#include "Arduino.h"


class Com
{
    //variables
  public:
  uint32_t AllPacets;
  uint32_t LostPacets;
  protected:
  private:

    //functions
  public:
    void Init();
    void Send(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType );
    uint8_t Req();
    uint8_t WaitForPacker();


    float GetFloat(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, float last);
    void SetUInt16(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, uint16_t parameter);
    void SetFloat(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, float parameter);
    void SetFloat3(uint8_t address, uint8_t subAddress, uint8_t Packet, uint8_t dataType, float parameter1, float parameter2, float parameter3);
  protected:
  private:


}; //Com
