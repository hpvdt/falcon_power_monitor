#include <Arduino.h>
#include <SPI.h>

// INternal Register Map
enum MCP3465 {

  ADCdata = 0x0,
  C0 = 0x1,
  C1 = 0x2,
  C2 = 0x3,
  C3 = 0x4,
  IRQ = 0x5,
  MUX = 0x6,
  SCAN = 0x7,
  TIMER = 0x8,
  OFFSETCAL = 0x9,
  GAINCAL = 0xA,
  LOCK = 0xD,
  CRCCFG = 0xF

};

// SPI communication settings
const SPISettings SPI_SETTINGS = SPISettings(20e6, MSBFIRST, SPI_MODE0);

const int CS = PIN_PB0;

// Read registers
uint32_t readRegStat(MCP3465 reg, int num_bytes) {
  uint8_t command = 0;
  const int addr = 1;
  int regAddr = 0;
  regAddr = reg << 2;

  command = (addr << 6) + regAddr + 1;

  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite(CS, LOW);

  // Send read command
  SPI.transfer(command);

  // Get data
  uint32_t data = 0;
  for (int i = 0; i < num_bytes; i++) {
    data = data << 8;
    data += SPI.transfer(0);
  }

  digitalWrite(CS, HIGH);
  SPI.endTransaction();

  return data;
}

// Write to registers
void writeReg(MCP3465 reg, uint32_t data, int num_bytes) {
  uint8_t command = 0;
  const int addr = 1;
  int send_data = 0;

  command = (addr << 6) + (reg << 2) + 0b10;

  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite(CS, LOW);

  // Send write command
  SPI.transfer(command);

  // send data
  for (int i = num_bytes; i > 0; i--) {
    send_data = (data >> ((i - 1) * 8));
    send_data = send_data & 0xFF;
    SPI.transfer(send_data);
  }

  digitalWrite(CS, HIGH);
  SPI.endTransaction();
}

void setup() {
  // start serial communication
  Serial.begin(9600);

  // Set the pinmode
  pinMode(CS, OUTPUT);

  // gets ATMega read
}

void loop() { Serial.println("Hello"); }