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

  if (!isnan(humedad) && !isnan(temperatura)) {
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("% - Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");
  } 
  
  else 
  {
    Serial.println("Error en la lectura del sensor. Comprueba la conexión o espera...");
  }

  delay(2000);
}
