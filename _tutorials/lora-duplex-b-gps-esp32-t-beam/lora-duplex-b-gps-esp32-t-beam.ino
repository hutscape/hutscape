#include "src/gps/gps.h"
#include "src/oled/oled.h"
#include "src/lorap2p/lorap2p.h"

#define GPS_ACCURACY 7
#define PERIOD 2000

byte localAddress = 0xBB;
byte peerAddress = 0xAA;

unsigned long localGPSFixMillis;

long lastSendTime = 0;
int interval = PERIOD;
long haversine_distance = 0.0;

LatLong localLatlong = {0.0, 0.0};
LatLong destinationLatlong = {0.0, 0.0};

void setup() {
  Serial.begin(9600);
  Serial.println("Start LoRa GPS duplex");

  initGPS();
  initOLED();
  initLora();

  displayInitOLED();
}

void loop() {
  while (isGPSAvailable()) {
    getLatLong(&localLatlong);
    localGPSFixMillis = millis();
  }

  if (receiveLora(localAddress, &destinationLatlong.latitude, &destinationLatlong.longitude)) {
    // TODO: Takes note of the millis() when other node lat-long is received
    printStatus("Received", &destinationLatlong, peerAddress, localAddress);
  }

  if (millis() - lastSendTime > interval) {
    if (isGPSValid(&localLatlong)) {
      String latlongData = String(localLatlong.latitude, GPS_ACCURACY) + "," + String(localLatlong.longitude, GPS_ACCURACY);
      sendLora(latlongData, localAddress, peerAddress);

      haversine_distance = distance(localLatlong.latitude, localLatlong.longitude, destinationLatlong.latitude, destinationLatlong.longitude);

      Serial.print("Distance between 2 nodes: ");
      Serial.print(haversine_distance);
      Serial.println("m");

      String localMillisStr;
      getReadableTime(localGPSFixMillis, localMillisStr);

      displayOLED(localLatlong.latitude, localLatlong.longitude, haversine_distance, localMillisStr);
      printStatus("Sent", &localLatlong, localAddress, peerAddress);

      lastSendTime = millis();
      interval = random(1000) + PERIOD;
    }
  }
}

void printStatus(String status, struct LatLong *ll, byte addressA, byte addressB) {
  Serial.print(status + " latlong ");
  Serial.print(ll->latitude, GPS_ACCURACY);
  Serial.print(",");
  Serial.print(ll->longitude, GPS_ACCURACY);
  Serial.print(" from 0x" + String(addressA, HEX));
  Serial.println(" to 0x" + String(addressB, HEX));
}

bool isGPSValid(LatLong *localLatlong) {
  if (localLatlong->latitude == 0.000 || localLatlong->longitude == 0.000) {
    return false;
  }

  return true;
}

void getReadableTime(long millisTime, String &readableTime) {
  unsigned long seconds;
  unsigned long minutes;
  unsigned long hours;
  unsigned long days;

  seconds = millisTime / 1000;
  minutes = seconds / 60;
  hours = minutes / 60;
  days = hours / 24;
  millisTime %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  if (days > 0) {
    readableTime = String(days) + " ";
  }

  if (hours > 0) {
    readableTime += String(hours) + ":";
  }

  if (minutes < 10) {
    readableTime += "0";
  }
  readableTime += String(minutes) + ":";

  if (seconds < 10) {
    readableTime += "0";
  }
  readableTime += String(seconds) + " ago";
}