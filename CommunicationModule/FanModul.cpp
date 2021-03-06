#include "Block.h"
#define ADDRESS 4

FanModul::FanModul(byte subaddress): AcutuatorModul(ADDRESS, subaddress)
{
}

void FanModul::Activate(bool ON)
{
  if (Get_Mode() != Mode_Manual)
  {
    Set_Mode(Mode_Manual);
  }
  if (ON)
  {
       Serial.println("bekapcsolás");
    Set_Mode(Mode_Manual);
    c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 10, 255);// bekapcsolás
  }
  else
  {
      Serial.println("kikapcsolás");
    Set_Mode(Mode_Manual);
    c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 10, 0); // kikapcsolás
  }
}

void FanModul::Set_Time_Interval(int t)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, t);//EZ még rosz
  _Time_Interval = t;
}

void FanModul::SetActuatorValue(JsonObject value)
{
  Serial.println("asdasd");
  bool ON = value["Value"];
  //Serial.println(ON);
  Activate(ON);
}

String FanModul::ShowModul()
{
  String ret = "";
  ret += "Address/sub: " + String( Get_Address()) + "/" + String(Get_Subaddress()) + "\n";
  ret += "Enable: " + String(Is_Enabled); // csak virtuális
  return ret;
}
