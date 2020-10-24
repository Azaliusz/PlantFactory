# PlantFactoryServer

Ez a docker projekt a szerver oldalt szolgáltatja a Plant Pactory projektnek

Tartalmaz: \*

- Node-Red servert
- Mosquitto MQTT brókert
- MongoDB adatbázist
- VUE webklienst

## Projekt elindítása

A projekt felépítéséhez szükség van a [Docker](https://www.docker.com/)-re. A könnyebb áttekinthetőség érdekébe érdemes telepíteni a Docker Desktop-ot
Ennek telepítése után ebbeen a mappában kell futtatni a következő parancsot

```bash
docker-compose -f "docker-compose.yml" up -d --build
```

## Portok

A különböző kontánerekből a programok a következő portokon keresztül kommunikálnak

- 1880: Node-Red
- 1883: Mosquitto MQTT bróker
- 8080: VUE webkliens
- 27017: MongoDB adatbázist

## MQTT topic-ok

TODO: ez még hiányzik
