/*
 * CycleSync.c
 * Version: 1.2.0
 *
 *  Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include "cyclesync.h"

cyclesyncstruct_t CycleSyncStruct;

/**
 * @brief  Initialisiert die CycleSync-Struktur und den Hardware-Timer TCB3.
 * @note   Diese Funktion setzt alle Zähler zurück, konfiguriert den Timer für
 * einen 1-ms-Intervall (Periodic Interrupt) und aktiviert die globalen Interrupts.
 * @param  tic_ms: Die gewünschte Zykluszeit für das blockierende CycleSync in Millisekunden.
 * @return uint8_t: Gibt 1 nach erfolgreicher Initialisierung zurück.
 */
uint8_t CycleSyncInit(uint16_t tic_ms)
{
	//init CycleSync struct
	CycleSyncStruct.tic = tic_ms;
	CycleSyncStruct.cnt = CycleSyncStruct.tic;
	CycleSyncStruct.timeleft = 0;
	CycleSyncStruct.status = 0;
    CycleSyncStruct.systicks = 0;

	
	//timer TCB3 init
	TCB3.CCMP = 0x7d0; /* Compare or Capture: 0x7d0 */

	// TCB3.CNT = 0x0; /* Count: 0x0 */

	// TCB3.CTRLB = 0 << TCB_ASYNC_bp /* Asynchronous Enable: disabled */
	//		 | 0 << TCB_CCMPEN_bp /* Pin Output Enable: disabled */
	//		 | 0 << TCB_CCMPINIT_bp /* Pin Initial State: disabled */
	//		 | TCB_CNTMODE_INT_gc; /* Periodic Interrupt */

	// TCB3.DBGCTRL = 0 << TCB_DBGRUN_bp; /* Debug Run: disabled */

	// TCB3.EVCTRL = 0 << TCB_CAPTEI_bp /* Event Input Enable: disabled */
	//		 | 0 << TCB_EDGE_bp /* Event Edge: disabled */
	//		 | 0 << TCB_FILTER_bp; /* Input Capture Noise Cancellation Filter: disabled */

	TCB3.INTCTRL = 1 << TCB_CAPT_bp   /* Capture or Timeout: enabled */
	               | 0 << TCB_OVF_bp; /* OverFlow Interrupt: disabled */

	TCB3.CTRLA = TCB_CLKSEL_DIV2_gc     /* CLK_PER/2 */
	             | 0 << TCB_ENABLE_bp   /* Enable: disabled */
	             | 0 << TCB_RUNSTDBY_bp /* Run Standby: disabled */
	             | 0 << TCB_SYNCUPD_bp  /* Synchronize Update: disabled */
	             | 0 << TCB_CASCADE_bp; /* Cascade Two Timer/Counters: disabled */
	
	//enable all interrupts
    ENABLE_INTERRUPTS();
	
	//enable Timer TCB3
	TCB3.CTRLA |= 1 << TCB_ENABLE_bp;
	
	return 1;
}

/**
 * @brief  Interrupt Service Routine (ISR) für den Timer TCB3.
 * @note   Triggert zyklisch alle 1 ms. Sie setzt das Interrupt-Flag zurück,
 * inkrementiert den globalen Taktzähler (sysTicks) für das nicht-blockierende
 * Konzept und dekrementiert den Countdown (cnt) für das blockierende Konzept.
 */
ISR(TCB3_INT_vect)
{
	TCB3.INTFLAGS = TCB_CAPT_bm;
    
    CycleSyncStruct.systicks++;
	
	CycleSyncStruct.cnt--;
}

/**
 * @brief  Sorgt für eine deterministische, blockierende Zeitverzögerung der Hauptschleife.
 * @note   Die Funktion wartet, bis die mit CycleSyncInit definierte Zykluszeit abgelaufen ist.
 * Wurde die Zeit bereits überschritten, wird das Warten übersprungen. In beiden
 * Fällen wird der Timer-Countdown für den nächsten Zyklus neu geladen.
 * @return int16_t: 
 * - 1: Zykluszeit wurde eingehalten (ordnungsgemäss gewartet).
 * - 0: Zykluszeit wurde überschritten (Zeitüberschreitung im Hauptcode).
 */
int16_t CycleSync(void)
{		
	//store unnecessary time value (for debugging)
	CycleSyncStruct.timeleft = CycleSyncStruct.cnt;	
	
	//is cycle time exceeded?
	if(CycleSyncStruct.cnt < 0)
	{
		//skip waiting
		
		//load tic for a new cycle	
		CycleSyncStruct.cnt = CycleSyncStruct.tic;
		
		//return
		CycleSyncStruct.status = 0;
		return 0;
	}
	
	//wait for the remaining time
	while(CycleSyncStruct.cnt > 0)
	{;}
	
	//load tic for a new cycle	
	CycleSyncStruct.cnt = CycleSyncStruct.tic;
	
	//return
	CycleSyncStruct.status = 1;
	return 1;
}

/**
 * @brief  Gibt den Wert von timeleft (verbleibende Zykluszeit) sicher zurück.
 * @note   Sichert den Zugriff auf die 16-Bit-Variable gegen Interrupts ab (Atomarität).
 * Nützlich, um im Hauptprogramm (z.B. via Display oder Seriell) zu prüfen,
 * wie viel "Reserve" der blockierende Zyklus noch hatte.
 * @return int16_t: Die Anzahl der verbleibenden Millisekunden des letzten Zyklus.
 */
int16_t GetTimeLeft(void)
{
    int16_t currentTimeLeft;
    uint8_t sregBackup;
    
    // Statusregister sichern und Interrupts global deaktivieren
    sregBackup = SREG;
    cli();
    
    // 16-Bit-Wert sicher auslesen (2 Bytes am Stück, ohne ISR-Unterbrechung)
    currentTimeLeft = CycleSyncStruct.timeleft;
    
    // Alten Interrupt-Status wiederherstellen
    SREG = sregBackup;
    
    return currentTimeLeft;
}

/**
 * @brief Gibt die aktuellen System-Ticks (seit Start) sicher zurück.
 * @note Sichert den Zugriff auf die 32-Bit Variable gegen Interrupts ab (Atomarität).
 */
uint32_t GetSysTicks(void)
{
    uint32_t currentTicks;
    uint8_t sregBackup;
    
    // Statusregister sichern und Interrupts global deaktivieren
    sregBackup = SREG;
    cli();
    
    // 32-Bit-Wert sicher in Registern zusammenbauen (wird nicht von ISR unterbrochen)
    currentTicks = CycleSyncStruct.systicks;
    
    // Alten Interrupt-Status (aktiv oder inaktiv) wiederherstellen
    SREG = sregBackup;
    
    return currentTicks;
}
