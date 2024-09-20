#include "MCP3465.hpp"
#include <Arduino.h>
#include <SPI.h>

// SPI communication settings
const SPISettings SPI_SETTINGS = SPISettings(20e6, MSBFIRST, SPI_MODE0);

MCP3465::MCP3465(SPIClass* spi_bus, int8_t CS, uint8_t addr) :
        CS_PIN(CS), ADC_ADDRESS(addr) {
    _spi = spi_bus;
}

int MCP3465::setup() {
    pinMode(CS_PIN, OUTPUT);

    return 0;
}

// Read registers
uint32_t MCP3465::read_reg_static(REG_MCP3465 reg, uint8_t num_bytes) {
    uint8_t command = 0;
    int regAddr = reg << 2;

    command = (ADC_ADDRESS << 6) + regAddr + MCP3465_COMM_STATIC_READ;

    _spi->beginTransaction(SPI_SETTINGS);
    digitalWrite(CS_PIN, LOW);

    // Send read command
    _spi->transfer(command);

    // Get data
    uint32_t data = 0;
    for (int i = 0; i < num_bytes; i++) {
        data = data << 8;
        data += _spi->transfer(0);
    }

    digitalWrite(CS_PIN, HIGH);
    _spi->endTransaction();

    return data;
}

// Write to registers (always incremental)
void MCP3465::write_reg(REG_MCP3465 start_reg, uint32_t data, int num_bytes) {
    uint8_t command = (ADC_ADDRESS << 6) + (start_reg << 2) + MCP3465_COMM_INCR_WRITE;

    _spi->beginTransaction(SPI_SETTINGS);
    digitalWrite(CS_PIN, LOW);

    // Send write command
    _spi->transfer(command);

    // send data
    for (int i = num_bytes; i > 0; i--) {
        uint8_t send_data = (data >> ((i - 1) * 8));
        send_data = send_data & 0xFF;
        _spi->transfer(send_data);
    }

    digitalWrite(CS_PIN, HIGH);
    _spi->endTransaction();
}
