

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

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("Conectandose a: ");
  Serial.println(github_host);

  Serial.printf("Using certificate: %s\n", cert_DigiCert_Global_Root_CA);
  client.setTrustAnchors(&cert);

  if (!client.connect(github_host, github_port)) {
    Serial.println("Conexion fallida");
    return;
  }

   String url = "http://10.8.17.118/hard";

     int temp = 0;
     int idVagon = 0;
     int idTren = 1;

//       String url_1 = url + temp;
//       String url_2 = url + idVagon;
//       String url_3 = url + idTren;
           
  
  
  Serial.print("Requesting URL: ");
  Serial.println(url);

//  client.print(String("GET")) + url + " HTTP/1.1\r\n" + "Host: "; + temp + idVagon + idTren //github_host + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
   client.print(String("GET")) 

  Serial.println("Request sent");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successful!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("Closing connection");
}

void loop() {}
