void TestSetup()
{
  blocks.add(new Block("Test chamber"));
}

String ESP_MAC;

void ConnectWifi() {
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ESP_MAC = WiFi.macAddress();
}


String command;

void ESPConsole()
{
  if (Serial.available() > 0)
  {
    command = Serial.readString();
    if (command == "show")
    {
      for (int i = 0; i < blocks.size(); ++i)
      {
        Serial.println(blocks.get(i)->ShowBlock());
      }
    }
  }
}

String ipToString(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}



//START--------------------------------------Measure--------------------------------------------
void Measure()
{
  for (int i = 0; i < blocks.size(); ++i)
  {
    blocks.get(i)->RefressALL();
  }
}
//END----------------------------------------Measure--------------------------------------------
