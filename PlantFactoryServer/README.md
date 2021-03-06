# PlantFactoryServer

Ez a docker projekt a szerver oldalt szolgáltatja a Plant Pactory projektnek

Tartalmaz:

- Node-Red servert
- Mosquitto MQTT brókert
- MongoDB adatbázist
- VUE webklienst

## Projekt elindítása

A projekt felépítéséhez szükség van a [Docker](https://www.docker.com/)-re.
Ennek telepítése után ebben a mappában kell futtatni a következő parancsot:

```bash
docker-compose -f "docker-compose.yml" up -d --build
```

A könnyebb áttekinthetőség érdekébe érdemes telepíteni a Docker Desktop-ot és/vagy VS Code-ban való fejlesztés esetén a [Docker extension](https://code.visualstudio.com/docs/containers/overview)-t

## Portok

A különböző konténerekből a programok a következő portokon keresztül kommunikálnak a host géppel:

- **1880**: Node-Red
- **1883**: Mosquitto MQTT bróker
- **8080**: VUE webkliens
- **27017**: MongoDB adatbázist

## Konténerek hálózata

A konténerek között két hálózat található:

1. mqtt-network:

- Node-Red server
- Mosquitto MQTT bróker
- VUE webkliens

2. db-network:

- Node-Red server
- MongoDB adatbázis

Ezeken a hálózatokon belül az egyes konténerek a következő néven látják egymást:

- Node-Red server: **node-red**
- Mosquitto MQTT bróker: **mqtt-broker**
- MongoDB adatbázis: **database**
- VUE webkliens: **webclient**

## MQTT topic-ok

TODO: ez még hiányzik

## Adatbázis adatok

A MongoDB használatához ajánlott telepíteni a [MongoDB Compass](https://www.mongodb.com/try/download/compass)-t
Az adatbázishoz a következőkkel lehet csatlakoni

- Port: **27017**
- Felhasználónév: **root**
- Jelszó: **PF2020**

Ez a felhasználó admin jogosúltságú úgyhogy csk óvatosan :)

### Permanens adatok

Az első build-nél létrejön a mappában egy db nevü mappa. A MongoDB ebben a mappában fogja tárolni a benne található adatokat, így ha a konténer valamilyen olknál fogva törlésre kerül az adatok továbbra is megmaradnak. A docker-compose.yml újra build-elése után az adatok továbbra is elérhetőek lesznek a MongoDB konténeren belül
