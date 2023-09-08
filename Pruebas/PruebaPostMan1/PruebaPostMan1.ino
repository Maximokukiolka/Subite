#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

const char* ssid = "IoT"; 
const char* password = "elultimo10"; 

const char* host = "postman-echo.com"; 
const int port = 80; 

void setup() {
  Serial.begin(115200);
  delay(10);


  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conexión WiFi establecida");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 
  DynamicJsonDocument jsonDoc(200); 

 
  jsonDoc["sensor"] = "temperatura";
  //jsonDoc["valor"] = random(0, 100);

 
  String jsonString;
  serializeJson(jsonDoc, jsonString);

 
  WiFiClient client;
  if (client.connect(host, port)) {
    Serial.println("Conectado al servidor");

    
    client.println("POST /postman-echo.com HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Tipo contenido: application/json");
    client.println("Largo contentenido: " + String(jsonString.length()));
    client.println();
    client.println(jsonString);
    client.println();

  
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }
    }
    client.stop();
    Serial.println("Conexión cerrada");
  } else {
    Serial.println("Error al conectar al servidor");
  }

  
  delay(5000); 
}
