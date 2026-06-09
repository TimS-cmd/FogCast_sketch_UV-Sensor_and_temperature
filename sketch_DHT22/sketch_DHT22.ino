#include "DHT.h"

#define DHTPIN 27 //Je nachdem wo der Pin steckt
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 

float h = 0; //Luftfeuchtigkeit
float t = 0; //Temperatur - Grad Celsius
float f = 0; //Temperatur - Fahrenheit

float hic = 0; //Gefühlte Temperatur (heat index) - Grad Celsius
float hif = 0; //Gefühlte Temperatur (heat index) - Fahrenheit

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Serielle Kommunikation initialisieren - 9600 bits pro Sekunde
  dht.begin(); //DHT starten
}

void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true); //wenn (isFahrenheit = true)

  if (isnan(h) || isnan(t) || isnan(f)) { //Prüfung auf Daten fehlgeschlagen
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  hic = dht.computeHeatIndex(f, h, false); //Berechnung gefühlter Temperatur in Grad Celsius
  hif = dht.computeHeatIndex(f, h); //Berechnung gefühlter Temperatur in Fahrenheit

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(h);
  Serial.println(" %");

  Serial.print("Temperatur: ");
  Serial.print(t);
  Serial.println(" °C");
  //Serial.print(f);
  //Serial.println(" °F");

  Serial.println(" ");

  delay(2000); //2 Sekunden neue Messung
}