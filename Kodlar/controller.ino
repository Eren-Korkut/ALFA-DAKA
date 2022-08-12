#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int RXPin = 6;
int TXPin = 7;

int GPSBaud = 9600;

const int qAnalogPin = A3;

const int rcLedPin = 3;

int ppm;
int voiceLevel;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
    gpsSerial.begin(GPSBaud);
    pinMode(rcLedPin, OUTPUT);
    lcd.begin(16, 2);
//  lcd.begin();
    Serial.begin(9600);
    lcd.setCursor(0, 0);
    lcd.print("   ALFA DAKA");
    delay(3000);
    lcd.clear();
}

void loop() {

while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  
  ppm = analogRead(qAnalogPin);
  char string[100] = "PPM: ";
  char buffer[10];
  itoa(ppm, buffer, 10);
  strcat(string, buffer);
  lcd.setCursor(0, 0);
  lcd.print(string);
  lcd.setCursor(0, 1);
  lcd.print(gps.location.lat(), gps.location.lng());
  delay(1000);
  lcd.clear();
  }
  
