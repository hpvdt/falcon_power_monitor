#include <Arduino.h>
#include <SPI.h>

// Internal Register Map
typedef enum {
    REG_ADC_DATA  = 0x0,
    REG_CONFIG_0  = 0x1,
    REG_CONFIG_1  = 0x2,
    REG_CONFIG_2  = 0x3,
    REG_CONFIG_3  = 0x4,
    REG_IRQ       = 0x5,
    REG_MUX       = 0x6,
    REG_SCAN      = 0x7,
    REG_TIMER     = 0x8,
    REG_OFFSETCAL = 0x9,
    REG_GAINCAL   = 0xA,
    REG_LOCK      = 0xD,
    REG_CRCCFG    = 0xF
} MCP3465Reg;

// Command structure
typedef enum {
    COMM_ADC_CONV_START = 0x28,
    COMM_ADC_STBY       = 0x2C,
    COMM_ADC_SHDN       = 0x30,
    COMM_FULL_SHDN      = 0x34,
    COMM_FULL_RST       = 0x38,
    COMM_STATIC_READ    = 0x01, // Register address goes in bits [5:2]
    COMM_INCR_WRITE     = 0x02, // Register address goes in bits [5:2]
    COMM_INCR_READ      = 0x03  // Register address goes in bits [5:2]
} MCP3565CommandType;

const int ADC_ADDR = 1;

// SPI communication settings
const SPISettings SPI_SETTINGS = SPISettings(20e6, MSBFIRST, SPI_MODE0);

const int CS = PIN_PB0;

// Read registers
uint32_t readRegStat(MCP3465Reg reg, int num_bytes) {
    uint8_t command = 0;
    command = (ADC_ADDR << 6) | (reg << 2) | COMM_STATIC_READ;

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

// Write to register
void writeReg(MCP3465Reg reg, uint32_t data, int num_bytes) {
    uint8_t command = 0;
    int send_data = 0;
    command = (ADC_ADDR << 6) | (reg << 2) | COMM_INCR_WRITE;

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