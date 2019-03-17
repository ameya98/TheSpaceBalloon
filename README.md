# The Space Balloon
This is the source repository for the Space Balloon Project by Equinox, the Astronomy Club at the Indian Institute of Technology, Guwahati.

## GPS Tracking with Radio Transmission
The [Arduino Mega 2560](https://robokits.co.in/arduino/boards/arduino-mega-2560-r3-board) connects to the NXT2B Radio Transmitter sold by [Uputronics](https://store.uputronics.com/index.php?route=product/product&path=61&product_id=60), and the uBlox NEO-6M GPS Module, sold by [Robomart](https://robokits.co.in/wireless-solutions/gps-glonass/gps-module-neo-6m-ublox-with-micro-usb-interface?gclid=Cj0KCQjwsMDeBRDMARIsAKrOP7FtsVDHofjzGtLrRC6FFTopl2FRNuzXKjxqe9zFJWN8-V1Z6QYoBYAaAvQdEALw_wcB), with an antenna.  
The GPS module receives location and time information, and these are encoded as RTTY and sent via the NTX2B to the base station, where these signals are recieved with an SDR, and decoded on-the-fly with dl-fldigi.  
Source code is in the **transmitter** folder. For standalone checking of the GPS tracker, see the **tracker** folder.  
### Notes: 
* RX and TX pins are connected in the opposite way as the GPS module code suggests.
* 5V DC is alright for the GPS tracker.
* Location fix occurred only after using a phone's GPS (set to Device Only mode) kept close by.
* Baud rate 115200 for the serial monitor to see GPS data being transmitted by the Arduino. The Arduino will need to be connected to your laptop.
* Use dl-fldigi and CubicSDR to encode. Ensure the correct RTTY settings, and audible signals for dl-fldigi. For CubicSDR, use the LSB mode.
