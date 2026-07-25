#include <Wire.h>
#include <SparkFun_AS7331.h>
#include <Adafruit_SHT31.h>
#include <MPU6886.h> 
#include <qmp6988.h> // https://esp-idf-lib.github.io/qmp6988/#c.QMP6988_I2C_ADDR_GND

// Sensor-Objekte erstellen
SfeAS7331ArdI2C myUVSensor;
Adafruit_SHT31 sht_intern = Adafruit_SHT31();
Adafruit_SHT31 sht_extern = Adafruit_SHT31();
QMP6988 qmp;
MPU6886 imu;

// Kalibrierungsfaktor für UV-Sensor
float uviCalibration = 0.077; 

// Variablen für die IMU (MPU6886)
float accX = 0.0F, accY = 0.0F, accZ = 0.0F;
float gyroX = 0.0F, gyroY = 0.0F, gyroZ = 0.0F;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  delay(2000); 
  Serial.println("\n--- SYSTEMSTART SENSOR-ARRAY ---");

  // 1. UV-Sensor
  if (!myUVSensor.begin() || !myUVSensor.prepareMeasurement(MEAS_MODE_CONT)) {
    Serial.println("FEHLER: AS7331 (UV) nicht gefunden!");
  } else {
    myUVSensor.setGain(GAIN_1);              
    myUVSensor.setConversionTime(TIME_64MS); 
    myUVSensor.setStartState(true);
    Serial.println("AS7331 (UV) bereit.");
  }

  // 2. Interner SHT30 (0x44)
  if (!sht_intern.begin(0x44)) {
    Serial.println("FEHLER: Interner SHT30 nicht gefunden (0x44)!");
  } else {
    Serial.println("SHT30 (Intern) bereit.");
  }

  // 3. Externer SHT30 (0x45)
  if (!sht_extern.begin(0x45)) {
    Serial.println("FEHLER: Externer SHT30 nicht gefunden (0x45)!");
  } else {
    Serial.println("SHT30 (Extern) bereit.");
  }

  // 4. QMP6988 (Luftdruck)
  qmp.init();
  Serial.println("QMP6988 (Luftdruck) initialisiert.");

  // 5. MPU6886 (IMU) STANDALONE initialisieren
  // init() startet den Sensor auf dem Standard-I2C-Bus
  if (imu.begin() == false) {
    Serial.println("FEHLER: MPU6886 (IMU) nicht gefunden!");
  } else {
    Serial.println("MPU6886 (IMU) bereit.");
  }

  Serial.println("Initialisierung abgeschlossen. Starte Messungen...\n");
}

void loop() {
  Serial.println("--- NEUE MESSUNG ---");

  // UV-DATEN
  if (myUVSensor.readAllUV() == ksfTkErrOk) {
    float uva = myUVSensor.getUVA();
    float uvb = myUVSensor.getUVB();
    float uvIndex = ((uvb * 1.0) + (uva * 0.001)) * uviCalibration;
    Serial.print("UV-Index: "); Serial.println(uvIndex, 2);
  }

  // TEMPERATUR & FEUCHTIGKEIT (Beispiel für den internen Sensor)
  float temp_int = sht_intern.readTemperature();
  float hum_int = sht_intern.readHumidity();
  if (!isnan(temp_int)) {
    Serial.print("Intern - Temp: "); Serial.print(temp_int); Serial.print(" °C | Feuchte: "); Serial.print(hum_int); Serial.println(" %");
  }

  // LUFTDRUCK
  float pressure = qmp.calcPressure();
  Serial.print("Luftdruck: "); Serial.print(pressure / 100.0); Serial.println(" hPa");

  // --- IMU DATEN AUSLESEN ---
  // Die hideakitai-Bibliothek nutzt sehr direkte Befehle
  imu.getAccel(&accX, &accY, &accZ);
  imu.getGyro(&gyroX, &gyroY, &gyroZ);
  
  Serial.print("IMU Accel (G):  X: "); Serial.print(accX); Serial.print(" Y: "); Serial.print(accY); Serial.print(" Z: "); Serial.println(accZ);
  Serial.print("IMU Gyro (dps): X: "); Serial.print(gyroX); Serial.print(" Y: "); Serial.print(gyroY); Serial.print(" Z: "); Serial.println(gyroZ);
  
  Serial.println("--------------------\n");
  
  delay(5000); 
}