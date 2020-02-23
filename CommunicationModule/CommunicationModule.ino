/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif

#include <Arduino.h>

#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <LinkedList.h>


WiFiClient espClient;
PubSubClient client(espClient); //lib required for mqtt


#include "Block.h"

//START--------------------------------------Wifi parameters--------------------------------------------
//WIFI parameters
const char* ssid     = "Workstation";
const char* password = "EP56.csf78";

// Set your Static IP address
IPAddress local_IP(192, 168, 43, 10);
// Set your Gateway IP address
IPAddress gateway(192, 168, 43, 10);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

//END---------------------------------------- Wifi parameters--------------------------------------------

LinkedList<Block*> blocks = LinkedList<Block*>();

void setup() {

  Serial.begin(115200);
  ConnectWifi();
  ConnectMQTT();

  //PiciInit();
  TestSetup();
}


int measurement_period = 100;
unsigned long last_measurement = 0;


int send_period = 1000;
unsigned long last_send = 0;

void loop() {

  //webSocket.loop();
  mqttloop();

  if (millis() > last_measurement + measurement_period)
  {
    last_measurement = millis();
    Measure();// befrissiti az összes blok tárolt adatait
   //  SendToActuators();//a mért értékeket kiküldi a beavatkozoknak 
    //Serial.print("MÉRÉS:");
   // Serial.println();
  }
  
  if (WiFi.status() == WL_CONNECTED)
  {
    if (millis() > last_send + send_period)
    {
      last_send = millis();
      SendMeasurment();
      //Serial.println("Measurement send");
    }
  }
  else 
  {
    Serial.println("WiFi Disconnected");
    ConnectWifi();
  }
}
