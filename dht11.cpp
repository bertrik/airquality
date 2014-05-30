#include <stdint.h>
#include "Arduino.h"
#include "dht11.h"

const int MAX_BIT_US = 100;

DHT11::DHT11(int pin)
{
    dht11_pin = pin;
}

void DHT11::init(void)
{
    // default pin state is high (pulled up)
    pinMode(dht11_pin, INPUT);

    // wait for initialisation
    unsigned long m = millis();
    if (m < 1000) {
        delay(1000 - m);
    }
}

static int dht_bit(int pin)
{
    // wait for rising edge
    unsigned long t0 = micros();
    while (digitalRead(pin) == LOW) {
        if ((micros() - t0) > MAX_BIT_US) {
            return -1;
        }
    }
    
    // wait for falling edge
    unsigned long t1 = micros();
    while (digitalRead(pin) == HIGH) {
        if ((micros() - t1) > MAX_BIT_US) {
            return -2;
        }
    }
    
    // return length of high part
    return (int)(micros() - t1);
}

bool DHT11::read(int *humidity, int *temperature)
{
    uint8_t buf[5];  
  
    // send wake up pulse
    pinMode(dht11_pin, OUTPUT);
    digitalWrite(dht11_pin, LOW);
    delay(18);
    pinMode(dht11_pin, INPUT);
    delayMicroseconds(50);
    
    // check start bit
    if (dht_bit(dht11_pin) < 0) {
        return false;
    }
    
    // read 40 data bits
    for (int i = 0; i < 5; i++) {
        uint8_t b = 0;
        for (int j = 0; j < 8; j++) {
            int us = dht_bit(dht11_pin);
            b = b << 1;
            if (us >= 48) {
                b |= 1;
            }
        }
        buf[i] = b;
    }
    
    // verify checksum
    uint8_t sum = buf[0] + buf[1] + buf[2] + buf[3];
    if (sum != buf[4]) {
        return false;
    }
    
    *humidity = buf[0];
    *temperature = buf[2];
    return true;
}

