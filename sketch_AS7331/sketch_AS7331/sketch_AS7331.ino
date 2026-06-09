#include <Wire.h>
#include <SparkFun_AS7331.h>

SfeAS7331ArdI2C myUVSensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000); 

  // Dem System 1 Sekunde Zeit geben, um Spannungsspitzen beim Start zu glätten
  delay(1000); 

  Serial.println("\n--- SYSTEMSTART ---");
  Serial.println("Initialisiere AS7331...");

  if (myUVSensor.begin() == false) {
    Serial.println("FEHLER: Sensor nicht gefunden! Verkabelung prüfen.");
    while (1); 
  }

  if (myUVSensor.prepareMeasurement(MEAS_MODE_CONT) == false) {
    Serial.println("FEHLER: Sensor-Konfiguration fehlgeschlagen.");
    while (1);
  }
  
  // --- DIE ABSOLUTE BASIS-EINSTELLUNG ---
  myUVSensor.setGain(GAIN_1);              // Normale Verstärkung
  myUVSensor.setConversionTime(TIME_64MS); // Normaler Mittelweg für die Belichtung
  
  myUVSensor.setStartState(true);
  Serial.println("AS7331 erfolgreich konfiguriert!");
}

//Kalibrierung
float uviCalibration = 0.097; 

void loop() {
  if (myUVSensor.readAllUV() == ksfTkErrOk) {
    
    float uva = myUVSensor.getUVA();
    float uvb = myUVSensor.getUVB();
    float uvc = myUVSensor.getUVC();

    // Normale UV-Index Berechnung
    float uviEstimator = (uvb * 1.0) + (uva * 0.001);
    float uvIndex = uviEstimator * uviCalibration;

    Serial.print("UVA: "); 
    Serial.print(uva);
    Serial.print(" | UVB: "); 
    Serial.print(uvb);
    Serial.print(" | UVC: "); 
    Serial.print(uvc);
    Serial.print(" || UV-INDEX: "); 
    Serial.println(uvIndex, 2);

  } else {
    Serial.println("Fehler beim Auslesen der Daten!");
  }
  
  // 2 Sekunden Intervall für eine saubere, lesbare Ausgabe
  delay(2000); 
}