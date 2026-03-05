/*
 * cyclesync.h
 * Version: 1.1.1
 *
 * Created: 16.02.2024 14:57:25
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
} cyclesyncstruct_t;

uint8_t CycleSyncInit(uint16_t);
int16_t CycleSync(void);

#endif //CYCLESYNC_H