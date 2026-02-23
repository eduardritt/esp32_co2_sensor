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

SensirionI2cScd4x scd4x;

#define LED_GREEN 27
#define LED_YELLOW 26
#define LED_RED 25

bool sensorOK = true;

void blinkError() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(300);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  delay(300);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  scd4x.begin(Wire, 0x62);

  scd4x.stopPeriodicMeasurement();
  delay(500);

  if (scd4x.startPeriodicMeasurement() != 0) {
    sensorOK = false;
  }
}

void loop() {

  if (!sensorOK) {
    blinkError();
    return;
  }

  uint16_t co2;
  float temperature;
  float humidity;

  delay(5000);

  uint16_t error = scd4x.readMeasurement(co2, temperature, humidity);

  if (error) {
    Serial.println("Sensorfehler!");
    sensorOK = false;
    return;
  }

  Serial.print("CO2: ");
  Serial.println(co2);

  Serial.print("Temp: ");
  Serial.println(temperature);

  Serial.print("Feuchtigkeit: ");
  Serial.println(humidity);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

  if (co2 < 800) {
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (co2 < 1400) {
    digitalWrite(LED_YELLOW, HIGH);
  }
  else {
    // Rot blinkt
    digitalWrite(LED_RED, HIGH);
    delay(300);
    digitalWrite(LED_RED, LOW);
    delay(300);
  }
}
