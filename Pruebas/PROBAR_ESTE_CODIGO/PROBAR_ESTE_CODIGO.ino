#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


const char* ssid = "IoT";
const char* password = "elultimo10";
const char* serverAddress = ""; 
const int serverPort = 80; 
const int soundSensorPin = A0; 
const int temperatureSensorPin = A1; 
const int humiditySensorPin = A2; 

void setup() {
 
  Serial.begin(115200);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }
  Serial.println("Conexión Wi-Fi establecida");
}

void loop() {
  
  float soundValue = analogRead(soundSensorPin);
  float temperatureValue = analogRead(temperatureSensorPin);
  float humidityValue = analogRead(humiditySensorPin);


  StaticJsonDocument<200> jsonDocument;
  jsonDocument["sonido"] = soundValue;
  jsonDocument["temperatura"] = temperatureValue;
  jsonDocument["humedad"] = humidityValue;

  
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  
  sendToServer(jsonString);

  
  delay(5000); 
}

void sendToServer(String data) {
  
  WiFiClient client;

  
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Conectado al servidor");

   
    client.println("POST /ruta/de/tu/servicio HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(data.length()));
    client.println();
    client.println(data);

    
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }
    }

    
    client.stop();
    Serial.println("Desconectado del servidor");
  } else {
    Serial.println("Error al conectar al servidor");
  }
}
