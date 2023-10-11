#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);                              
  Serial.println("Espera un poco");
  dht.begin();
  delay(2000);
}

void loop() {
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();  

  if (!isnan(temperatura) && !isnan(humedad)) {
 
    Serial.print("% - Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");  
    Serial.print("Humedad: ");
    Serial.print(humedad);
  } 
  
  else 
  {
    Serial.println("Error en la lectura del sensor. Comprueba la conexión o espera...");
  }

  delay(2000);
}
