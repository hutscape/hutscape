---
layout: tutorials
title: Blinky nRF52
hardware:
  - nRF52
  - bluefruit
  - adafruit
  - feather
references:
  - name: Get started now with our most powerful Bluefruit board yet
    url: https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/introduction
  - name: Adafruit Feather nRF52 Bluefruit LE - nRF52832
    url: https://www.adafruit.com/product/3406
---

Create a blinky LED with Adafruit Bluefruit nRF52 breakout board.

Ensure the [boards URL is added](https://learn.sparkfun.com/tutorials/installing-arduino-ide/board-add-ons-with-arduino-board-manager) in Arduino IDE / CLI:

```
https://www.adafruit.com/package_adafruit_index.json
```

To use command line [arduino-cli](https://github.com/arduino/arduino-cli), install [Adafruit nRF52 nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) with `pip3`:

```
pip3 install --user adafruit-nrfutil
```

<img src="{{ site.url }}/assets/images/tutorials/blinky-nrf52-arduino-settings.png" alt="nRF52 settings on Arduino IDE">
