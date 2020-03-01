# PlantFactory
v1.0

Raspbian install

    -MQTT Broker:
        sudo apt-get update
        sudo apt install -y mosquitto mosquitto-clients
        sudo systemctl enable mosquitto.service
        
        #mosquitto -v
    
    -MongoDB
        sudo apt-get install mongodb

    -Upgrade Node.js and Node-red
        bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
    
    -Node-red package
        node-red-dashboard
        node-red-mongodb
        node-red-node-ui-table

Communication Modul

    -Arduino Libraries
        ArduinoJSON
        LinkedList
        PubSubClient
            -MQTT_MAX_PACKET_SIZE 2048
            -MQTT_KEEPALIVE 5

