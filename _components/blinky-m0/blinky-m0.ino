#define LED 13  // Pin 13 is connected to an on-board Blue LED

void setup() {
  pinMode(LED, OUTPUT);

  SerialUSB.begin(115200);
  delay(100);
  SerialUSB.println("Start!");
}

void loop() {
  SerialUSB.println("HIGH");
  digitalWrite(LED, HIGH);
  delay(500);

  SerialUSB.println("LOW");
  digitalWrite(LED, LOW);
  delay(500);
}