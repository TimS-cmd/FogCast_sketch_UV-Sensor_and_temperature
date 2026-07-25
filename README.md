# FogCast – UV-Sensor & Temperatur Sketches

Dieses Repository enthält mehrere Arduino-Sketches (`.ino`, geschrieben in C++) zur Ansteuerung verschiedener Sensoren für das FogCast-Projekt. Die Sketches sind für Development Boards bzw. den Raspberry Pi Pico ausgelegt und decken unterschiedliche Ausbaustufen der Sensorik ab – von Einzelsensoren bis zur vollständigen Außenstations-Architektur.

## Übersicht der Sketches

| Ordner | Beschreibung | Sensoren |
|---|---|---|
| `sketch_AS7331` | Basis-Sketch zur Ansteuerung des UV-Sensors | AS7331 (UV-Sensor) |
| `sketch_AS7331_und_SHT-30` | Kombination aus UV- und Temperatur-/Feuchtigkeitssensor | AS7331, SHT-30 |
| `sketch_DHT22` | Sketch zur Temperatur- und Luftfeuchtigkeitsmessung | DHT22 |
| `sketch_Pico2_with_AS7331_SHT30-Outdoor...` | Vollständige Architektur für den Außeneinsatz auf dem Raspberry Pi Pico 2 (ohne Ceilometer) | AS7331, SHT-30 |

## Sensoren im Überblick

- **AS7331** – Spektraler UV-Sensor (UVA/UVB/UVC) für die UV-Index-Erfassung
- **SHT-30** – Digitaler Temperatur- und Feuchtigkeitssensor
- **DHT22** – Temperatur- und Feuchtigkeitssensor (Alternative/Vergleichssensor zum SHT-30)

## Voraussetzungen

- Arduino IDE (oder PlatformIO)
- Für den Pico2-Sketch: Unterstützung für den Raspberry Pi Pico 2 (Arduino-Mbed-Core oder entsprechendes Board-Paket)
- Benötigte Bibliotheken je nach Sketch, u. a.:
  - Adafruit AS7331 Bibliothek (oder Hersteller-Library)
  - Adafruit SHT31/SHT30 Bibliothek
  - DHT sensor library (Adafruit)
  - Wire (I2C)

## Verwendung

1. Repository klonen:
   ```bash
   git clone https://github.com/<dein-user>/FogCast_sketch_UV-Sensor_and_temperature.git
   ```
2. Gewünschten Sketch-Ordner in der Arduino IDE öffnen
3. Benötigte Bibliotheken über den Bibliotheksverwalter installieren
4. Board und Port auswählen
5. Sketch hochladen

## Hinweis

Der Sketch `sketch_Pico2_with_AS7331_SHT30-Outdoor...` bildet die aktuell vollständigste Architektur ab, jedoch **ohne Anbindung des Ceilometers**. Diese Integration ist für eine spätere Version vorgesehen.

## Projektkontext

FogCast ist ein Projekt zur Nebel-/Wettervorhersage bzw. -erfassung mittels kombinierter Umweltsensorik (UV, Temperatur, Feuchtigkeit).
