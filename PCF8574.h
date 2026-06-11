/* 
 * File:   PCF8574.h
 * Author: bub
 *
 * Created on June 11, 2026, 1:11 PM
 */
#ifndef PCF8574_H
#define PCF8574_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// I2C Basisadresse fuer den PCF8574 (7-Bit Adresse)
// Der PCF8574 hat die Basisadresse 0x20.
#define PCF8574_BASE_ADDR   0x20

// Definition der drei ICs basierend auf deiner korrigierten Adressierung (A2, A1, A0)
#define PCF8574_IC1_ADDR    (PCF8574_BASE_ADDR | 0x00) // A2=0, A1=0, A0=0 -> I2C: 0x20
#define PCF8574_IC2_ADDR    (PCF8574_BASE_ADDR | 0x01) // A2=0, A1=0, A0=1 -> I2C: 0x21
#define PCF8574_IC3_ADDR    (PCF8574_BASE_ADDR | 0x02) // A2=0, A1=1, A0=0 -> I2C: 0x22 (Angepasst!)

// Spezifische Pins fuer IC3 (Spezialfunktionen)
#define IC3_LED1_PIN        4  // P4: lowaktive LED
#define IC3_LED2_PIN        5  // P5: lowaktive LED
#define IC3_DS3234_RST_PIN  6  // P6: nRST (Reset, lowaktiv)
#define IC3_DS3234_INT_PIN  7  // P7: nINT (Eingang von RTC)

// Aufzaehlung der IC-Indizes fuer die internen Funktionen
typedef enum {
    PCF8574_IC1 = 0,
    PCF8574_IC2,
    PCF8574_IC3,
    PCF8574_NUM_DEVICES
} pcf8574_id_t;

// Initialisiert den Treiber und setzt die Startwerte der ICs
bool PCF8574_Init(void);

// Schreibt einen kompletten Byte-Wert auf einen bestimmten PCF8574
bool PCF8574_WriteByte(pcf8574_id_t id, uint8_t value);

// Liest den aktuellen Zustand der Pins (Eingaenge und Ausgaenge)
bool PCF8574_ReadByte(pcf8574_id_t id, uint8_t *value);

// Setzt einen einzelnen Pin auf High oder Low
bool PCF8574_WritePin(pcf8574_id_t id, uint8_t pin, bool level);

// Liest den Zustand eines einzelnen Pins
bool PCF8574_ReadPin(pcf8574_id_t id, uint8_t pin, bool *level);

// --- Komfortfunktionen fuer IC3 Spezialpins ---
bool PCF8574_IC3_SetLED1(bool turnOn);
bool PCF8574_IC3_SetLED2(bool turnOn);
bool PCF8574_IC3_SetDS3234Reset(bool active);
bool PCF8574_IC3_GetDS3234Interrupt(bool *level);

#ifdef	__cplusplus
}
#endif

#endif	/* PCF8574_H */
