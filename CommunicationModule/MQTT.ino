const char* mqtt_server = "192.168.43.98"; //MQTT szerver címe
const int mqtt_port = 1883; //MQTT portja

//---------------------MQTT topics---------------------
const char* last_will_topic = "PF/Disconnected";
const char* connection_topic = "PF/Connected";

void ConnectMQTT()//MQTT brokerhez csatlakoás
{
  //Csatlakozás MQTT-hez
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //Várakozás az MQTT-hez való csatlakozáasra
  Serial.println("Connecting to MQTT");

  String mac = WiFi.macAddress();
  String last_will="{\"MAC\":\""+mac+"\"}";

  while (!client.connected())//Probálkozás MQTT-hez csatlakozásra
  {
    if (client.connect(mac.c_str(), last_will_topic, 2, true, last_will.c_str())) //Sikeres csatlakozás MQTT-hez
    {
      Serial.println("Connected to MQTT");
      connectedMessage(); //kapcsolodási üznet elküldése
      subscribeTopics(); //feliratkozás a topicokra
    }
    else //Hibás csatlakozás MQTT-hez
    {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(500);
    }
  }
}

void mqttloop()
{
  if (!client.connected())
  {
    ConnectMQTT();
  }

  client.loop();
}

void subscribeTopics()//Topicokra feliratkozás
{
  String own_topic = "PF/";
  own_topic += WiFi.macAddress().c_str();
  client.subscribe(own_topic.c_str());
}


void callback(char* topic, byte* payload, unsigned int length)
{
  String processedtopic = MQTTTopic((String)topic);

  if (processedtopic == "SetActuator") {
    SetActuator_Topic(payload);
  }

  if (processedtopic == "SetActuatorMode") {
    SetActuator_Topic(payload);
  }
}

String MQTTTopic(String topic)
{
  int topicstart = topic.substring(3).indexOf('/');
  return topic.substring(topicstart + 4);

}


void SetActuator_Topic(byte* payload)
{
  DynamicJsonDocument doc(4092);
  deserializeJson(doc, payload);
  int Address = doc["Address"]; 
  int Subaddress = doc["Subaddress"];

  AcutuatorModul* actuator = FindActuator(Address, Subaddress);
  if (actuator != NULL)
  {
    actuator->SetActuatorValue(doc["Value"]);
  }
}

void SetActuatorMode_Topic(byte* payload)
{
  DynamicJsonDocument doc(4092);
  deserializeJson(doc, payload);
  int Address = doc["Address"]; 
  int Subaddress = doc["Subaddress"];

  AcutuatorModul* actuator = FindActuator(Address, Subaddress);
  if (actuator != NULL)
  {
    actuator->Set_Mode(doc["Mode"]);
  }
}

AcutuatorModul* FindActuator(byte address, byte subaddress)
{
  for (int i = 0; i < blocks.size(); ++i)
  {
    AcutuatorModul* actuator = blocks.get(i)->FindAcutuatorModul(address, subaddress);
    // Serial.println("<FindActuator>" + String(address) + " " + String(subaddress));
    if (actuator != NULL)
    {
      return actuator;
    }
  }
  return NULL;
}

//--------------------Kimenő csomagok----------------------
void connectedMessage()//MQTT re csatlakozás után a MAC és IP elküldése
{
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(2));
  String ip = WiFi.localIP().toString();
  doc["MAC"] = ESP_MAC.c_str();
  doc["IP"] = ip.c_str();

  char buffer[512];
  size_t n = serializeJson(doc, buffer);  //Adatok serializálása
  client.publish(connection_topic, buffer, n); //MQTT üzenet küldése
}

void SendMeasurment()
{
  client.publish("MeasurPF", "MÉRÉS");
  for (int i = 0; i < blocks.size(); ++i)
  {
    for (int j = 0; j < blocks.get(i)->SensorModules.size(); ++j)
    {

      const size_t capacity = 2*JSON_OBJECT_SIZE(4);
      DynamicJsonDocument doc(2048);

      doc["ESP_MAC"] =  ESP_MAC.c_str();
      doc["Address"] = blocks.get(i)->SensorModules.get(j)->Get_Address();
      doc["Subaddress"] = blocks.get(i)->SensorModules.get(j)->Get_Subaddress();

      JsonObject Values = doc.createNestedObject("Values");
      blocks.get(i)->SensorModules.get(j)->ValuesJSON(Values);

      char buffer[2048];
      size_t n = serializeJson(doc, buffer);

      if ( client.publish("PF/Measurement", buffer) == true) 
      {
        //Serial.println("Success sending message");
      } 
      else 
      {
        client.publish("MeasurPF", "HIBA");
      }
    }
  }
}
