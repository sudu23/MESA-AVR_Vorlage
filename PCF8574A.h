/* 
 * File:   PCF8574A.h
 * Author: bub
 *
 * Created on June 11, 2026, 1:11 PM
 */
#ifndef PCF8574A_H
#define PCF8574A_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// I2C Basisadresse fuer den PCF8574A (7-Bit Adresse)
// Der PCF8574A hat die Basisadresse 0x38.
#define PCF8574A_BASE_ADDR   0x38

// Definition der drei ICs
#define PCF8574A_PF_ADDR    (PCF8574A_BASE_ADDR | 0x00) // A2=0, A1=0, A0=0 -> I2C: 0x20
#define PCF8574A_PG_ADDR    (PCF8574A_BASE_ADDR | 0x01) // A2=0, A1=0, A0=1 -> I2C: 0x21
#define PCF8574A_MIXEDSIGNALS_ADDR    (PCF8574A_BASE_ADDR | 0x02) // A2=0, A1=1, A0=0 -> I2C: 0x22

// Spezifische Pins fuer IC3 (Spezialfunktionen)
#define IC3_LED1_PIN        4  // P4: lowaktive LED
#define IC3_LED2_PIN        5  // P5: lowaktive LED
#define IC3_DS3234_RST_PIN  6  // P6: RTC nRST (Output, Reset, active low)
#define IC3_DS3234_INT_PIN  7  // P7: RTC nINT (Input, Interrupt, active low)

// Aufzaehlung der IC-Indizes fuer die internen Funktionen
typedef enum {
    PCF8574A_PF = 0,
    PCF8574A_PG,
    PCF8574A_MIXEDSIGNALS,
    PCF8574A_NUM_DEVICES
} pcf8574_id_t;

// Initialisiert den Treiber und setzt die Startwerte der ICs
bool PCF8574A_Init(void);

// Schreibt einen kompletten Byte-Wert auf einen bestimmten PCF8574A
bool PCF8574A_WriteByte(pcf8574_id_t id, uint8_t value);

// Liest den aktuellen Zustand der Pins (Eingaenge und Ausgaenge)
bool PCF8574A_ReadByte(pcf8574_id_t id, uint8_t *value);

// Setzt einen einzelnen Pin auf High oder Low
bool PCF8574A_WritePin(pcf8574_id_t id, uint8_t pin, bool level);

// Liest den Zustand eines einzelnen Pins
bool PCF8574A_ReadPin(pcf8574_id_t id, uint8_t pin, bool *level);

// --- Komfortfunktionen fuer IC3 Spezialpins ---
bool PCF8574A_MIXEDSIGNALS_SetLED1(bool turnOn);
bool PCF8574A_MIXEDSIGNALS_SetLED2(bool turnOn);
bool PCF8574A_MIXEDSIGNALS_SetDS3234Reset(bool active);
bool PCF8574A_MIXEDSIGNALS_GetDS3234Interrupt(bool *level);

#ifdef	__cplusplus
}
#endif

#endif	/* PCF8574A_H */
