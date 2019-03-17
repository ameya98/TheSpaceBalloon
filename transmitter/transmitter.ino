/*  
 *  GPS Tracker + Radio Transmitter
 *  Ameya Daigavane
 *  Code Snippets from UKHAS.
*/ 
 
#define RADIOPIN 13
 
#include <string.h>
#include <util/crc16.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

char infostring[1000];
 
void setup() {                
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println(F("The Space Balloon"));
  Serial.println(F("by Equinox, IIT Guwahati"));
  Serial.println();
  
  pinMode(RADIOPIN,OUTPUT); 
}
 
void loop() {
  while(ss.available() > 0){
    if(gps.encode(ss.read())){
        // Get GPS data and store in infostring.
        getGPSInfo();

        // Compute checksum.
        unsigned int checksum_val = gps_CRC16_checksum(infostring);
        char checksum_str[6];
        sprintf(checksum_str, "*%04X\n", checksum_val);
        strcat(infostring, " ");
        strcat(infostring, checksum_str);
        strcat(infostring, "\n\n");
        
        // Send over RTTY.
        rtty_txstring(infostring);

        // Print to serial monitor, to verify.
        Serial.println(infostring);
        
        // Wait for a while.
        delay(2000);
    }   
  }
}
 
 
void rtty_txstring (char * string)
{
 
  /* Simple function to sent a char at a time to 
     ** rtty_txbyte function. 
    ** NB Each char is one byte (8 Bits)
    */
 
  char c;
 
  c = *string++;
 
  while ( c != '\0')
  {
    rtty_txbyte (c);
    c = *string++;
  }
}
 
 
void rtty_txbyte (char c)
{
  /* Simple function to sent each bit of a char to 
    ** rtty_txbit function. 
    ** NB The bits are sent Least Significant Bit first
    **
    ** All chars should be preceded with a 0 and 
    ** proceded with a 1. 0 = Start bit; 1 = Stop bit
    **
    */
 
  int i;
 
  rtty_txbit (0); // Start bit
 
  // Send bits for for char LSB first 
 
  for (i=0;i<7;i++) // Change this here 7 or 8 for ASCII-7 / ASCII-8
  {
    if (c & 1) rtty_txbit(1); 
 
    else rtty_txbit(0); 
 
    c = c >> 1;
 
  }
 
  rtty_txbit (1); // Stop bit
  rtty_txbit (1); // Stop bit
}
 
void rtty_txbit (int bit)
{
  if (bit)
  {
    // high
    digitalWrite(RADIOPIN, HIGH);
  }
  else
  {
    // low
    digitalWrite(RADIOPIN, LOW);
 
  }
 
  //                  delayMicroseconds(3370); // 300 baud
  delayMicroseconds(10000); // For 50 Baud uncomment this and the line below. 
  delayMicroseconds(10150); // You can't do 20150 it just doesn't work as the
                            // largest value that will produce an accurate delay is 16383
                            // See : http://arduino.cc/en/Reference/DelayMicroseconds
 
}
 
uint16_t gps_CRC16_checksum (char *string)
{
  size_t i;
  uint16_t crc;
  uint8_t c;
 
  crc = 0xFFFF;
 
  // Calculate checksum ignoring the first two $s
  for (i = 2; i < strlen(string); i++)
  {
    c = string[i];
    crc = _crc_xmodem_update (crc, c);
  }
 
  return crc;
}    


void getGPSInfo() {
  sprintf(infostring, "Loc: "); 

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
    strcat(infostring, "--");
  }

  strcat(infostring, "  DT (UTC): ");
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
    strcat(infostring, "--  ");  
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
    strcat(infostring, "--.");  
  }
}
