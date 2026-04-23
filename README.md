# Practica 1 - MQTT con BBB y ESP32

Esta es la guia de lo que hice para montar el broker en la BeagleBone y conectar la ESP32.

### 1. Instalar Mosquitto en la BeagleBone
Primero hay que actualizar y bajar el broker:

```bash
sudo apt update && sudo apt install mosquitto mosquitto-clients -y
```

Para ver si quedo bien instalado, checar el status:

```bash
sudo systemctl status mosquitto
```

Deberia decir "active (running)" en las letras verdes.


### 2. Configurar el acceso
Por default no deja entrar de fuera, asi que cree el archivo de configuracion:

```bash
sudo nano /etc/mosquitto/conf.d/default.conf
```

Le pegue esto:

```text
listener 1883
allow_anonymous true
```

Y reinicie para que agarre los cambios:

```bash
sudo systemctl restart mosquitto
```


### 3. Probar que funcione el broker
Abri dos terminales para ver si pasaban los mensajes entre ellas.

En la **Terminal 1** me quede escuchando el topico "test":

```bash
mosquitto_sub -h localhost -t "test" -v
```

En la **Terminal 2** mande el mensaje:

```bash
mosquitto_pub -h localhost -t "test" -m "Hola desde BBB"
```

Si en la Terminal 1 sale `test Hola desde BBB`, es que el broker ya esta funcionando bien.


### 4. Configurar la ESP32
En el codigo de `main.cpp` dentro de PlatformIO, puse mis datos de red:

```cpp
const char* ssid = "mi_red";
const char* password = "mi_password";
const char* mqtt_server = "192.168.1.xxx"; // aqui va la IP de la BBB
```

Compile y subi el codigo. En el monitor serie deberia salir:

```text
Conectando a WiFi...
WiFi conectado. IP: 192.168.1.yyy
Conectando al broker MQTT... conectado!
```


### 5. Ver los datos reales
Para ver lo que esta mandando la ESP32 desde la BeagleBone use:

```bash
mosquitto_sub -h localhost -t "esp32/datos" -v
```

**Salida esperada:**

```text
esp32/datos Temperatura: 25 C
esp32/datos Temperatura: 27 C
```


### Notas finales:
- Si no conecta, hay que checar que la BBB y la ESP32 esten conectadas al mismo modem.
- Las capturas de pantalla de todo el proceso estan en la carpeta `/evidencias`.
