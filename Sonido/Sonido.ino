const int PIN_SENSOR_SONIDO = 4;

void setup() 
{
  
  Serial.begin(115200);
  
  pinMode(PIN_SENSOR_SONIDO, INPUT);
  
}

void loop() 
{
  
  int valorSensorSonido = analogRead(PIN_SENSOR_SONIDO);

  Serial.print("Valor del sensor de sonido: ");
  Serial.println(valorSensorSonido);

  delay(1000);
  
}
