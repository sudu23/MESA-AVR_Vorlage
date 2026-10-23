/* 
 * File:   MCP23008.c
 * Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include <stdio.h>
#include "MCP23008.h"

extern bool TWI1_Write(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_Read(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_IsBusy(void);

// Register-Adressen des MCP23008
#define MCP23008_IODIR   0x00
#define MCP23008_IPOL    0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL  0x03
#define MCP23008_INTCON  0x04
#define MCP23008_IOCON   0x05
#define MCP23008_GPPU    0x06
#define MCP23008_INTF    0x07
#define MCP23008_INTCAP  0x08
#define MCP23008_GPIO    0x09
#define MCP23008_OLAT    0x0A

static const uint8_t mcp23008_addresses[MCP23008_NUM_DEVICES] = {
    MCP23008_PF_ADDR,
    MCP23008_PG_ADDR,
    MCP23008_MIXEDSIGNALS_ADDR
};

// Shadow-Register zur Speicherung des aktuellen Ausgangszustands.
static uint8_t shadow_registers[MCP23008_NUM_DEVICES] = {
    0xFF, // IC1 PORTF
    0xFF, // IC2 PORTG
    0xFF  // IC3 MIXED SIGNALS
};

// Interne Hilfsfunktion: Schreibt ein einzelnes Register
static bool MCP23008_WriteRegister(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    uint8_t buffer[2];
    buffer[0] = reg_addr;
    buffer[1] = data;
    
    return TWI1_Write(i2c_addr, buffer, 2);
}

// Interne Hilfsfunktion: Liest ein einzelnes Register
static bool MCP23008_ReadRegister(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *data) {
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    if (!TWI1_Write(i2c_addr, &reg_addr, 1)) {
        return false;
    }
    
    timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    return TWI1_Read(i2c_addr, data, 1);
}

// Interne Hilfsfunktion: Wartet bis TWI frei ist und schreibt das Shadow-Register in den GPIO-Port
static bool MCP23008_Sync(mcp23008_id_t id) {
    if (id >= MCP23008_NUM_DEVICES) return false;
    return MCP23008_WriteRegister(mcp23008_addresses[id], MCP23008_GPIO, shadow_registers[id]);
}

bool MCP23008_Init(void) {
    bool success = true;
    
    for (int i = 0; i < MCP23008_NUM_DEVICES; i++) {
        // IODIR konfigurieren: 
        // Fuer IC3 definieren wir P4, P5, P6 als Ausgang (0), P7 als Eingang (1), Rest nach Bedarf (hier standardmaessig 0xFF)
        uint8_t iodir_val = 0xFF;
        if (i == MCP23008_MIXEDSIGNALS) {
            iodir_val = ~( (1 << IC3_LED1_PIN) | (1 << IC3_LED2_PIN) | (1 << IC3_DS3234_RST_PIN) );
        }
        
        success &= MCP23008_WriteRegister(mcp23008_addresses[i], MCP23008_IODIR, iodir_val);
        success &= MCP23008_WriteRegister(mcp23008_addresses[i], MCP23008_IPOL, 0x00);
        success &= MCP23008_WriteRegister(mcp23008_addresses[i], MCP23008_GPINTEN, 0x00);
        success &= MCP23008_WriteRegister(mcp23008_addresses[i], MCP23008_GPPU, 0x00);
        
        // Startzustand schreiben
        success &= MCP23008_WriteRegister(mcp23008_addresses[i], MCP23008_GPIO, shadow_registers[i]);
    }
    
    return success;
}

bool MCP23008_WriteByte(mcp23008_id_t id, uint8_t value) {
    if (id >= MCP23008_NUM_DEVICES) return false;
    
    shadow_registers[id] = value;
    return MCP23008_Sync(id);
}

bool MCP23008_ReadByte(mcp23008_id_t id, uint8_t *value) {
    if (id >= MCP23008_NUM_DEVICES || value == NULL) return false;
    
    return MCP23008_ReadRegister(mcp23008_addresses[id], MCP23008_GPIO, value);
}

bool MCP23008_WritePin(mcp23008_id_t id, uint8_t pin, bool level) {
    if (id >= MCP23008_NUM_DEVICES || pin > 7) return false;
    
    if (level) {
        shadow_registers[id] |= (1 << pin);
    } else {
        shadow_registers[id] &= ~(1 << pin);
    }
    
    return MCP23008_Sync(id);
}

bool MCP23008_ReadPin(mcp23008_id_t id, uint8_t pin, bool *level) {
    if (id >= MCP23008_NUM_DEVICES || pin > 7 || level == NULL) return false;
    
    uint8_t current_port_state = 0;
    if (!MCP23008_ReadByte(id, &current_port_state)) {
        return false;
    }
    
    *level = (current_port_state & (1 << pin)) ? true : false;
    return true;
}

// --- Komfortfunktionen fuer IC3 ---
bool MCP23008_MIXEDSIGNALS_SetLED1(bool turnOn) {
    return MCP23008_WritePin(MCP23008_MIXEDSIGNALS, IC3_LED1_PIN, !turnOn);
}

bool MCP23008_MIXEDSIGNALS_SetLED2(bool turnOn) {
    return MCP23008_WritePin(MCP23008_MIXEDSIGNALS, IC3_LED2_PIN, !turnOn);
}

bool MCP23008_MIXEDSIGNALS_SetDS3234Reset(bool active) {
    return MCP23008_WritePin(MCP23008_MIXEDSIGNALS, IC3_DS3234_RST_PIN, !active);
}

bool MCP23008_MIXEDSIGNALS_GetDS3234Interrupt(bool *level) {
    return MCP23008_ReadPin(MCP23008_MIXEDSIGNALS, IC3_DS3234_INT_PIN, level);
}