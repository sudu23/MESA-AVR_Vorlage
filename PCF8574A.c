/*
 * PCF8574A.c
 * Version: 1.0.0
 *
 *  Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include <stdio.h>
#include "PCF8574A.h"

extern bool TWI1_Write(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_Read(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_IsBusy(void);

static const uint8_t pcf8574_addresses[PCF8574A_NUM_DEVICES] = {
    PCF8574A_PF_ADDR,
    PCF8574A_PG_ADDR,
    PCF8574A_MIXEDSIGNALS_ADDR
};

// Shadow-Register zur Speicherung des aktuellen Ausgangszustands.
static uint8_t shadow_registers[PCF8574A_NUM_DEVICES] = {
    0xFF, // IC1 PORTF
    0xFF, // IC2 PORTG
    0xFF  // IC3 MIXED SIGNALS
};

// Interne Hilfsfunktion: Wartet bis TWI frei ist und schreibt das Shadow-Register
static bool PCF8574A_Sync(pcf8574_id_t id) {
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    return TWI1_Write(pcf8574_addresses[id], &shadow_registers[id], 1);
}

bool PCF8574A_Init(void) {
    bool success = true;
    
    // IC1 und IC2 initialisieren (alle Pins standardmaessig High/Eingang)
    success &= PCF8574A_WriteByte(PCF8574A_PF, 0xFF);
    success &= PCF8574A_WriteByte(PCF8574A_PG, 0xFF);
    
    // IC3 initialisieren: 
    // P0-P3: Steuersignale zu LWB-Bus (P0: PH0 / P1: PH1 / P2: PH2 / P3: PH3)
    // P4-P5: LEDs active low (P4: P2 / P5: P3)
    // P6: RTC_nRST als Ausgang zu DS3234
    // P7: RTC_nINT als Eingang von DS3234
    success &= PCF8574A_WriteByte(PCF8574A_MIXEDSIGNALS, 0xFF);
    
    return success;
}

bool PCF8574A_WriteByte(pcf8574_id_t id, uint8_t value) {
    if (id >= PCF8574A_NUM_DEVICES) return false;
    
    shadow_registers[id] = value;
    return PCF8574A_Sync(id);
}

bool PCF8574A_ReadByte(pcf8574_id_t id, uint8_t *value) {
    if (id >= PCF8574A_NUM_DEVICES || value == NULL) return false;
    
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    return TWI1_Read(pcf8574_addresses[id], value, 1);
}

bool PCF8574A_WritePin(pcf8574_id_t id, uint8_t pin, bool level) {
    if (id >= PCF8574A_NUM_DEVICES || pin > 7) return false;
    
    if (level) {
        shadow_registers[id] |= (1 << pin);
    } else {
        shadow_registers[id] &= ~(1 << pin);
    }
    
    return PCF8574A_Sync(id);
}

bool PCF8574A_ReadPin(pcf8574_id_t id, uint8_t pin, bool *level) {
    if (id >= PCF8574A_NUM_DEVICES || pin > 7 || level == NULL) return false;
    
    uint8_t current_port_state = 0;
    if (!PCF8574A_ReadByte(id, &current_port_state)) {
        return false;
    }
    
    *level = (current_port_state & (1 << pin)) ? true : false;
    return true;
}

// --- Komfortfunktionen fuer IC3 ---
// LED1 (P4): lowaktiv -> Einschalten = 0, Ausschalten = 1
bool PCF8574A_MIXEDSIGNALS_SetLED1(bool turnOn) {
    return PCF8574A_WritePin(PCF8574A_MIXEDSIGNALS, IC3_LED1_PIN, !turnOn);
}

// LED2 (P5): lowaktiv -> Einschalten = 0, Ausschalten = 1
bool PCF8574A_MIXEDSIGNALS_SetLED2(bool turnOn) {
    return PCF8574A_WritePin(PCF8574A_MIXEDSIGNALS, IC3_LED2_PIN, !turnOn);
}

// nRST (P6): lowaktiv -> Active = 0 (Reset wird ausgeloest), Inactive = 1 (Normalbetrieb)
bool PCF8574A_MIXEDSIGNALS_SetDS3234Reset(bool active) {
    return PCF8574A_WritePin(PCF8574A_MIXEDSIGNALS, IC3_DS3234_RST_PIN, !active);
}

// nINT (P7): Eingang -> Liest den Zustand der RTC-Interrupt-Leitung
bool PCF8574A_MIXEDSIGNALS_GetDS3234Interrupt(bool *level) {
    // Da P7 ein Eingang ist, stellen wir sicher, dass er im Shadow-Reg auf 1 steht
    // (wurde beim Init gemacht, schadet aber nicht als Erinnerung im Code)
    return PCF8574A_ReadPin(PCF8574A_MIXEDSIGNALS, IC3_DS3234_INT_PIN, level);
}