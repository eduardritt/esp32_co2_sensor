/*
  Projekt: ESP32 CO² Sensor
  
  Beschreibung: 
        Europäische Norm EN 13779 bewertet die Konzentration von CO2 in Innenräumen in vier Qualitätsstufen. 
        Als hygienisch inakzeptabel gilt die Raumluftqualität ab 2.000 ppm.

        
        CO2 Gehalt im ppm   |  	CO2 in %	    |   Qualitätsstufe
        -----------------------------------------------------------
        Unter 800	          |   < 0,08 %	    | Hohe Raumluftqualität
        800 - 1.000	        |   0,08 - 0,1 %	| Mittlere Raumluftqualität
        1.000 - 1.400       |   0,1 - 0,14 %	| Mäßige Raumluftqualität
        Über 1.400          |   >0,14 %	      | Niedrige Raumluftqualität
  
  Version: v.1.0

*/

#include <Wire.h>
#include <SensirionI2cScd4x.h>
#include "MAX7SegmentDisplay.h"

// ----------- MAX7219 Pins -----------
#define DIN 23
#define CS 5
#define CLK 18

MAX7SegmentDisplay display(DIN, CS, CLK);

// ----------- Sensor -----------
SensirionI2cScd4x scd4x;

// ----------- LEDs -----------
#define LED_GREEN 27
#define LED_YELLOW 26
#define LED_RED 25

bool redBlinkState = false;
unsigned long lastBlinkTime = 0;
unsigned long lastMeasurement = 0;

uint16_t currentCO2 = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Display
  display.setBright(10);
  display.setDigitLimit(8);
  display.clear();

  // Sensor starten
  scd4x.begin(Wire, 0x62);
  scd4x.stopPeriodicMeasurement();
  delay(500);
  scd4x.startPeriodicMeasurement();
}

void loop() {

  unsigned long now = millis();

  // ----------- CO2 Messung alle 5 Sekunden -----------
  if (now - lastMeasurement >= 5000) {
    lastMeasurement = now;

    uint16_t co2;
    float temperature;
    float humidity;

    uint16_t error = scd4x.readMeasurement(co2, temperature, humidity);

    if (!error && co2 > 400) {
      currentCO2 = co2;
      Serial.print("CO2: ");
      Serial.println(currentCO2);

      displayCO2(currentCO2);
    } else {
      Serial.println("Sensorfehler!");
      display.clear();
      blinkAllLEDs();
      return;
    }
  }

  // ----------- LED Steuerung -----------
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);

  if (currentCO2 < 800) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  else if (currentCO2 < 1400) {
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  else {
    // Rot blinkt alle 300ms
    if (now - lastBlinkTime >= 300) {
      lastBlinkTime = now;
      redBlinkState = !redBlinkState;
      digitalWrite(LED_RED, redBlinkState);
    }
  }
}

// ----------- CO2 Anzeige -----------
void displayCO2(uint16_t value) {
  display.clear();
  display.printDigit(value);  // linksbündig
}

// ----------- Fehlerblinken -----------
void blinkAllLEDs() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(200);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}
