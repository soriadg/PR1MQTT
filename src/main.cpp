#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "Vallejo ";
const char* password = "Vall0340";
const char* mqtt_server = "192.168.68.111";

const char* topic     = "esp32/datos";
const char* client_id = "ESP32_Publisher";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Conectando a WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect(client_id)) {
      Serial.println("conectado!");
    } else {
      Serial.print("Error: ");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    String mensaje = "Temperatura: " + String(random(20, 35)) + " C";
    client.publish(topic, mensaje.c_str());
    Serial.println("Publicado: " + mensaje);
  }
}