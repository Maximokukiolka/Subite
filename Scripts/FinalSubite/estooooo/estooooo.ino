#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "IoTB";  // Reemplaza con el nombre de tu red Wi-Fi
const char* password = "inventaronelVAR";  
const char* serverAddress = "https://subite-back-git-main-ambarpalermo.vercel.app/hard";  // http://prueba/hard/kuku  https://subite-front.vercell.app 
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
    WiFiClient client;  // Crea un objeto WiFiClient

    HTTPClient http;
    http.begin(client, serverAddress);  // Pasa el objeto WiFiClient a begin

    // Configura el tipo de contenido de la solicitud a JSON
    http.addHeader("Content-Type", "application/json");

    
    String jsonData = "[{\"temp\" : \"45\", \"hum\" : \"32\", \"idVagon\" : \"3\", \"idTren\" : \"1\"},{ \"temp\" : \"45\", \"hum\" : \"32\", \"idVagon\" : \"3\", \"idTren\" : \"1\" }]";

    
    int httpResponseCode = http.POST(jsonData);

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

  delay(10000);  // Espera 5 segundos antes de la siguiente solicitud
}
