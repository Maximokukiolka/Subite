

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "certs.h"

#ifndef STASSID
#define STASSID "IoT"
#define STAPSK "elultimo10"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

X509List cert(cert_DigiCert_Global_Root_CA);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Conectanodse...");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());


  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Esperando para tiempo de sincronizacion NTP: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("timpo: ");
  Serial.print(asctime(&timeinfo));


  WiFiClientSecure client;
  Serial.print("Conectandose a: ");
  Serial.println(github_host);

  Serial.printf("Using certificate: %s\n", cert_DigiCert_Global_Root_CA);
  client.setTrustAnchors(&cert);

  if (!client.connect(github_host, github_port)) {
    Serial.println("Conexion fallida");
    return;
  }
  
  
  int temp = 0;
  int idVagon = 0;
  int idTren = 0;
  
  String url = "http://10.8.17.118/hard";
  String query = "?temp" + String(temp) + "&idVagon" + String(idVagon) + "&idTren";
  String quer_url = url + query;
  Serial.print("Pedido de la URL: ");
  Serial.println(url);

  client.println(String("GET")) + quer_url;


  Serial.println("Pedido enviado");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers receividos");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successful!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Respuesta:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("Cerrando conexion");
}

void loop() {}
