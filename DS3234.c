/*
 * DS3234.c
 * Version: 1.0.0
 *
 * Author: bub
 */

#include <util/delay.h>
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
#define REG_SRAM_ADDR    0x18
#define REG_SRAM_DATA    0x19

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

// Niedrigwertige SPI-Hilfsfunktionen mit korrigiertem ISR-Warte-Timing
static uint8_t DS3234_ReadRegister(uint8_t reg) {
    uint8_t data = 0;
    
    DS3234_CS_SELECT();
    _delay_us(2); // Dem CS-Pin Zeit zum Einschwingen geben
    
    SPI1_ByteExchange(reg & 0x7F);  // Bit 7 auf 0 fuer Lesen
    DS3234_WaitForSPI();            // Zwingend auf Ende der ISR warten!
    
    data = SPI1_ByteExchange(0x00); // Dummy senden, um Daten zu lesen
    DS3234_WaitForSPI();            // Zwingend auf Ende der ISR warten!
    
    _delay_us(2);
    DS3234_CS_DESELECT();

    return data;
}

static void DS3234_WriteRegister(uint8_t reg, uint8_t val) {
    DS3234_CS_SELECT();
    _delay_us(2);
    
    SPI1_ByteExchange(reg | 0x80);  // Bit 7 auf 1 fuer Schreiben
    DS3234_WaitForSPI();            // Zwingend warten!
    
    SPI1_ByteExchange(val);
    DS3234_WaitForSPI();            // Zwingend warten!
    
    _delay_us(2);
    DS3234_CS_DESELECT();
}

bool DS3234_Init(void) {
    // 1. PORTC gezielt fuer SPI1-Betrieb umschreiben (Einkommentiert und erweitert!)
    PORTC.DIRSET = PIN0_bm | PIN2_bm | PIN3_bm; // PC0 (MOSI), PC2 (SCK), PC3 (CS) -> Ausgang
    PORTC.DIRCLR = PIN1_bm;                     // PC1 (MISO) -> Eingang
    
    DS3234_CS_INIT();
    DS3234_CS_DESELECT(); // Direkt in den inaktiven Zustand (High) versetzen
    
    // SPI-Konfiguration laden
    if(!SPI1_Open(HOST_CONFIG)){
        return false;
    }
    
    _delay_ms(5); // Kurze Stabilisierungszeit nach dem Bus-Schnittstellen-Einschalten
    
    // 2. Control Register auslesen und einstellen
    uint8_t control_reg = DS3234_ReadRegister(REG_CONTROL);
    control_reg &= ~(1 << 7); // EOSC bit loeschen = Oszillator an im Batteriebetrieb
    control_reg |= (1 << 2);  // INTCN bit setzen = nINT Pin feuert Alarme
    control_reg |= (1 << 5);  // CONV bit setzen = Convert Temperatur
    DS3234_WriteRegister(REG_CONTROL, control_reg);
    
    // Kontrolllesung zur Absicherung
    if(control_reg != DS3234_ReadRegister(REG_CONTROL)){
        return false;
    }
    
    // Status Register (0x0F) pruefen / OSF (Oscillator Stop Flag) loeschen
    uint8_t status_reg = DS3234_ReadRegister(REG_STATUS);
    if (status_reg & (1 << 7)) {
        // Oszillator stand still (z.B. nach Power-loss), Flag loeschen
        DS3234_WriteRegister(REG_STATUS, status_reg & ~(1 << 7));
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
     
    DS3234_CS_SELECT();
    _delay_us(2);
    
    SPI1_BufferWrite(write_buffer, sizeof(write_buffer));
    DS3234_WaitForSPI();
    
    _delay_us(2);
    DS3234_CS_DESELECT();
    return true;
}

bool DS3234_GetTime(ds3234_time_t *time) {
    if (time == NULL) return false;
    
    uint8_t tx_buffer[8] = { REG_SECONDS & 0x7F, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t rx_buffer[8] = { 0 };
    
    DS3234_CS_SELECT();
    _delay_us(2);
    
    SPI1_Transfer(tx_buffer, rx_buffer, sizeof(tx_buffer));
    DS3234_WaitForSPI();
    
    _delay_us(2);
    DS3234_CS_DESELECT();

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
     
    DS3234_CS_SELECT();
    _delay_us(2);
    
    SPI1_Transfer(tx_buffer, rx_buffer, sizeof(tx_buffer));
    DS3234_WaitForSPI();
    
    _delay_us(2);
    DS3234_CS_DESELECT();
    
    int8_t msb = (int8_t)rx_buffer[1];
    uint8_t lsb = rx_buffer[2];
    
    float fraction = (float)(lsb >> 6) * 0.25f;
    
    // Korrektes Vorzeichenhandling fuer negative Temperaturen
    if (msb < 0) {
        *temperature = (float)msb - fraction;
    } else {
        *temperature = (float)msb + fraction;
    }
    
    return true;
}