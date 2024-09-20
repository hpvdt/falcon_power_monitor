#ifndef MCP3465_HEADER
#define MCP3465_HEADER

#include <Arduino.h>
#include <SPI.h>

// Internal Register Map
enum REG_MCP3465 : uint8_t {
    MCP3465_REG_ADC_DATA    = 0x0,
    MCP3465_REG_C0          = 0x1,
    MCP3465_REG_C1          = 0x2,
    MCP3465_REG_C2          = 0x3,
    MCP3465_REG_C3          = 0x4,
    MCP3465_REG_IRQ         = 0x5,
    MCP3465_REG_MUX         = 0x6,
    MCP3465_REG_SCAN        = 0x7,
    MCP3465_REG_TIMER       = 0x8,
    MCP3465_REG_OFFSETCAL   = 0x9,
    MCP3465_REG_GAINCAL     = 0xA,
    MCP3465_REG_LOCK        = 0xD,
    MCP3465_REG_CRCCFG      = 0xF
};

typedef enum {
    MCP3465_COMM_ADC_CONV_START = 0x28,
    MCP3465_COMM_ADC_STBY       = 0x2C,
    MCP3465_COMM_ADC_SHDN       = 0x30,
    MCP3465_COMM_FULL_SHDN      = 0x34,
    MCP3465_COMM_FULL_RST       = 0x38,
    MCP3465_COMM_STATIC_READ    = 0x01, // Register address goes in bits [5:2]
    MCP3465_COMM_INCR_WRITE     = 0x02, // Register address goes in bits [5:2]
    MCP3465_COMM_INCR_READ      = 0x03  // Register address goes in bits [5:2]
} MCP3565Command_t;

typedef enum _MCP3465Mux : uint8_t {
    MCP3465_MUX_CH0     = 0x0,
    MCP3465_MUX_CH1     = 0x1,
    MCP3465_MUX_AGND    = 0x8,
    MCP3465_MUX_AVDD    = 0x9,
    MCP3465_MUX_REFIN_P = 0xB,
    MCP3465_MUX_REFIN_M = 0xC,
    MCP3465_MUX_TEMP_P  = 0xD,
    MCP3465_MUX_TEMP_M  = 0xE,
    MCP3465_MUX_INT_VCM = 0xF
} MCP3465Mux_t;

typedef enum _MCP3465ClkSource : uint8_t {
    MCP3465_CLK_EXT             = 0x0,
    MCP3465_CLK_INT             = 0x2,
    MCP3465_CLK_INT_WITH_OUT    = 0x3 // Outputs AMCLK on SCK
} MCP3465ClkSource_t;

typedef enum _MCP3465ADCConvMode : uint8_t {
    MCP3465_ADC_MODE_ONE_SHOT_SHTDN  = 0x0,
    MCP3465_ADC_MODE_ONE_SHOT_STBY   = 0x2,
    MCP3465_ADC_MODE_CONTINUOUS      = 0x3
} MCP3465ADCConvMode_t;

typedef enum _MCP3465ADCMode :uint8_t {
    MCP3465_MODE_SHUTDOWN    = 0x0,
    MCP3465_MODE_STANDBY     = 0x2,
    MCP3465_MODE_CONVERSION  = 0x3
} MCP3465ADCMode_t;

typedef enum _MCP3465VRef : uint8_t {
    MCP3465_VREF_INT = 0x1,
    MCP3465_VREF_EXT = 0x0
} MCP3465VRef_t;

typedef enum _MCP3465Gain : uint8_t {
    MCP3465_GAIN_13 = 0x0,  // 1/3
    MCP3465_GAIN_01 = 0x1,
    MCP3465_GAIN_02 = 0x2,
    MCP3465_GAIN_04 = 0x3,
    MCP3465_GAIN_08 = 0x4,
    MCP3465_GAIN_16 = 0x5,
    MCP3465_GAIN_32 = 0x6,  // 16x analog 2x digital
    MCP3465_GAIN_64 = 0x7   // 16x analog 4x digital
} MCP3465Gain_t;

typedef enum _MCP3465Format : uint8_t {
    MCP3465_FORMAT_16               = 0x0,
    MCP3465_FORMAT_32_LEFT_ALIGNED  = 0x1, // Appended with 0x____0000
    MCP3465_FORMAT_32_SIGN_EXTENDED = 0x2, // 8-bit sign extension, 16-bit data
    MCP3465_FORMAT_32_SIGN_WITH_ID  = 0x3, // 4-bits channel ID, 12-bit sign extension, 16-bit data
} MCP3465Format_t;

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
    void set_input_mux(MCP3465Mux_t pos, MCP3465Mux_t neg);
    uint32_t read_adc_raw();
    void set_adc_mode(MCP3465ADCMode_t mode);
    void set_clock_source(MCP3465ClkSource_t clock);
    void set_voltage_reference(MCP3465VRef_t reference);
    void set_gain(MCP3465Gain_t gain);
    void set_conversion_mode(MCP3465ADCConvMode_t mode);
    void set_data_format(MCP3465Format_t format);
    uint8_t read_interrupts();
};





#endif