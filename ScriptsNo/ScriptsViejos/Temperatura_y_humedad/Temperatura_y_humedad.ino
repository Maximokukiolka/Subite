#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11


DHT dht(DHT_PIN, DHT_TYPE);

void setup() 
{
 
 Serial.begin(115200);

 dht.begin();
 delay(2000);
 
}

void loop() 
{
  
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("% - Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  delay(2000);
  
}
