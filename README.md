# cg-scale-wifi-oled

A fresh, completely refactored design and rewrote code highly inspired by the original and innovative Olkal cg-scale design.

<img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/photo-stormbird3.jpg" width="500" alt="CG Scale" align="center" />

<img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/photo-folded.jpg" width="350" alt="CG Scale folded" /><img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/photo-assembly-full1.jpg" width="350" alt="CG Scale ready" />

## Features

- recent ESP32 wifi-bluetooth-oled board, mainstream and low cost (sub $10) - all-in-one
- minimal and well designed parts (3d printing)
- foldable and easy transport
- manage from a parkflyer, 1m DLG to bigger aerobatic motorised planes (and tunable), and of course F3X gliders
- full remote control: tare, configuration and monitoring via Wifi
- precise tuning
- configuration saved in the ESP32 flash memory
- standalone display with the ESP32 oled
- powered with a simple 1S lipo, a 5V USB battery, Li-Ion 18650, ... 
- multi-language design (included: english, french)
- complete documentation
- easy code upload in the ESP32 with the arduino.cc IDE (few steps documented in 'soft' folder)

The scale 3d parts are parametric and designed with openscad. You can edit the SCAD file and regenerate the STL.

## Comment

Photos were taken from my development unit.
The available parts are now enhanced in strength and stiffness at key points.
Depending on your rc models, you can even trim the rods to lower length to get even more stiffness.
The girder (holding the rods vertically), with its inverted V-shape, is designed to lock itself on the support when a weight is applied.

## Documentation

- [x] Circuit diagram: [CG Scale Circuit Diagram](documentation/circuit-diagram.pdf)
- [x] Assembly: [CG Scale Assembly](documentation/assembly.pdf)
- [x] Manual: [CG Scale Manual](documentation/manual.pdf)
- [x] Soft: [CG Scale Soft](soft/)

<img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/photo-stormbird1.jpg" width="500" alt="CG Scale" align="center" />

## Display/Interface

#### Standalone OLED

<img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/photo-board-stormbird.jpg" width="500" alt="CG Scale board display" align="center" />

#### Wifi interface

<img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/screenshot-configuration.jpg" width="500" alt="Wifi interface" align="center" /> <img src="https://github.com/guillaumef/cg-scale-wifi-oled/blob/master/pix/screenshot-stormbird.jpg" width="500" alt="Wifi interface" align="center" />
