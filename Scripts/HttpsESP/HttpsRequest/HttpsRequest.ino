#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "IoTB";
const char* password = "inventaronelVAR";
const char* server = "https://subite-back-git-main-ambarpalermo.vercel.app";
const int httpsPort = 443;

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conéctate a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }
  Serial.println("Conexión WiFi establecida");

  // Realiza la solicitud HTTPS
  if (sendHTTPSRequest()) {
    Serial.println("Solicitud HTTPS exitosa");
  } else {
    Serial.println("Fallo en la solicitud HTTPS");
  }
}

void loop() {
  // Tu código adicional puede ir aquí
}

bool sendHTTPSRequest() {
  Serial.print("Conectando a ");
  Serial.println(server);

  if (!client.connect(server, httpsPort)) {
    Serial.println("Conexión fallida");
    return false;
  }

  // Construye los datos que quieres enviar en formato JSON
  //DynamicJsonDocument doc(200);
  // Define tus datos JSON aquí
  //doc[0]["temp"] = 45;
  //doc[0]["hum"] = 32;
  //doc[0]["idVagon"] = 3;
  //doc[0]["idTren"] = 1;
  //doc[1]["temp"] = 45;
  //doc[1]["hum"] = 32;
  //doc[1]["idVagon"] = 3;
  //doc[1]["idTren"] = 1;
  
  //String jsonData;
  //serializeJson(doc, jsonData);
   
    DynamicJsonDocument jsonDoc(200);
    String jsonData = "[{\"temp\" : 45, \"hum\" : 32, \"idVagon\" : 3, \"idTren\" : 1},{ \"temp\" : 45, \"hum\" : 32, \"idVagon\" : 3, \"idTren\" : 1 }]";
    //JsonObject& root = jsonDoc.parseObject(jsonData);
  
  HTTPClient https;
  https.begin(client, server, httpsPort, "/hard"); // Ruta con "/" al principio
  https.addHeader("Content-Type", "application/json");
  int httpCode = https.POST(jsonData);

  if (httpCode > 0) {
    String payload = https.getString();
    Serial.println("Código de respuesta HTTP: " + String(httpCode));
    Serial.println("Respuesta del servidor: " + payload);
    https.end();
    return true;
  } else {
    Serial.println("Error en la solicitud HTTPS");
    https.end();
    return false;
  }
  
}
 //AGREGAR ARRIBA
  char sslErrorMsg[80];
  int sslError = client.getLastSSLError(sslErrorMsg, sizeof(sslErrorMsg));
  if (sslError) {
    Serial.printf("SSL error: %d: %s\r\n", sslError, sslErrorMsg);
  }
  http.end();
