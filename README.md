# Practica MQTT - Mosquitto + ESP32

Broker MQTT en BeagleBone Black con una ESP32 como publisher.

Esquema:
ESP32 - WiFi - Broker Mosquitto (BeagleBone Black) - Subscriber

## Instalacion del broker (BeagleBone Black)

Conectarse por SSH a la BBB y correr:

sudo apt update && sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto
sudo systemctl start mosquitto

Crear el archivo /etc/mosquitto/conf.d/default.conf con:

listener 1883
allow_anonymous true

sudo systemctl restart mosquitto

## Prueba local

Abrir dos terminales SSH a la BBB.

# Terminal 1
mosquitto_sub -h localhost -t "test/topic" -v

# Terminal 2
mosquitto_pub -h localhost -t "test/topic" -m "Hola"

## ESP32

Abrir el proyecto en PlatformIO y cambiar en main.cpp:

const char* ssid        = "nombre_red";
const char* password    = "contraseña";
const char* mqtt_server = "ip_de_la_bbb";

Subir el codigo. La ESP32 publica en esp32/datos cada 5 segundos.

Para recibir los mensajes en la BBB:

mosquitto_sub -h localhost -t "esp32/datos" -v

## Notas

- La ESP32 solo soporta redes 2.4GHz, verificar que el router no este en modo 5GHz o banda dual
- La ESP32 y la BBB tienen que estar en la misma red, no funciona si una esta en red guest
- Si el SSID tiene espacios al final hay que incluirlos exactos en el codigo o no conecta
- En Linux puede salir error de permisos al abrir el monitor serie, correr sudo usermod -a -G dialout $USER y reiniciar sesion

## Evidencias

Las capturas estan en /evidencias.

## Referencias

- https://beagleboard.org/getting-started
- https://mosquitto.org
