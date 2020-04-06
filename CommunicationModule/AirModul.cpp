#include "Block.h"

#define ADDRESS 1

// packet types
#define SystemPacket 1
#define ConfigPacket 2
#define GetPacket 3
#define SetPacket 4
#define SetCalibratePacket 5
#define GetCalibratePacket 6
#define WorkDoPacket 7

// data types system
# define OnNetworkDataType 0
# define SubbAddresGetSetDataType 1
# define NoSubbAddressDataType 2
# define ClockSynDataType 1

// data types module
# define GetTempDataType 10
# define GetHumanityDataType 11
# define GetIRDataType 12
# define GetUVDataType 13
# define GetBrrDataType 14
# define GetAIRDataType 15

AirModul::AirModul(byte subaddress) : SensorModul(ADDRESS, subaddress)
{
}

void AirModul::Refress_CO2()
{
  CO2 =  c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetAIRDataType, CO2);
}

void AirModul::Refress_Humidity()
{
 Humidity = c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetHumanityDataType, Humidity);
}

void AirModul::Refress_Air_Temperature()
{
  Air_Temperature =  c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetTempDataType, Air_Temperature);
}

void AirModul::Refress_Light()
{
  Light =  c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetBrrDataType, Light);
}

void AirModul::Refress_Light_IR()
{
  Light_IR =  c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetIRDataType, Light_IR);
}

void AirModul::Refress_Light_UV()
{
  Light_UV =  c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetUVDataType, Light_UV);
}

void AirModul::RefressValues()
{
  Refress_CO2();
  Refress_Humidity();
  Refress_Air_Temperature();
  Refress_Light();
  Refress_Light_IR();
  Refress_Light_UV();
}

void AirModul::ValuesJSON(JsonObject values)
{
  values["CO2"] = CO2;
  values["Humidity"] = Humidity;
  values["Air_Temperature"] = Air_Temperature;
  values["Light"] = Light;
  values["Light_IR"] = Light_IR;
  values["Light_UV"] = Light_UV;
}

String AirModul::ShowModul()
{
  String ret = "";
  ret += "Address/sub: " +String( Get_Address()) + "/" + String(Get_Subaddress())+"\n";
  ret+="Enable: "+String(Is_Enabled);// csak virtuális
  return ret;
}
