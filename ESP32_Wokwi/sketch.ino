#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <HX711.h>
#include <ArduinoJson.h>
 
const char* ssid = "Wokwi-GUEST";
const char* password = "";
 
const char* mqtt_server = "6264bb59992c4a7ea9f762277e2f87a1.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "VetFlowAdmin";
const char* mqtt_pass = "VetFlow123abc";
 
const char* topic_telemetria = "vetflow/clinica/baia1/telemetria";
 
#define DHTPIN 15
#define DHTTYPE DHT22
 
#define HX711_DT 16
#define HX711_SCK 4
 
DHT dht(DHTPIN, DHTTYPE);
HX711 scale;
WiFiClientSecure espClient;
PubSubClient client(espClient);
 
unsigned long lastMsgTime = 0;
const unsigned long interval = 1000;
 
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a rede: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nWiFi conectado!");
}
 
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT segura com HiveMQ...");
    String clientId = "ESP32Client-VetFlow-";
    clientId += String(random(0xffff), HEX);
   
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("conectado com sucesso!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
 
void setup() {
  Serial.begin(115200);
 
  dht.begin();
  scale.begin(HX711_DT, HX711_SCK);
  scale.set_scale(420.0);
  scale.tare();
 
  espClient.setInsecure();
 
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}
 
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  unsigned long now = millis();
  if (now - lastMsgTime > interval) {
    lastMsgTime = now;
 
    float temperatura = dht.readTemperature();
    float peso = 0.0;

    if (scale.is_ready()) {
      long raw_val = scale.read();
      peso = abs((float)raw_val / 426.0); 
    } 
    else {
      Serial.println("HX711 não detectado.");
    }
 
    if (isnan(temperatura)) {
      Serial.println("Falha ao ler DHT22!");
      temperatura = 0.0;
    }
 
    StaticJsonDocument<200> doc;
    doc["id_pet"] = "VF-789";        
    doc["temperatura"] = serialized(String(temperatura, 1));
    doc["peso"] = serialized(String(peso, 2));              
    doc["timestamp"] = now;
 
    char buffer[200];
    serializeJson(doc, buffer);
 
    Serial.print("Publicando: ");
    Serial.println(buffer);
    client.publish(topic_telemetria, buffer);
  }
}