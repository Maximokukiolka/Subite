#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>  // Librería NUEVA

const char* ssid = "IoTB";
const char* password = "inventaronelVAR";
const char* serverAddress = "https://subite-back-git-main-ambarpalermo.vercel.app/hard/";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }

  Serial.println("Conexión Wi-Fi exitosa.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client; 

    HTTPClient http;

    http.setReuse(true);
    http.begin(client, serverAddress);

  
    http.addHeader("Content-Type", "application/json");  

    DynamicJsonBuffer jsonDoc;
    String jsonData = "[{\"temp\" : \"45\", \"hum\" : \"32\", \"idVagon\" : \"3\", \"idTren\" : \"1\"},{ \"temp\" : \"45\", \"hum\" : \"32\", \"idVagon\" : \"3\", \"idTren\" : \"1\" }]";
    JsonObject& root = jsonDoc.parseObject(jsonData);

    String data;
    root.printTo(data);

    int httpResponseCode = http.POST(data);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Solicitud exitosa. Respuesta del servidor:");
      Serial.print(httpResponseCode);
      Serial.print(": ");
      Serial.println(response);
    } else {
      Serial.print("Error en la solicitud. Código de estado HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(10000);
}
