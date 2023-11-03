#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "IoTB";
const char* password = "inventaronelVAR";
const char* serverAddress = "https://subite-back-git-main-ambarpalermo.vercel.app/hard";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }

  Serial.println("Conexión Wi-Fi exitosa.");
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float humedad = dht.readHumidity();
    float temperatura = dht.readTemperature();

    if (!isnan(temperatura) && !isnan(humedad)) {
      Serial.print("% - Temperatura: ");
      Serial.print(temperatura);
      Serial.println("°C");
      Serial.print("Humedad: ");
      Serial.print(humedad);

      
      String jsonData = "[{\"temp\" : \"" + String(temperatura) + "\", \"hum\" : \"" + String(humedad) + "\", \"idVagon\" : \"3\", \"idTren\" : \"1\"}]";

      
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverAddress);

      
      http.addHeader("Content-Type", "application/json");

      
      int httpResponseCode = http.POST(jsonData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("\nSolicitud exitosa. Respuesta del servidor:");
        Serial.print(httpResponseCode);
        Serial.print(": ");
        Serial.println(response);
      } else {
        Serial.print("\nError en la solicitud. Código de estado HTTP: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("\nError en la lectura del sensor. Comprueba la conexión o espera...");
    }
  }

  delay(10000); 
}
