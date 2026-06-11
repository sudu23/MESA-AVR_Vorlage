/*
 * DS3234.c
 * Version: 1.0.0
 *
 * Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include "DS3234.h"

// --- HARDWARE ANPASSUNG: Chip Select (CS) auf PC3 ---
#define DS3234_CS_INIT()     PORTC.DIRSET = PIN3_bm
#define DS3234_CS_SELECT()   PORTC.OUTCLR = PIN3_bm
#define DS3234_CS_DESELECT() PORTC.OUTSET = PIN3_bm

// Register-Adressen (Lesen). Fuer Schreiben wird Bit 7 gesetzt (Address | 0x80)
#define REG_SECONDS      0x00
#define REG_MINUTES      0x01
#define REG_HOURS        0x02
#define REG_DAY_OF_WEEK  0x03
#define REG_DATE         0x04
#define REG_MONTH        0x05
#define REG_YEAR         0x06
#define REG_CONTROL      0x0E
#define REG_STATUS       0x0F
#define REG_TEMP_MSB     0x11
#define REG_TEMP_LSB     0x12

// Hilfsfunktionen zur BCD-Konvertierung
static uint8_t bin2bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

static uint8_t bcd2bin(uint8_t val) {
    return ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
}

// Hilfsfunktion: Wartet, bis die MCC-Interrupt-Uebertragung vollstaendig abgeschlossen ist
static void DS3234_WaitForSPI(void) {
    while (!SPI1_IsTxReady()) {
        ; // Blockiert, solange die ISR noch mit dem Buffer beschaeftigt ist
    }
}

// Niedrigwertige SPI-Hilfsfunktionen unter Verwendung deiner API
static uint8_t DS3234_ReadRegister(uint8_t reg) {
    uint8_t data = 0;
    
    if (SPI1_Open(SPI1_DEFAULT)) {
        DS3234_CS_SELECT();
        SPI1_ByteExchange(reg & 0x7F);  // Bit 7 auf 0 fuer Lesen
        data = SPI1_ByteExchange(0x00); // Dummy senden, um Daten zu lesen
        DS3234_CS_DESELECT();
        SPI1_Close();
    }
    return data;
}

static void DS3234_WriteRegister(uint8_t reg, uint8_t val) {
    if (SPI1_Open(SPI1_DEFAULT)) {
        DS3234_CS_SELECT();
        SPI1_ByteExchange(reg | 0x80);  // Bit 7 auf 1 fuer Schreiben
        SPI1_ByteExchange(val);
        DS3234_CS_DESELECT();
        SPI1_Close();
    }
}

bool DS3234_Init(void) {
    // 1. PORTC gezielt fuer SPI1-Betrieb umschreiben
    // PC0 (MOSI) -> Ausgang
    // PC1 (MISO) -> Eingang
    // PC2 (SCK)  -> Ausgang
    // PC3 (CS)   -> Ausgang (und direkt auf HIGH legen)
    PORTC.DIRSET = PIN0_bm | PIN2_bm | PIN3_bm;
    PORTC.DIRCLR = PIN1_bm;
    
    // Default-Zustand (High = Deselect) fuer PC3 einrichten
    DS3234_CS_DESELECT();
    
    // 2. Den MCC SPI Treiber initialisieren
    SPI1_Initialize();
    
    // 3. Control Register auslesen und einstellen
    // Sicherstellen, dass der Oszillator laeuft (EOSC = 0) und
    // den nINT/SQW Pin auf Interrupt-Betrieb stellen (INTCN = 1)
    uint8_t control = DS3234_ReadRegister(REG_CONTROL);
    control &= ~(1 << 7); // EOSC bit loeschen = Oszillator an im Batteriebetrieb
    control |= (1 << 2);  // INTCN bit setzen = nINT Pin feuert Alarme
    DS3234_WriteRegister(REG_CONTROL, control);
    
    // Status Register (0x0F) pruefen / OSF (Oscillator Stop Flag) loeschen
    uint8_t status = DS3234_ReadRegister(REG_STATUS);
    if (status & (1 << 7)) {
        // Oszillator stand still (z.B. nach Power-loss), Flag loeschen
        DS3234_WriteRegister(REG_STATUS, status & ~(1 << 7));
    }
    
    return true;
}

bool DS3234_SetTime(const ds3234_time_t *time) {
    if (time == NULL) return false;
    
    uint8_t write_buffer[8];
    write_buffer[0] = REG_SECONDS | 0x80; // Startadresse mit Schreib-Bit
    write_buffer[1] = bin2bcd(time->second);
    write_buffer[2] = bin2bcd(time->minute);
    write_buffer[3] = bin2bcd(time->hour) & 0x3F; // 24h-Modus erzwungen
    write_buffer[4] = bin2bcd(time->day_of_week);
    write_buffer[5] = bin2bcd(time->day);
    write_buffer[6] = bin2bcd(time->month);
    write_buffer[7] = bin2bcd((uint8_t)(time->year % 100));
    
    if (!SPI1_Open(SPI1_DEFAULT)) return false;
    
    DS3234_CS_SELECT();
    // Nutzt die BufferWrite-Funktion deiner API fuer einen schnellen Burst
    SPI1_BufferWrite(write_buffer, sizeof(write_buffer));
    
    // Warten, bis die ISR alle Bytes vollstaendig gesendet hat
    DS3234_WaitForSPI();
    
    DS3234_CS_DESELECT();
    SPI1_Close();
    return true;
}

bool DS3234_GetTime(ds3234_time_t *time) {
    if (time == NULL) return false;
    
    uint8_t tx_buffer[8] = { REG_SECONDS & 0x7F, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t rx_buffer[8] = { 0 };
    
    if (!SPI1_Open(SPI1_DEFAULT)) return false;
    
    DS3234_CS_SELECT();
    // SPI1_Transfer sendet die Startadresse und liest parallel die 7 Bytes der Uhrzeit ein
    SPI1_Transfer(tx_buffer, rx_buffer, sizeof(tx_buffer));
    
    // Warten, bis die ISR den gesamten Buffer gefuellt hat
    DS3234_WaitForSPI();
    
    DS3234_CS_DESELECT();
    SPI1_Close();
    
    // rx_buffer[0] enthaelt nur Muell von der Adressphase, Daten starten ab Index 1
    time->second      = bcd2bin(rx_buffer[1]);
    time->minute      = bcd2bin(rx_buffer[2]);
    time->hour        = bcd2bin(rx_buffer[3] & 0x3F);
    time->day_of_week = bcd2bin(rx_buffer[4]);
    time->day         = bcd2bin(rx_buffer[5]);
    time->month       = bcd2bin(rx_buffer[6] & 0x1F);
    time->year        = bcd2bin(rx_buffer[7]) + 2000;
    
    return true;
}

bool DS3234_GetTemperature(float *temperature) {
    if (temperature == NULL) return false;
    
    uint8_t tx_buffer[3] = { REG_TEMP_MSB & 0x7F, 0, 0 };
    uint8_t rx_buffer[3] = { 0 };
    
    if (!SPI1_Open(SPI1_DEFAULT)) return false;
    
    DS3234_CS_SELECT();
    SPI1_Transfer(tx_buffer, rx_buffer, sizeof(tx_buffer));
    
    // Warten auf das Ende der ISR-Uebertragung
    DS3234_WaitForSPI();
    
    DS3234_CS_DESELECT();
    SPI1_Close();
    
    // rx_buffer[0] = Dummy waehrend Adressphase
    int8_t msb = (int8_t)rx_buffer[1];
    uint8_t lsb = rx_buffer[2];
    
    float fraction = (float)(lsb >> 6) * 0.25f;
    
    if (msb < 0) {
        *temperature = (float)msb - fraction;
    } else {
        *temperature = (float)msb + fraction;
    }
    
    return true;
}
