/* * File:   DS3234.h
 * Author: bub
 *
 * Created on June 11, 2026, 13:20
 */

#ifndef DS3234_H
#define DS3234_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Struktur fuer Zeit und Datum
typedef struct {
    uint8_t second;     // 0-59
    uint8_t minute;     // 0-59
    uint8_t hour;       // 0-23 (24h-Modus vorausgesetzt)
    uint8_t day_of_week;// 1-7 (z.B. 1 = Montag)
    uint8_t day;        // 1-31
    uint8_t month;      // 1-12
    uint16_t year;      // Vollstaendig, z.B. 2026
} ds3234_time_t;

// Initialisiert die RTC (stellt z.B. den Oszillator sicher)
bool DS3234_Init(void);

// Setzt die Uhrzeit und das Datum in der RTC
bool DS3234_SetTime(const ds3234_time_t *time);

// Liest die aktuelle Uhrzeit und das Datum aus der RTC
bool DS3234_GetTime(ds3234_time_t *time);

// Liest die interne Temperatur des TCXO (in Grad Celsius)
bool DS3234_GetTemperature(float *temperature);

#ifdef __cplusplus
}
#endif

#endif /* DS3234_H */