# The Space Balloon
This is the source repository for the Space Balloon Project by Equinox, the Astronomy Club at the Indian Institute of Technology, Guwahati.

## Radio Tracking
The [Arduino Mega 2560](https://robokits.co.in/arduino/boards/arduino-mega-2560-r3-board) connects to the NXT2B Radio Transmitter sold by [Uputronics](https://store.uputronics.com/index.php?route=product/product&path=61&product_id=60), and the uBlox NEO-6M GPS Module, sold by [Robomart](https://robokits.co.in/wireless-solutions/gps-glonass/gps-module-neo-6m-ublox-with-micro-usb-interface?gclid=Cj0KCQjwsMDeBRDMARIsAKrOP7FtsVDHofjzGtLrRC6FFTopl2FRNuzXKjxqe9zFJWN8-V1Z6QYoBYAaAvQdEALw_wcB).  
Source code is in the **tracker** folder. 
* RX and TX pins are connected in the opposite way as the GPS Module.
* 5V DC is alright.
* Location fix occurred only after using a phone's GPS (set to Device Only mode) kept close by.
