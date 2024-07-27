#include <Arduino.h>
#include <SPI.h>
#include "MCP3465.hpp"

const int CS_PIN = PIN_PB0;
const int ADC_ADDRESS = 0b01;  // MCP3465 has hardcoded address bits

MCP3465 adc(&SPI, CS_PIN, ADC_ADDRESS);

void setup() {
  // start serial communication
  Serial.begin(9600);

  // Set the pinmode
  pinMode(CS_PIN, OUTPUT);

  adc.setup();
}

void loop() { 
  Serial.println("Hello");
}