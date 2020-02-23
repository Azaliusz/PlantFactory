#include "Block.h"
#define ADDRESS 3

PowerModul::PowerModul(byte subaddress): AcutuatorModul(ADDRESS, subaddress)
{
  _Water_Temperature_Sensor_Subaddress = 0;
}

//START--------------------------------------Air_Temp------------------------------------------
void PowerModul::Set_Air_Temperature_Referenc(float air_temp_reference)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, air_temp_reference);
  _Air_Temperature_Referenc = air_temp_reference;
}

void PowerModul::Set_Air_Temperature_PID(float p, float i, float d)
{
  c.SetFloat3(Get_Address(), Get_Subaddress(), 4, 51, p, i, d);
  _Air_Temperature_P = p;
  _Air_Temperature_I = i;
  _Air_Temperature_D = d;
}

void PowerModul::Set_Air_Temperature_PID_Time(float t)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, t);
  _Air_Temperature_Referenc = t;
}

void PowerModul::Set_Air_Temperature_Sensor(byte subaddress)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, subaddress);
  _Air_Temperature_Sensor_Subaddress = subaddress;
}
//END--------------------------------------Air_Temp--------------------------------------------

//START------------------------------------Water_Temp------------------------------------------

void PowerModul::Set_Water_Temperature_Referenc(float water_temp_reference)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, water_temp_reference);
  _Water_Temperature_Referenc = water_temp_reference;
}

void PowerModul::Set_Water_Temperature_PID(float p, float i, float d)
{
  c.SetFloat3(Get_Address(), Get_Subaddress(), 4, 51, p, i, d);
  _Water_Temperature_P = p;
  _Water_Temperature_I = i;
  _Water_Temperature_D = d;
}

void PowerModul::Set_Water_Temperature_PID_Time(float t)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, t);
  _Water_Temperature_Referenc = t;
}

void PowerModul::Set_Water_Temperature_Sensor(byte subaddress)
{
  c.SetFloat(Get_Address(), Get_Subaddress(), 4, 41, subaddress);
  _Water_Temperature_Sensor_Subaddress = subaddress;
}

//END------------------------------------Water_Temp---------------------------------------------

void PowerModul::SetActuatorValue(JsonObject value){}// EZ NEM RELEVÁNS
