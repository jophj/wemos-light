#include <ESP8266WiFi.h>
const int relayPin = D1;
const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  Serial.print("Setup done. LED and relay LOW\r\n");
}


int status = HIGH;
void loop() {
  digitalWrite(ledPin, status);
  digitalWrite(relayPin, status);

  Serial.print("Status: "); Serial.print(status); Serial.print("\r\n");


  if (status == LOW) status = HIGH;
  else status = LOW;

  delay(1000);
}
