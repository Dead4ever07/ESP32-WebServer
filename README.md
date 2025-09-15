# ESP32 Web Server

This server is sometimes available at the address: http://94.60.93.1/

## Hardware

Board: ESP32-S3
CPU: Xtensa Dual-code 32-bit 240 MHz
ROM: 384KB
SRAM: 512KB

## Advantages

Doing a small server with esp32 at home is a easy way to have a micro website, it is cheap to aquire and it is cheap to maintain.

Fun Fact: PowerWise it consumes ~0.250w (20x less than a lamp)


## Disadvantages

The project is barely scalable due to the reduced rom size. Not recomended building an API due to the increased complexity of one.


## Dependencies

To do this i have used the libraries declared in the .ino file.

The <LittleFS.h> to be installed it is necessary to download a modified version of the ESP32 library available in their github(https://github.com/lorol/LITTLEFS/releases/tag/1.0.6)


## Pictures

![Project Picture](/Pictures/Project%20Picture.jpeg)