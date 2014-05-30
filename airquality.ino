#include "dht11.h"

#define PIN A1

DHT11 dht11(2);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world!");
  pinMode(PIN, INPUT);
  analogReference(INTERNAL);

  dht11.init();
}

void loop() {
//#if 1
  int val = analogRead(PIN);
  Serial.print("analog=");
  Serial.println(val, DEC);
//#else
  
  int h, t;
  dht11.read(&h, &t);
  
  Serial.print("T=");
  Serial.print(t);
  Serial.print(", ");
  Serial.print("H=");
  Serial.println(h);

//#endif
  delay(1000);
}
