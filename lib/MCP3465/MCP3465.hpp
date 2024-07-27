#ifndef MCP3465_HEADER
#define MCP3465_HEADER

#include <Arduino.h>
#include <SPI.h>

// Internal Register Map
enum REG_MCP3465 : uint8_t {
    ADC_DATA    = 0x0,
    C0          = 0x1,
    C1          = 0x2,
    C2          = 0x3,
    C3          = 0x4,
    IRQ         = 0x5,
    MUX         = 0x6,
    SCAN        = 0x7,
    TIMER       = 0x8,
    OFFSETCAL   = 0x9,
    GAINCAL     = 0xA,
    LOCK        = 0xD,
    CRCCFG      = 0xF
};

class MCP3465
{
private:
    SPIClass* _spi;
    const uint8_t CS_PIN;
    const uint8_t ADC_ADDRESS;
public:
    MCP3465(SPIClass* spi_bus, int8_t CS, uint8_t addr);
    int setup();
    uint32_t read_reg_static(REG_MCP3465 reg, uint8_t num_bytes);
    void write_reg(REG_MCP3465 start_reg, uint32_t data, int num_bytes);
};





#endif