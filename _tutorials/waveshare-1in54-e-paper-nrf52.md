---
layout: tutorials
title: Waveshare 1.54 inch with nRF52
hardware:
  - arduino
  - nRF52
  - waveshare
  - e-paper
  - e-ink
references:
  - name: Waveshare 1.54 inch e-paper module
    url: https://www.waveshare.com/product/1.54inch-e-Paper-Module.htm
  - name: Waveshare 1.54 inch e-paper schematic
    url: https://www.waveshare.com/w/upload/5/5b/1.54inch_e-Paper_Schematic.pdf
  - name: E-Ink Arduino library
    url: https://github.com/soonuse/epd-library-arduino
  - name: Code example for 1.54 inch e-paper
    url: https://github.com/waveshare/e-Paper/blob/master/Arduino/epd1in54/epd1in54.ino
  - name: Arduino SPI
    url: https://www.arduino.cc/en/reference/SPI
  - name: Adafruit nRF52 Feather pinout
    url: https://cdn-learn.adafruit.com/assets/assets/000/046/248/original/microcontrollers_Feather_NRF52_Pinout_v1.2-1.png?1504885794
---

The 4 non-SPI pins are defined in `epdif.h` file:

```c
// Pin definition
#define RST_PIN         2   // A0
#define DC_PIN          3   // A1
#define CS_PIN          4   // A2
#define BUSY_PIN        5   // A3
```
