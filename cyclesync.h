/*
 * cyclesync.h
 * Version: 1.2.0
 *
 *  Author: bub
 */

//CYCLESYNC_H
#ifndef CYCLESYNC_H
#define CYCLESYNC_H

typedef struct {
	volatile int16_t cnt;
	int16_t tic;
	uint8_t status;
	int16_t timeleft;
    volatile uint32_t systicks;
} cyclesyncstruct_t;

uint8_t CycleSyncInit(uint16_t);
int16_t CycleSync(void);

int16_t GetTimeLeft(void);

uint32_t GetSysTicks(void);

#endif //CYCLESYNC_H