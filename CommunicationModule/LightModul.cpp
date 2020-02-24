#include "Block.h"
#define ADDRESS 5

LightModul::LightModul(byte subaddress): AcutuatorModul(ADDRESS, subaddress)
{
}

void LightModul::Activate(int percent)
{
  if (Get_Mode() != Mode_Manual)
  {
    Set_Mode(Mode_Manual);
  }
  c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 62, percent);// bekapcsolás
  c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 11, percent);// bekapcsolás

}

void LightModul::Set_Time_Interval(int t)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, t);//EZ még rosz
  _Time_Interval = t;
}

void LightModul::SetActuatorValue(JsonObject value)
{
  int val = value["Value"];
  //Serial.println(percent);
  Activate(val);
}

String LightModul::ShowModul()
{
  String ret = "";
  ret += "Address/sub: " + String( Get_Address()) + "/" + String(Get_Subaddress()) + "\n";
  ret += "Enable: " + String(Is_Enabled); // csak virtuális
  return ret;
}
