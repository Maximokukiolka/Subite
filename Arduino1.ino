#include<ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "";
const char* password= "";

String user = "";
String pass ="";
  
void setup() 
{
 Delay(10);
 serial.begin(115200);

 WiFi.begin (ssid, password);
 Serial.print("Conectando -.-' ...");
 while (WiFi.status() !=WL_CONNECTED)
 {
 delay(500);
 Serial.print(".")
 }
 Serial.print("Conectado:D! La IP es: ");
 
}

void loop() 
{
   if (WiFi.status()==WL_CONNECTED)
   {
   HTTPClient  http;
   Serial.print ("Comenzando...");
   //String DatosEnviar = "user" + user "&pass" + pass;

   http.begin(client, "http://localhost:5000/hard" SERVER_IP "/postplain/");
   http.addHeader("Content-Type", "application/json");
    
    
   }

}
