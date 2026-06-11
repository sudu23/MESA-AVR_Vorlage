/*
 * PCF8574.c
 * Version: 1.0.0
 *
 *  Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include <stdio.h>
#include "PCF8574.h"


// Hier muessen die MCC TWI1 Funktionen deklariert sein (wird ueblicherweise via "modules/twi1.h" o.ae. eingebunden)
// Da wir den genauen Pfad nicht wissen, stellen wir sicher, dass sie bekannt sind:
extern bool TWI1_Write(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_Read(uint16_t address, uint8_t *data, size_t dataLength);
extern bool TWI1_IsBusy(void);

// Array mit den tatsaechlichen I2C-Adressen
static const uint8_t pcf8574_addresses[PCF8574_NUM_DEVICES] = {
    PCF8574_IC1_ADDR,
    PCF8574_IC2_ADDR,
    PCF8574_IC3_ADDR
};

// Shadow-Register zur Speicherung des aktuellen Ausgangszustands.
// Wichtig: Pins, die als Eingang dienen, MUESSEN im Shadow-Register auf 1 stehen!
static uint8_t shadow_registers[PCF8574_NUM_DEVICES] = {
    0xFF, // IC1: Alles High (sicherer Default/Eingaenge bereit)
    0xFF, // IC2: Alles High
    0xFF  // IC3: P7 (nINT) muss 1 sein, LEDs aus (1), nRST inaktiv (1) -> 0xFF passt perfekt als Startwert
};

// Interne Hilfsfunktion: Wartet bis TWI frei ist und schreibt das Shadow-Register
static bool PCF8574_Sync(pcf8574_id_t id) {
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    return TWI1_Write(pcf8574_addresses[id], &shadow_registers[id], 1);
}

bool PCF8574_Init(void) {
    bool success = true;
    
    // IC1 und IC2 initialisieren (alle Pins standardmaessig High/Eingang)
    success &= PCF8574_WriteByte(PCF8574_IC1, 0xFF);
    success &= PCF8574_WriteByte(PCF8574_IC2, 0xFF);
    
    // IC3 initialisieren: 
    // P0-P3: Frei (High/Eingang)
    // P4-P5: LEDs aus (High bei lowaktiv)
    // P6: nRST inaktiv (High)
    // P7: nINT als Eingang von DS3234 (Muss zwingend High geschrieben werden!)
    success &= PCF8574_WriteByte(PCF8574_IC3, 0xFF);
    
    return success;
}

bool PCF8574_WriteByte(pcf8574_id_t id, uint8_t value) {
    if (id >= PCF8574_NUM_DEVICES) return false;
    
    shadow_registers[id] = value;
    return PCF8574_Sync(id);
}

bool PCF8574_ReadByte(pcf8574_id_t id, uint8_t *value) {
    if (id >= PCF8574_NUM_DEVICES || value == NULL) return false;
    
    uint8_t timeout = 250;
    while (TWI1_IsBusy()) {
        if (--timeout == 0) return false;
    }
    
    return TWI1_Read(pcf8574_addresses[id], value, 1);
}

bool PCF8574_WritePin(pcf8574_id_t id, uint8_t pin, bool level) {
    if (id >= PCF8574_NUM_DEVICES || pin > 7) return false;
    
    if (level) {
        shadow_registers[id] |= (1 << pin);
    } else {
        shadow_registers[id] &= ~(1 << pin);
    }
    
    return PCF8574_Sync(id);
}

bool PCF8574_ReadPin(pcf8574_id_t id, uint8_t pin, bool *level) {
    if (id >= PCF8574_NUM_DEVICES || pin > 7 || level == NULL) return false;
    
    uint8_t current_port_state = 0;
    if (!PCF8574_ReadByte(id, &current_port_state)) {
        return false;
    }
    
    *level = (current_port_state & (1 << pin)) ? true : false;
    return true;
}

// --- Komfortfunktionen fuer IC3 ---

// LED1 (P4): lowaktiv -> Einschalten = 0, Ausschalten = 1
bool PCF8574_IC3_SetLED1(bool turnOn) {
    return PCF8574_WritePin(PCF8574_IC3, IC3_LED1_PIN, !turnOn);
}

// LED2 (P5): lowaktiv -> Einschalten = 0, Ausschalten = 1
bool PCF8574_IC3_SetLED2(bool turnOn) {
    return PCF8574_WritePin(PCF8574_IC3, IC3_LED2_PIN, !turnOn);
}

// nRST (P6): lowaktiv -> Active = 0 (Reset wird ausgeloest), Inactive = 1 (Normalbetrieb)
bool PCF8574_IC3_SetDS3234Reset(bool active) {
    return PCF8574_WritePin(PCF8574_IC3, IC3_DS3234_RST_PIN, !active);
}

// nINT (P7): Eingang -> Liest den Zustand der RTC-Interrupt-Leitung
bool PCF8574_IC3_GetDS3234Interrupt(bool *level) {
    // Da P7 ein Eingang ist, stellen wir sicher, dass er im Shadow-Reg auf 1 steht
    // (wurde beim Init gemacht, schadet aber nicht als Erinnerung im Code)
    return PCF8574_ReadPin(PCF8574_IC3, IC3_DS3234_INT_PIN, level);
}