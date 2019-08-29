

1) download/install the latest Arduino.cc IDE.

2) in the File > Preferences window in the IDE paste the following line into the Additional Boards Manager URL:

https://dl.espressif.com/dl/package_esp32_index.json

3) go to Tools > Board > Board Manager

4) type ESP32 and Install the new hardware libraries

5) you will be able to find all the ESP32 boards including the Heltec Wifi 32 in the IDE’s board selector:
     "ESP32 Dev Module"

6) go to Tools > Manage Libraries. Search and install those:
     "ESP8266 and ESP32 Oled Driver for SSD1306 display"
     "HX711_ADC"


You are set to compile the 'cgscale.ino' file and flash the board.


Under linux, you can run my Makefile (`make`) to compile and flash to the board.


