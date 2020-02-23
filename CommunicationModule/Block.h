#ifndef Block_h
#define Block_h

#include "Com.h"
#include "Arduino.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <LinkedList.h>


#define Mode_Manual 0
#define Mode_PID 1
#define Mode_Interval 2


class Modul //Destruktor!
{
  public:
    Modul(byte address, byte subaddress);
    //-------------------FIELDS-------------------
    bool Is_Enabled;// csak virtuális
    //-------------------GET/SET------------------
    byte Get_Address();
    byte Get_Subaddress();
    //-------------------METHODS------------------
    void Enable_Mode(bool enabled);
    void Set_Subaddress(byte subaddress);
  protected:
    Com c;
  private:
    byte _Address;
    byte _Subaddress;
};

class SensorModul: public Modul //Destruktor!
{
  public:
    SensorModul(byte address, byte subaddress);
    virtual void RefressValues();
    virtual void ValuesJSON(JsonObject modulJO);
};

class AcutuatorModul: public Modul //Destruktor!
{
  public:
    AcutuatorModul(byte address, byte subaddress);
    void Set_Mode(int mode);
    int Get_Mode();

    virtual void SetActuatorValue(JsonObject value);
  private:
    int _Mode;
};

class AirModul: public SensorModul //Destruktor!
{
  public:
    AirModul(byte subaddress);

    //MeasurementValues
    float CO2;
    float Humidity;
    float Air_Temperature;
    float Light_IR;
    float Light_UV;
    float Light;

    //RefressMeasurement
    void Refress_CO2();
    void Refress_Humidity();
    void Refress_Air_Temperature();
    void Refress_Light_IR();
    void Refress_Light_UV();
    void Refress_Light();

    virtual void RefressValues();
    virtual void ValuesJSON(JsonObject modulJO);
    //Communication
    //Minden féle kommunikációs cucc (Modnjuk ezek közül lehet hogy valami az ösben lesz)
  private:
};

class WaterModul: public SensorModul //Destruktor!
{
  public:
    WaterModul(byte subaddress);

    //MeasurementValues
    float PH;
    float EC;
    float Water_Temperature;
    float Water_Level;

    //RefressMeasurement
    void Refress_PH();
    void Refress_EC();
    void Refress_Water_Temperature();
    void Refress_Water_Level();

    virtual void RefressValues();
    virtual void ValuesJSON(JsonObject modulJO);
    //Communication
    //Minden féle kommunikációs cucc (Modnjuk ezek közül lehet hogy valami az ösben lesz)
  private:
};

class PowerModul: public AcutuatorModul //Destruktor!
{
  public:
    PowerModul(byte subaddress);

    //Air_Temperature
    void Set_Air_Temperature_Referenc(float air_temp_reference);
    void Set_Air_Temperature_PID(float p, float i, float d);
    void Set_Air_Temperature_PID_Time(float t);
    void Set_Air_Temperature_Sensor(byte subaddress);

    //Water_Temperature
    void Set_Water_Temperature_Referenc(float water_temp_reference);
    void Set_Water_Temperature_PID(float p, float i, float d);
    void Set_Water_Temperature_PID_Time(float t);
    void Set_Water_Temperature_Sensor(byte subaddress);

    virtual void SetActuatorValue(JsonObject value);

  private:
    //Air_Temperature
    float _Air_Temperature_Referenc;
    float _Air_Temperature_LastMeasure;
    float _Air_Temperature_P;
    float _Air_Temperature_I;
    float _Air_Temperature_D;
    byte _Air_Temperature_Sensor_Subaddress;

    //Water_Temperature
    float _Water_Temperature_Referenc;
    float _Water_Temperature_LastMeasure;
    float _Water_Temperature_P;
    float _Water_Temperature_I;
    float _Water_Temperature_D;
    byte _Water_Temperature_Sensor_Subaddress;


};

class FanModul: public AcutuatorModul //Destruktor!
{
  public:
    FanModul(byte subaddress);
    void Activate(bool v);
    void Set_Time_Interval(int t);

    virtual void SetActuatorValue(JsonObject value);
  private:
    int _Time_Interval;
};

class LightModul: public AcutuatorModul //Destruktor!
{
  public:
    LightModul(byte subaddress);
    void Activate(int percent);
    void Set_Time_Interval(int t);

    virtual void SetActuatorValue(JsonObject value);
  private:
    int _Time_Interval;
};

class Block //Destruktor!
{
  public:
    Block(String block_name);

    //Fields
    String Block_Name;
    int Block_ID; //Adatbázisból kapott id
    bool Enable;

    LinkedList<SensorModul*> SensorModules = LinkedList<SensorModul*>();
    LinkedList<AcutuatorModul*> AcutuatorModuls = LinkedList<AcutuatorModul*>();

    AcutuatorModul*  FindAcutuatorModul(byte address, byte subaddress); //megirni
    void AddModul(byte address, byte subaddress);
    void RefressALL();
    //void ValuesToActuators(); erre nem lesz szükseg

  private:

};


#endif
