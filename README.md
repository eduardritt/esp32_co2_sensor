# 🌬️ ESP32 CO₂-Ampel mit SCD41 & 8-stelligem MAX7219 Display

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue.svg)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Version](https://img.shields.io/badge/Version-1.0.0-orange.svg)]()

Ein intelligentes CO₂-Ampelsystem auf Basis eines **ESP32** und des **Sensirion SCD41 Sensors**.  
Die aktuelle CO₂-Konzentration wird auf einem **8-stelligen MAX7219 7-Segment-Display** angezeigt und zusätzlich über eine LED-Ampel visualisiert.
---

## Messwerte

Europäische Norm EN 13779 bewertet die Konzentration von CO2 in Innenräumen in vier Qualitätsstufen. 
Als hygienisch inakzeptabel gilt die Raumluftqualität ab 2.000 ppm.

| CO2 Gehalt im ppm    |  	CO2 in %	     |   Qualitätsstufe
|----------------------|-----------------|----------------------------|
|   Unter 800	        |   < 0,08 %	     | Hohe Raumluftqualität      |
|   800 - 1.000	     |   0,08 - 0,1 %  | Mittlere Raumluftqualität  |
|   1.000 - 1.400      |   0,1 - 0,14 %  | Mäßige Raumluftqualität    |
|   Über 1.400         |   >0,14 %	     | Niedrige Raumluftqualität  | 

---

## 📖 Projektbeschreibung

Dieses Projekt misst die CO₂-Konzentration in Innenräumen und stellt diese:

- 🔢 numerisch auf einem 8-stelligen MAX7219 7-Segment-Display dar  
- 🚦 visuell über eine LED-Ampel (Grün / Gelb / Rot blinkend)

Die Ampellogik:

| CO₂-Wert | Status | LED |
|----------|--------|-----|
| < 800 ppm | Gute Luft | 🟢 Grün |
| 800–1400 ppm | Mittel | 🟡 Gelb |
| ≥ 1400 ppm | Lüften! | 🔴 Rot blinkend |

Messintervall: **5 Sekunden**  
Anzeige: fortlaufend aktualisiert  
Keine blockierenden `delay()`-Aufrufe im Hauptprogramm

---

## 🧰 Stückliste (BOM)

| Bauteil | Menge | Beschreibung |
|----------|--------|--------------|
| ESP32 Dev Board | 1 | z. B. ESP32 DevKit V1 |
| SCD41 CO₂ Sensor | 1 | I²C CO₂ / Temperatur / Luftfeuchte |
| MAX7219 8-stelliges 7-Segment-Display | 1 | SPI-Ansteuerung |
| LED Grün | 1 | 5 mm oder 3 mm |
| LED Gelb | 1 | 5 mm oder 3 mm |
| LED Rot | 1 | 5 mm oder 3 mm |
| Widerstände 220–330 Ω | 3 | Für LEDs |
| Jumperkabel | mehrere | Verbindung |
| Breadboard | 1 | optional |
| 5 V Versorgung | 1 | USB oder extern |

---

## 🔌 Pinbelegung

### MAX7219 Display

| Display Pin | ESP32 Pin |
|-------------|------------|
| VCC | 3.3V |
| GND | GND |
| DIN | GPIO23 |
| CLK | GPIO18 |
| CS  | GPIO5 |


---

### SCD41 Sensor (I²C)

| Sensor Pin | ESP32 Pin |
|------------|------------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

### LED-Ampel

| LED | ESP32 Pin |
|------|------------|
| Grün | GPIO27 |
| Gelb | GPIO26 |
| Rot | GPIO25 |

Alle LEDs mit Vorwiderstand (220–330 Ω) betreiben.

---

## 🛠️ Verwendete Bibliotheken

- [SensirionI2cScd4x](https://github.com/Sensirion/embedded-scd4x)  
- [MAX7SegmentDisplay](https://github.com/MajicDesigns/MAX7SegmentDisplay)  
- Wire (Standard I²C, Arduino Core)

Installation über den Arduino Library Manager.

---

## 🚀 Funktionsweise

1. ESP32 startet den SCD41 im periodischen Messmodus  
2. Alle 5 Sekunden wird ein neuer CO₂-Wert gelesen  
3. Der Wert wird:
   - auf dem **7-Segment-Display** angezeigt
   - zur **Ampelsteuerung** verwendet  
4. Bei Werten ≥1400 ppm blinkt die **rote LED** als Lüftungswarnung


---

## 🖼️ Verdrahtungsdiagramm / Screenshot

![Verdrahtung / Screenshot](./docs/co2_sensor_kicad.png)


---

## 🎯 Ziel des Projekts

- Raumluftqualität sichtbar machen  
- Konzentrationsfähigkeit verbessern  
- Energieeffizientes Lüften ermöglichen  
- Demonstrationsprojekt für IoT & Umwelttechnik

---

## 📄 Lizenz

MIT License – siehe [LICENSE](LICENSE) Datei
