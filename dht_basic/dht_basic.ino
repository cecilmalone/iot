#include <DHT.h>

#define DHTPIN 5 // pino que estamos conectado (D1)
#define DHTTYPE DHT11 // DHT 11

DHT dht1(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht1.begin();
}

void loop() 
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } 
  else 
  {
    Serial.print("Umidade (%): ");
    Serial.print(h);
    Serial.print("       ");
    Serial.print("Temperatura (°C): ");
    Serial.println(t);
  }
  delay(3000);
}