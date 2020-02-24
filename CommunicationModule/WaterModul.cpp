#include "Block.h"

#define ADDRESS 2


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
# define GetPhDataType 11
# define GetECDataType 12
# define GetWaterLevelDataType 13

WaterModul::WaterModul(byte subaddress) : SensorModul(ADDRESS, subaddress)
{
}

void WaterModul::Refress_PH()
{
  PH = random(300);//c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetPhDataType, PH);
}

void WaterModul::Refress_EC()
{
  EC =random(300);// c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetECDataType, EC);
}

void WaterModul::Refress_Water_Temperature()
{
  Water_Temperature =random(300);// c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetTempDataType, Water_Temperature);
}

void WaterModul::Refress_Water_Level()
{
  Water_Level =random(300);// c.GetFloat(Get_Address(), Get_Subaddress(), GetPacket, GetWaterLevelDataType, Water_Level);
}

void WaterModul::RefressValues()
{
  Refress_PH();
  Refress_EC();
  Refress_Water_Temperature();
  Refress_Water_Level();
}

void WaterModul::ValuesJSON(JsonObject values)
{
  values["PH"] = PH;
  values["EC"] = EC;
  values["Water_Temperature"] = Water_Temperature;
  values["Water_Level"] = Water_Level;
}

String WaterModul::ShowModul()
{
  String ret = "";
  ret += "Address/sub: " + String(Get_Address()) + "/" + String(Get_Subaddress())+"\n";
  ret+="Enable: "+String(Is_Enabled);// csak virtuális
  return ret;
}
