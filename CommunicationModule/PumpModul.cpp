#include "Block.h"
#define ADDRESS 6

PumpModul::PumpModul(byte subaddress): AcutuatorModul(ADDRESS, subaddress)
{
}

void PumpModul::Activate(bool ON)
{
  if (Get_Mode() != Mode_Manual)
  {
    Set_Mode(Mode_Manual);
  }
  if (ON)
  {
    //   Serial.println("bekapcsolás");
    Set_Mode(Mode_Manual);
    c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 11, 255);// bekapcsolás
  }
  else
  {
    //  Serial.println("kikapcsolás");
    Set_Mode(Mode_Manual);
    c.SetUInt16(Get_Address(), Get_Subaddress(), 4, 11, 0); // kikapcsolás
  }
}

void PumpModul::Set_Time_Interval(int t)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, t);//EZ még rosz
  _Time_Interval = t;
}

void PumpModul::SetActuatorValue(JsonObject value)
{
  bool ON = value["Value"];
  Serial.println(String(ON));
  Serial.println("Fasz");
  
  Activate(ON);
}

String PumpModul::ShowModul()
{
  String ret = "";
  ret += "Address/sub: " + String( Get_Address()) + "/" + String(Get_Subaddress()) + "\n";
  ret += "Enable: " + String(Is_Enabled); // csak virtuális
  return ret;
}
