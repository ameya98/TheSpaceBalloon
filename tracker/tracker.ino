/*
 * The Space Balloon
 * Radio Tracking Code for the Arduino
 * 
 * Author: Ameya Daigavane
 * Code fragments taken from DeviceExample.ino in the TinyGPS++ library.
 */

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// Stores the GPS info as a string
char infostring[1000];

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println(F("The Space Balloon"));
  Serial.println(F("by Equinox, IIT Guwahati"));
  Serial.println();
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()));
      getGPSInfo();
      displayInfo();
      delay(2000);
      
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo() {
  Serial.println(infostring);
}

void getGPSInfo() {
  sprintf(infostring, "Location: "); 

  // Buffer string for converting values.
    char buff[10];

  if (gps.location.isValid()) {    
    // Latitude.
    dtostrf(gps.location.lat(), 4, 6, buff); 
    strcat(infostring, buff);

    // Separator.
    strcat(infostring, ", ");

    // Longitude.
    dtostrf(gps.location.lng(), 4, 6, buff); 
    strcat(infostring, buff);
    
  } else {
    strcat(infostring, "INVALID");
  }

  strcat(infostring, "  Date/Time (UTC): ");
  if (gps.date.isValid()) {
    // Date.
    itoa(gps.date.day(), buff, 10);
    strcat(infostring, buff);
    strcat(infostring, "/");

    // Month.
    itoa(gps.date.month(), buff, 10);
    strcat(infostring, buff);
    strcat(infostring, "/");

    // Year.
    itoa(gps.date.year(), buff, 10);
    strcat(infostring, buff);
    strcat(infostring, "  ");
  } else {
    strcat(infostring, "INVALID  ");  
  }

  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) strcat(infostring, "0");
    itoa(gps.time.hour(), buff, 10);
    strcat(infostring, buff);

    strcat(infostring, ":");
    if (gps.time.minute() < 10) strcat(infostring, "0");
    itoa(gps.time.minute(), buff, 10);
    strcat(infostring, buff);

    strcat(infostring, ":");
    if (gps.time.second() < 10) strcat(infostring, "0");
    itoa(gps.time.second(), buff, 10);
    strcat(infostring, buff);
    
    strcat(infostring, ".");  
    if (gps.time.centisecond() < 10) strcat(infostring, "0");
    itoa(gps.time.centisecond(), buff, 10);
    strcat(infostring, buff);
  } else {
    strcat(infostring, "INVALID.");  
  }
}
