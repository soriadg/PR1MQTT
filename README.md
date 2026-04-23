# Practica 1 - MQTT con BBB y ESP32

Esta es la guia de lo que hice para montar el broker en la BeagleBone y conectar la ESP32.

1. Instalar Mosquitto en la BeagleBone
Primero hay que actualizar y bajar el broker.
$ sudo apt update && sudo apt install mosquitto mosquitto-clients -y

Para ver si quedo bien instalado, checar el status:
$ sudo systemctl status mosquitto
Deberia decir "active (running)".

2. Configurar el acceso
Por default no deja entrar de fuera, asi que cree el archivo de configuracion:
$ sudo nano /etc/mosquitto/conf.d/default.conf

Le pegue esto:
listener 1883
allow_anonymous true

Y reinicie para que agarre los cambios:
$ sudo systemctl restart mosquitto

3. Probar que funcione el broker
Abri dos terminales para ver si pasaban los mensajes.
En la 1 me quede escuchando:
$ mosquitto_sub -h localhost -t "test" -v

En la 2 mande un saludo:
$ mosquitto_pub -h localhost -t "test" -m "hola"

Si en la terminal 1 sale "test hola" es que ya jala.

4. Configurar la ESP32
En el codigo de main.cpp puse mis datos de red:
const char* ssid = "mi_red";
const char* password = "mi_password";
const char* mqtt_server = "192.168.1.xxx"; // aqui va la IP de la BBB

Compile y subi con PlatformIO. En el monitor serie sale:
Conectando a WiFi...
WiFi conectado. IP: 192.168.1.yyy
Conectando al broker MQTT... conectado!

5. Ver los datos reales
Para ver lo que manda la ESP32 desde la BBB use:
$ mosquitto_sub -h localhost -t "esp32/datos" -v

Salida esperada:
esp32/datos Temperatura: 25 C
esp32/datos Temperatura: 27 C

Notas:
- Si no conecta, checar que la BBB y la ESP32 esten en el mismo modem.
- Las capturas de como me salio a mi estan en la carpeta /evidencias.
