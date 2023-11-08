#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <DHT.h>

#ifndef STASSID
#define STASSID "IoTB"
#define STAPSK "inventaronelVAR"
#endif

ESP8266WiFiMulti WiFiMulti;
DHT dht(4, DHT11); // Define el sensor DHT11 en el pin 4

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(STASSID, STAPSK);
  Serial.println("setup() done connecting to ssid '" STASSID "'");
  dht.begin(); // Inicializa el sensor DHT
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://subite-back-git-main-ambarpalermo.vercel.app/hard")) {
      Serial.print("[HTTPS] POST...\n");

      float humedad = dht.readHumidity();
      float temperatura = dht.readTemperature();

      if (!isnan(temperatura) && !isnan(humedad)) {
        Serial.print("% - Temperatura: ");
        Serial.print(temperatura);
        Serial.println("°C");
        Serial.print("Humedad: ");
        Serial.print(humedad);

        // Crear un objeto JSON con los datos del sensor
        String jsonData = "[{\"temp\" : " + String(int(temperatura)) + ", \"hum\" : " + String(int(humedad)) + ", \"idVagon\" : 3, \"idTren\" : 1 },{ \"temp\" : 45, \"hum\" : 32, \"idVagon\" : 3, \"idTren\" : 1 }]";

        Serial.println("Body data: " + jsonData);
        int httpCode = https.POST(jsonData);

        if (httpCode > 0) {
          Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTPS] POST... failed, code %d error: %s\n", httpCode, https.errorToString(httpCode).c_str());
        }
        https.end();
      } else {
        Serial.println("Error en la lectura del sensor. Comprueba la conexión o espera...");
      }
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
