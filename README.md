# Práctica 1 - MQTT con BeagleBone Black y ESP32

Este documento detalla el procedimiento que seguimos para configurar el broker Mosquitto en la BeagleBone Black y realizar la comunicación con una ESP32 como publicador.

### 1. Instalación de Mosquitto en la BeagleBone Black
En primer lugar, procedimos a actualizar los repositorios e instalar el broker y los clientes de Mosquitto:

```bash
sudo apt update && sudo apt install mosquitto mosquitto-clients -y
```

Para verificar que la instalación fue exitosa, revisamos el estado del servicio:

```bash
sudo systemctl status mosquitto
```

Confirmamos que el estado aparece como "active (running)".


### 2. Configuración de acceso remoto
Dado que por defecto el broker solo permite conexiones locales, creamos un archivo de configuración para habilitar el acceso desde otros dispositivos de la red:

```bash
sudo nano /etc/mosquitto/conf.d/default.conf
```

Se añadió el siguiente contenido:

```text
listener 1883
allow_anonymous true
```

Posteriormente, reiniciamos el servicio para aplicar los cambios realizados:

```bash
sudo systemctl restart mosquitto
```


### 3. Pruebas de funcionamiento del broker
Para validar que el broker procesa correctamente los mensajes, realizamos una prueba utilizando dos terminales SSH.

En la **Terminal 1**, nos suscribimos al tópico "test":

```bash
mosquitto_sub -h localhost -t "test" -v
```

En la **Terminal 2**, enviamos un mensaje de prueba:

```bash
mosquitto_pub -h localhost -t "test" -m "Hola desde BBB"
```

Al recibir el mensaje `test Hola desde BBB` en la primera terminal, confirmamos el correcto funcionamiento del broker.


### 4. Configuración y despliegue en la ESP32
En el entorno de PlatformIO, configuramos el archivo `main.cpp` con las credenciales de red y la dirección IP de la BeagleBone Black:

```cpp
const char* ssid = "nombre_de_red";
const char* password = "contraseña_de_red";
const char* mqtt_server = "192.168.1.xxx"; // IP asignada a la BBB
```

Tras compilar y subir el código, verificamos en el monitor serie la conexión exitosa:

```text
Conectando a WiFi...
WiFi conectado. IP: 192.168.1.yyy
Conectando al broker MQTT... conectado!
```


### 5. Recepción de datos en tiempo real
Finalmente, desde la BeagleBone Black, nos suscribimos al tópico donde publica la ESP32 para visualizar los datos recibidos:

```bash
mosquitto_sub -h localhost -t "esp32/datos" -v
```

**Salida esperada:**

```text
esp32/datos Temperatura: 25 C
esp32/datos Temperatura: 27 C
```


### Notas adicionales
- Es fundamental que tanto la BeagleBone Black como la ESP32 se encuentren conectadas a la misma red local para asegurar la comunicación.
- Las capturas de pantalla que evidencian cada etapa del proceso se encuentran almacenadas en la carpeta `/evidencias`.
