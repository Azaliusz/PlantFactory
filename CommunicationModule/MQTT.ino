const char* mqtt_server = "192.168.43.98"; //MQTT szerver címe
const int mqtt_port = 1883; //MQTT portja

//---------------------MQTT topics---------------------
const char* last_will_topic = "PF/Disconnected";
const char* connection_topic = "PF/Connected";

/*void ConnectMQTT() //Connect to MQTT broker
{
  client.setServer(mqtt_server, 1883);//connecting to mqtt server
  client.setCallback(callback);

  client.connect("ESP32_ID");  // ESP will connect to mqtt broker with clientID
  {
    Serial.println("connected to MQTT");
    // Once connected, publish an announcement...

    // ... and resubscribe
    SubscribeToTopics();//topic=Demo ADATLEKÉRÉS SZERVERTŐL
    client.publish("PF/Connected",  "");

    if (!client.connected())
    {
      reconnect();
    }
  }
}*/


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

void reconnect() //refact!!!!
{
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32_ID")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "XYZ esp32 joined");
      // ... and resubscribe
      client.subscribe("inTopic");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
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

  String mac = WiFi.macAddress();
  String ip = WiFi.localIP().toString();
  doc["MAC"] = mac.c_str();
  doc["IP"] = ip.c_str();

  char buffer[512];
  size_t n = serializeJson(doc, buffer);  //Adatok serializálása
  client.publish(connection_topic, buffer, n); //MQTT üzenet küldése
}


void mqttloop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();
}


void SubscribeToTopics() //MÉG NEM DINAMIKUS SAJÁT IPT KELL IDE BEIRNI
{
  client.subscribe("PF/10.0.0.10/SetActuator");
}

void SendMeasurment()
{
  client.publish("MeasurPF", "MÉRÉS");
  for (int i = 0; i < blocks.size(); ++i)
  {
    for (int j = 0; j < blocks.get(i)->SensorModules.size(); ++j)
    {
      DynamicJsonDocument doc(1024);
      JsonObject doc_0 = doc.createNestedObject();
      doc_0["ESP_IP"] =  ipToString(WiFi.localIP());
      doc_0["Address"] = blocks.get(i)->SensorModules.get(j)->Get_Address();
      doc_0["Subaddress"] = blocks.get(i)->SensorModules.get(j)->Get_Subaddress();
      blocks.get(i)->SensorModules.get(j)->ValuesJSON( doc_0);

      char buffer[1024];
      size_t n = serializeJson(doc, buffer);

      if ( client.publish("PF/Measurement", buffer) == true) {
        //Serial.println("Success sending message");
      } else {
        client.publish("MeasurPF", "HIBA");
      }
    }
  }
}
