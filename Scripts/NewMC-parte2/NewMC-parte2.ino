#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//#define SERVER_IP "10.0.1.7:9080" 
#define SERVER_IP "10.8.17.55"

#ifndef STASSID
#define STASSID "IoT"
#define STAPSK "elultimo10"
#endif

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado:D! Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    int temp = 0;
    int idVagon = 0;
    int idTren = 0;

    String query = "?temp" + String(temp) + "&idVagon" + String(idVagon) + "&idTren" + String(idTren);

    Serial.print("[HTTP] begin...\n");
    Serial.println("http://" SERVER_IP "/hard" + query);
   
    http.begin(client, "http://" SERVER_IP "/hard");  // HTTP
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDocument;
    jsonDocument["temp"] = temp;
    jsonDocument["idVagon"] = idVagon;
    jsonDocument["idTren"] = idTren;

   
    String jsonString;
    serializeJson(jsonDocument, jsonString);

    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST(jsonString);

    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... fallido, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
