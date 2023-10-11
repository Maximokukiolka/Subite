#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>

char serverAddress[] = "http://prueba/hard/kuku"; // Cambia esto por la dirección de tu servidor
int serverPort = 80;
EthernetClient client;
//HttpClient http(client);

void setup() {
  Ethernet.begin(mac);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Define la información que deseas enviar en formato JSON
  String jsonData = "{\"nombre\": \"Ejemplo\"}";

  // Configura los encabezados para indicar que estás enviando datos en formato JSON
  String headers[] = {"Content-Type: application/json"};
  
  int statusCode = http.post(serverAddress, serverPort, "http://prueba/hard/kuku", jsonData, headers);

  if (statusCode == 200) {
    Serial.println("Solicitud exitosa.");
    Serial.print("Respuesta del servidor: ");
    Serial.println(http.responseBody());
  } else {
    Serial.print("Error en la solicitud. Código de estado HTTP: ");
    Serial.println(statusCode);
  }

  delay(5000); // Espera 5 segundos antes de la siguiente solicitud
}
