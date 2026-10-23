/* 
 * File:   MCP23008.h
 * Author: bub
 */

#ifndef MCP23008_H
#define MCP23008_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// I2C Basisadresse fuer den MCP23008 (7-Bit Adresse)
#define MCP23008_BASE_ADDR    0x20

// Definition der drei ICs
#define MCP23008_PF_ADDR           (MCP23008_BASE_ADDR | 0x00) // 0x20
#define MCP23008_PG_ADDR           (MCP23008_BASE_ADDR | 0x01) // 0x21
#define MCP23008_MIXEDSIGNALS_ADDR (MCP23008_BASE_ADDR | 0x02) // 0x22

// Spezifische Pins fuer IC3 (Spezialfunktionen)
#define IC3_LED1_PIN        4  // PH4: lowaktive LED
#define IC3_LED2_PIN        5  // PH5: lowaktive LED
#define IC3_DS3234_RST_PIN  6  // PH6: RTC nRST (Output, Reset, active low)
#define IC3_DS3234_INT_PIN  7  // PH7: RTC nINT (Input, Interrupt, active low)

// Aufzaehlung der IC-Indizes fuer die internen Funktionen
typedef enum {
    MCP23008_PF = 0,
    MCP23008_PG,
    MCP23008_MIXEDSIGNALS,
    MCP23008_NUM_DEVICES
} mcp23008_id_t;

// Initialisiert den Treiber und setzt die Startwerte der ICs
bool MCP23008_Init(void);

// Schreibt einen kompletten Byte-Wert auf einen bestimmten MCP23008
bool MCP23008_WriteByte(mcp23008_id_t id, uint8_t value);

// Liest den aktuellen Zustand der Pins
bool MCP23008_ReadByte(mcp23008_id_t id, uint8_t *value);

// Setzt einen einzelnen Pin auf High oder Low
bool MCP23008_WritePin(mcp23008_id_t id, uint8_t pin, bool level);

// Liest den Zustand eines einzelnen Pins
bool MCP23008_ReadPin(mcp23008_id_t id, uint8_t pin, bool *level);

// --- Komfortfunktionen fuer IC3 Spezialpins ---
bool MCP23008_MIXEDSIGNALS_SetLED1(bool turnOn);
bool MCP23008_MIXEDSIGNALS_SetLED2(bool turnOn);
bool MCP23008_MIXEDSIGNALS_SetDS3234Reset(bool active);
bool MCP23008_MIXEDSIGNALS_GetDS3234Interrupt(bool *level);

#ifdef __cplusplus
}
#endif

#endif /* MCP23008_H */