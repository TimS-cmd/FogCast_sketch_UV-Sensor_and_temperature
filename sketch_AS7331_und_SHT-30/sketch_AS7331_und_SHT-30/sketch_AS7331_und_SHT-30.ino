#include <Wire.h>
#include <SparkFun_AS7331.h>
#include <Adafruit_SHT31.h>

// Instanzen für beide Sensoren
SfeAS7331ArdI2C myUVSensor;
Adafruit_SHT31 sht30 = Adafruit_SHT31();

// Kalibrierung für UV-Index
float uviCalibration = 0.097; 

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000); 

  // Dem System 1 Sekunde Zeit geben, um Spannungsspitzen beim Start zu glätten
  delay(1000); 

  Serial.println("\n--- SYSTEMSTART ---");

  // 1. SHT30 initialisieren
  Serial.println("Initialisiere SHT30 Luftsensor...");
  if (!sht30.begin(0x44)) {
    Serial.println("FEHLER: SHT30 nicht gefunden! Verkabelung prüfen.");
  } else {
    Serial.println("SHT30 erfolgreich gefunden!");
  }

  // 2. AS7331 initialisieren
  Serial.println("Initialisiere AS7331 UV-Sensor...");
  if (myUVSensor.begin() == false) {
    Serial.println("FEHLER: AS7331 nicht gefunden! Verkabelung prüfen.");
    while (1); 
  }

  if (myUVSensor.prepareMeasurement(MEAS_MODE_CONT) == false) {
    Serial.println("FEHLER: AS7331 Sensor-Konfiguration fehlgeschlagen.");
    while (1);
  }
  
  // --- DIE ABSOLUTE BASIS-EINSTELLUNG ---
  myUVSensor.setGain(GAIN_1);              // Normale Verstärkung
  myUVSensor.setConversionTime(TIME_64MS); // Normaler Mittelweg für die Belichtung
  
  myUVSensor.setStartState(true);
  Serial.println("AS7331 erfolgreich konfiguriert!");
  
  Serial.println("--- SETUP ABGESCHLOSSEN ---");
}

void loop() {
  Serial.println("\n");

  // SHT30 AUSLESEN
  float temp = sht30.readTemperature();
  float humidity = sht30.readHumidity();

  if (!isnan(temp) && !isnan(humidity)) {
    Serial.print("SHT30   -> Temp: "); 
    Serial.print(temp, 1); // ,1 rundet auf eine Nachkommastelle
    Serial.print(" °C | Luftfeuchte: "); 
    Serial.print(humidity, 1); 
    Serial.println(" %");
  } else {
    Serial.println("SHT30   -> Fehler beim Lesen der Klimadaten!");
  }

  // AS7331 AUSLESEN
  if (myUVSensor.readAllUV() == ksfTkErrOk) {
    
    float uva = myUVSensor.getUVA();
    float uvb = myUVSensor.getUVB();
    float uvc = myUVSensor.getUVC();

    // Normale UV-Index Berechnung
    float uviEstimator = (uvb * 1.0) + (uva * 0.001);
    float uvIndex = uviEstimator * uviCalibration;

    Serial.print("AS7331  -> UVA: "); 
    Serial.print(uva, 1);
    Serial.print(" | UVB: "); 
    Serial.print(uvb, 1);
    Serial.print(" | UVC: "); 
    Serial.print(uvc, 1);
    Serial.print(" || UV-INDEX: "); 
    Serial.println(uvIndex, 2);

  } else {
    Serial.println("AS7331  -> Fehler beim Auslesen der UV-Daten!");
  }
  
  // 2 Sekunden Intervall für eine saubere, lesbare Ausgabe
  delay(2000); 
}