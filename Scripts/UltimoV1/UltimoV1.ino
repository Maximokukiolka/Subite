#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define PIN_SENSOR_SONIDO 4

#define STASSID "https://subite-back.vercel.app/hard"
#define STAPSK "IoT"
#define SERVER_IP "elultimo10"

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(STASSID, STAPSK);

  pinMode(PIN_SENSOR_SONIDO, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado:D! Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    float humedad = dht.readHumidity();
    float temperatura = dht.readTemperature();

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("% - Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");

    int valorSensorSonido = analogRead(PIN_SENSOR_SONIDO);
    Serial.print("Valor del sensor de sonido: ");
    Serial.println(valorSensorSonido);

    String query = "?temp=" + String(temperatura) + "&sound=" + String(valorSensorSonido);

    Serial.print("[HTTP] begin...\n");
    Serial.println("http://" SERVER_IP "/hard" + query);

    http.begin(client, "http://" SERVER_IP "/hard");  // HTTP
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDocument;
    jsonDocument["temp"] = temperatura;
    jsonDocument["sound"] = valorSensorSonido;

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
