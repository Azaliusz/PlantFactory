#include "Block.h"

//START--------------------------------------MODUL--------------------------------------------
Modul::Modul(byte address, byte subaddress)
{
  _Address = address;
  _Subaddress = subaddress;
  Is_Enabled = true;
  c.Init();
}

byte Modul::Get_Address()
{
  return _Address;
}

byte Modul::Get_Subaddress()
{
  return _Subaddress;
}

void Modul::Enable_Mode(bool enabled)
{
  //Itt kell majd egy kommunikálás
  //if(kommnikálás lezajlott jól)
  //{
  Is_Enabled = enabled;
  //  }

}

void Modul::Set_Subaddress(byte subaddress)
{
  //Kommunikácio
  //if(kommnikálás lezajlott jól)
  _Subaddress = subaddress;
  //{
  //}
}
//START--------------------------------------MODUL--------------------------------------------

//START-------------------------------------SENSOR--------------------------------------------
SensorModul::SensorModul(byte address, byte subaddress): Modul(address, subaddress) {}
void SensorModul::RefressValues() {}
void SensorModul::ValuesJSON(JsonObject doc_0 ) {}
//END---------------------------------------SENSOR--------------------------------------------

//START-----------------------------------ACTUATOR--------------------------------------------
AcutuatorModul::AcutuatorModul(byte address, byte subaddress): Modul(address, subaddress) {}

void AcutuatorModul::Set_Mode(int mode)
{
   c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 61, mode);
  _Mode = mode;
}
int AcutuatorModul::Get_Mode()
{
  return _Mode;
}

void AcutuatorModul::SetActuatorValue(JsonObject val){}
//END-------------------------------------ACTUATOR--------------------------------------------
