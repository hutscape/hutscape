#include <SPI.h>
#include "epd1in54.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

unsigned char image[1024];
Paint paint(image, 0, 0);
Epd epd;
int count = 0;
char count_string[] = {'1', '2', '3'};

void setup() {
  SerialUSB.begin(9600);
  while (!SerialUSB) { }
  SerialUSB.println("Start E-ink display...");
}

void loop() {
  count++;

  count_string[2] = count % 10 + '0';
  count_string[1] = count / 10 % 10 + '0';
  count_string[0] = count / 100 + '0';

  SerialUSB.println(count_string);

  if (epd.Init(lut_full_update) != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_0);
  paint.SetWidth(200);
  paint.SetHeight(24);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(10, 4, count_string, &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 50, paint.GetWidth(), paint.GetHeight());

  epd.DisplayFrame();

  delay(2000);
  epd.Sleep();
}
