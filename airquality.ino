#include "DHT.h"

#define PIN A1

DHT dht(3, DHT11);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world!");
  pinMode(PIN, INPUT);
  analogReference(INTERNAL);

  dht.begin();
}

void loop() {
//#if 1
  int val = analogRead(PIN);
  Serial.print("analog=");
  Serial.println(val, DEC);
//#else

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  Serial.print("T=");
  Serial.print(t);
  Serial.print(", ");
  Serial.print("H=");
  Serial.println(h);

//#endif
  delay(500);
}
