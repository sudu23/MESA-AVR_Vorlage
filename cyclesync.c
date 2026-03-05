/*
 * CycleSync.c
 * Version: 1.1.1
 *
 * Created: 16.02.2024 14:20
 *  Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include "cyclesync.h"

cyclesyncstruct_t CycleSyncStruct;

uint8_t CycleSyncInit(uint16_t tic_ms)
{
	//init CycleSync struct
	CycleSyncStruct.tic = tic_ms;
	CycleSyncStruct.cnt = CycleSyncStruct.tic;
	CycleSyncStruct.timeleft = 0;
	CycleSyncStruct.status = 0;

	
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

ISR(TCB3_INT_vect)
{
	TCB3.INTFLAGS = TCB_CAPT_bm;
	
	CycleSyncStruct.cnt--;
}

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
