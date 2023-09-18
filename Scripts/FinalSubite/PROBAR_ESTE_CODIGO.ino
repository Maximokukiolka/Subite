#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h>


const char* ssid = "IoT";
const char* password = "elultimo10";


const char* serverAddress = "https://subite-back.vercel.app/hard";
const int serverPort = 80;


#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


WiFiClient client;

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
  Serial.println("Conexión WiFi exitosa");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {

  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();


  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

 s
  String jsonPayload = "{\"temperatura\":" + String(temperatura) + ",\"humedad\":" + String(humedad) + "}";


  String postData = "POST /ruta-api HTTP/1.1\r\n";
  postData += "Host: " + String(serverAddress) + "\r\n";
  postData += "Content-Type: application/json\r\n";
  postData += "Content-Length: " + String(jsonPayload.length()) + "\r\n\r\n";
  postData += jsonPayload;


  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Conectado al servidor");
    client.print(postData);


    while (client.connected()) {
      if (client.available()) {
        String response = client.readStringUntil('\r');
        Serial.println("Respuesta del servidor: ");
        Serial.println(response);
      }
    }
    client.stop();
  } else {
    Serial.println("Error al conectarse al servidor");
  }


  delay(60000);  
}
