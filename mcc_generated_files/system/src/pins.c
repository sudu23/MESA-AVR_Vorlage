/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*IO_PF1_InterruptHandler)(void);
static void (*IO_PF0_InterruptHandler)(void);
static void (*IO_PA0_InterruptHandler)(void);
static void (*IO_PA1_InterruptHandler)(void);
static void (*IO_PA2_InterruptHandler)(void);
static void (*IO_PA3_InterruptHandler)(void);
static void (*IO_PA4_InterruptHandler)(void);
static void (*IO_PA5_InterruptHandler)(void);
static void (*IO_PA6_InterruptHandler)(void);
static void (*IO_PA7_InterruptHandler)(void);
static void (*IO_PB0_InterruptHandler)(void);
static void (*IO_PB1_InterruptHandler)(void);
static void (*IO_PB2_InterruptHandler)(void);
static void (*IO_PB3_InterruptHandler)(void);
static void (*IO_PE0_InterruptHandler)(void);
static void (*IO_PE1_InterruptHandler)(void);
static void (*IO_PE2_InterruptHandler)(void);
static void (*IO_PE3_InterruptHandler)(void);
static void (*HBLED_InterruptHandler)(void);
static void (*RGBLED_B_InterruptHandler)(void);
static void (*IO_PC0_InterruptHandler)(void);
static void (*IO_PC1_InterruptHandler)(void);
static void (*IO_PC2_InterruptHandler)(void);
static void (*IO_PC3_InterruptHandler)(void);
static void (*IO_PC4_InterruptHandler)(void);
static void (*IO_PC5_InterruptHandler)(void);
static void (*IO_PC6_InterruptHandler)(void);
static void (*IO_PC7_InterruptHandler)(void);
static void (*IO_PD0_InterruptHandler)(void);
static void (*IO_PD1_InterruptHandler)(void);
static void (*IO_PD2_InterruptHandler)(void);
static void (*IO_PD3_InterruptHandler)(void);
static void (*IO_PD4_InterruptHandler)(void);
static void (*IO_PD5_InterruptHandler)(void);
static void (*IO_PD6_InterruptHandler)(void);
static void (*IO_PD7_InterruptHandler)(void);
static void (*RGBLED_R_InterruptHandler)(void);
static void (*RGBLED_G_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTB.OUT = 0x20;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTE.OUT = 0x0;
    PORTF.OUT = 0x31;

  /* DIR Registers Initialization */
    PORTA.DIR = 0x0;
    PORTB.DIR = 0x30;
    PORTC.DIR = 0xFF;
    PORTD.DIR = 0xFF;
    PORTE.DIR = 0x0;
    PORTF.DIR = 0x31;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x8;
    PORTA.PIN1CTRL = 0x8;
    PORTA.PIN2CTRL = 0x8;
    PORTA.PIN3CTRL = 0x8;
    PORTA.PIN4CTRL = 0x8;
    PORTA.PIN5CTRL = 0x8;
    PORTA.PIN6CTRL = 0x8;
    PORTA.PIN7CTRL = 0x8;
    PORTB.PIN0CTRL = 0x0;
    PORTB.PIN1CTRL = 0x0;
    PORTB.PIN2CTRL = 0x0;
    PORTB.PIN3CTRL = 0x0;
    PORTB.PIN4CTRL = 0x0;
    PORTB.PIN5CTRL = 0x0;
    PORTB.PIN6CTRL = 0x0;
    PORTB.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTE.PIN0CTRL = 0x0;
    PORTE.PIN1CTRL = 0x0;
    PORTE.PIN2CTRL = 0x0;
    PORTE.PIN3CTRL = 0x0;
    PORTE.PIN4CTRL = 0x0;
    PORTE.PIN5CTRL = 0x0;
    PORTE.PIN6CTRL = 0x0;
    PORTE.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.ACROUTEA = 0x0;
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCDROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;
    PORTMUX.USARTROUTEB = 0x0;
    PORTMUX.ZCDROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PF1_SetInterruptHandler(IO_PF1_DefaultInterruptHandler);
    IO_PF0_SetInterruptHandler(IO_PF0_DefaultInterruptHandler);
    IO_PA0_SetInterruptHandler(IO_PA0_DefaultInterruptHandler);
    IO_PA1_SetInterruptHandler(IO_PA1_DefaultInterruptHandler);
    IO_PA2_SetInterruptHandler(IO_PA2_DefaultInterruptHandler);
    IO_PA3_SetInterruptHandler(IO_PA3_DefaultInterruptHandler);
    IO_PA4_SetInterruptHandler(IO_PA4_DefaultInterruptHandler);
    IO_PA5_SetInterruptHandler(IO_PA5_DefaultInterruptHandler);
    IO_PA6_SetInterruptHandler(IO_PA6_DefaultInterruptHandler);
    IO_PA7_SetInterruptHandler(IO_PA7_DefaultInterruptHandler);
    IO_PB0_SetInterruptHandler(IO_PB0_DefaultInterruptHandler);
    IO_PB1_SetInterruptHandler(IO_PB1_DefaultInterruptHandler);
    IO_PB2_SetInterruptHandler(IO_PB2_DefaultInterruptHandler);
    IO_PB3_SetInterruptHandler(IO_PB3_DefaultInterruptHandler);
    IO_PE0_SetInterruptHandler(IO_PE0_DefaultInterruptHandler);
    IO_PE1_SetInterruptHandler(IO_PE1_DefaultInterruptHandler);
    IO_PE2_SetInterruptHandler(IO_PE2_DefaultInterruptHandler);
    IO_PE3_SetInterruptHandler(IO_PE3_DefaultInterruptHandler);
    HBLED_SetInterruptHandler(HBLED_DefaultInterruptHandler);
    RGBLED_B_SetInterruptHandler(RGBLED_B_DefaultInterruptHandler);
    IO_PC0_SetInterruptHandler(IO_PC0_DefaultInterruptHandler);
    IO_PC1_SetInterruptHandler(IO_PC1_DefaultInterruptHandler);
    IO_PC2_SetInterruptHandler(IO_PC2_DefaultInterruptHandler);
    IO_PC3_SetInterruptHandler(IO_PC3_DefaultInterruptHandler);
    IO_PC4_SetInterruptHandler(IO_PC4_DefaultInterruptHandler);
    IO_PC5_SetInterruptHandler(IO_PC5_DefaultInterruptHandler);
    IO_PC6_SetInterruptHandler(IO_PC6_DefaultInterruptHandler);
    IO_PC7_SetInterruptHandler(IO_PC7_DefaultInterruptHandler);
    IO_PD0_SetInterruptHandler(IO_PD0_DefaultInterruptHandler);
    IO_PD1_SetInterruptHandler(IO_PD1_DefaultInterruptHandler);
    IO_PD2_SetInterruptHandler(IO_PD2_DefaultInterruptHandler);
    IO_PD3_SetInterruptHandler(IO_PD3_DefaultInterruptHandler);
    IO_PD4_SetInterruptHandler(IO_PD4_DefaultInterruptHandler);
    IO_PD5_SetInterruptHandler(IO_PD5_DefaultInterruptHandler);
    IO_PD6_SetInterruptHandler(IO_PD6_DefaultInterruptHandler);
    IO_PD7_SetInterruptHandler(IO_PD7_DefaultInterruptHandler);
    RGBLED_R_SetInterruptHandler(RGBLED_R_DefaultInterruptHandler);
    RGBLED_G_SetInterruptHandler(RGBLED_G_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PF1 at application runtime
*/
void IO_PF1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF1_InterruptHandler = interruptHandler;
}

void IO_PF1_DefaultInterruptHandler(void)
{
    // add your IO_PF1 interrupt custom code
    // or set custom function using IO_PF1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF0 at application runtime
*/
void IO_PF0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF0_InterruptHandler = interruptHandler;
}

void IO_PF0_DefaultInterruptHandler(void)
{
    // add your IO_PF0 interrupt custom code
    // or set custom function using IO_PF0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA0 at application runtime
*/
void IO_PA0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA0_InterruptHandler = interruptHandler;
}

void IO_PA0_DefaultInterruptHandler(void)
{
    // add your IO_PA0 interrupt custom code
    // or set custom function using IO_PA0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA1 at application runtime
*/
void IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA1_InterruptHandler = interruptHandler;
}

void IO_PA1_DefaultInterruptHandler(void)
{
    // add your IO_PA1 interrupt custom code
    // or set custom function using IO_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA2 at application runtime
*/
void IO_PA2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA2_InterruptHandler = interruptHandler;
}

void IO_PA2_DefaultInterruptHandler(void)
{
    // add your IO_PA2 interrupt custom code
    // or set custom function using IO_PA2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA3 at application runtime
*/
void IO_PA3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA3_InterruptHandler = interruptHandler;
}

void IO_PA3_DefaultInterruptHandler(void)
{
    // add your IO_PA3 interrupt custom code
    // or set custom function using IO_PA3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA4 at application runtime
*/
void IO_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA4_InterruptHandler = interruptHandler;
}

void IO_PA4_DefaultInterruptHandler(void)
{
    // add your IO_PA4 interrupt custom code
    // or set custom function using IO_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA5 at application runtime
*/
void IO_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA5_InterruptHandler = interruptHandler;
}

void IO_PA5_DefaultInterruptHandler(void)
{
    // add your IO_PA5 interrupt custom code
    // or set custom function using IO_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA6 at application runtime
*/
void IO_PA6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA6_InterruptHandler = interruptHandler;
}

void IO_PA6_DefaultInterruptHandler(void)
{
    // add your IO_PA6 interrupt custom code
    // or set custom function using IO_PA6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA7 at application runtime
*/
void IO_PA7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA7_InterruptHandler = interruptHandler;
}

void IO_PA7_DefaultInterruptHandler(void)
{
    // add your IO_PA7 interrupt custom code
    // or set custom function using IO_PA7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PB0 at application runtime
*/
void IO_PB0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PB0_InterruptHandler = interruptHandler;
}

void IO_PB0_DefaultInterruptHandler(void)
{
    // add your IO_PB0 interrupt custom code
    // or set custom function using IO_PB0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PB1 at application runtime
*/
void IO_PB1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PB1_InterruptHandler = interruptHandler;
}

void IO_PB1_DefaultInterruptHandler(void)
{
    // add your IO_PB1 interrupt custom code
    // or set custom function using IO_PB1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PB2 at application runtime
*/
void IO_PB2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PB2_InterruptHandler = interruptHandler;
}

void IO_PB2_DefaultInterruptHandler(void)
{
    // add your IO_PB2 interrupt custom code
    // or set custom function using IO_PB2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PB3 at application runtime
*/
void IO_PB3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PB3_InterruptHandler = interruptHandler;
}

void IO_PB3_DefaultInterruptHandler(void)
{
    // add your IO_PB3 interrupt custom code
    // or set custom function using IO_PB3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PE0 at application runtime
*/
void IO_PE0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PE0_InterruptHandler = interruptHandler;
}

void IO_PE0_DefaultInterruptHandler(void)
{
    // add your IO_PE0 interrupt custom code
    // or set custom function using IO_PE0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PE1 at application runtime
*/
void IO_PE1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PE1_InterruptHandler = interruptHandler;
}

void IO_PE1_DefaultInterruptHandler(void)
{
    // add your IO_PE1 interrupt custom code
    // or set custom function using IO_PE1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PE2 at application runtime
*/
void IO_PE2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PE2_InterruptHandler = interruptHandler;
}

void IO_PE2_DefaultInterruptHandler(void)
{
    // add your IO_PE2 interrupt custom code
    // or set custom function using IO_PE2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PE3 at application runtime
*/
void IO_PE3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PE3_InterruptHandler = interruptHandler;
}

void IO_PE3_DefaultInterruptHandler(void)
{
    // add your IO_PE3 interrupt custom code
    // or set custom function using IO_PE3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for HBLED at application runtime
*/
void HBLED_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    HBLED_InterruptHandler = interruptHandler;
}

void HBLED_DefaultInterruptHandler(void)
{
    // add your HBLED interrupt custom code
    // or set custom function using HBLED_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RGBLED_B at application runtime
*/
void RGBLED_B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RGBLED_B_InterruptHandler = interruptHandler;
}

void RGBLED_B_DefaultInterruptHandler(void)
{
    // add your RGBLED_B interrupt custom code
    // or set custom function using RGBLED_B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC0 at application runtime
*/
void IO_PC0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC0_InterruptHandler = interruptHandler;
}

void IO_PC0_DefaultInterruptHandler(void)
{
    // add your IO_PC0 interrupt custom code
    // or set custom function using IO_PC0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC1 at application runtime
*/
void IO_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC1_InterruptHandler = interruptHandler;
}

void IO_PC1_DefaultInterruptHandler(void)
{
    // add your IO_PC1 interrupt custom code
    // or set custom function using IO_PC1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC2 at application runtime
*/
void IO_PC2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC2_InterruptHandler = interruptHandler;
}

void IO_PC2_DefaultInterruptHandler(void)
{
    // add your IO_PC2 interrupt custom code
    // or set custom function using IO_PC2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC3 at application runtime
*/
void IO_PC3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC3_InterruptHandler = interruptHandler;
}

void IO_PC3_DefaultInterruptHandler(void)
{
    // add your IO_PC3 interrupt custom code
    // or set custom function using IO_PC3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC4 at application runtime
*/
void IO_PC4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC4_InterruptHandler = interruptHandler;
}

void IO_PC4_DefaultInterruptHandler(void)
{
    // add your IO_PC4 interrupt custom code
    // or set custom function using IO_PC4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC5 at application runtime
*/
void IO_PC5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC5_InterruptHandler = interruptHandler;
}

void IO_PC5_DefaultInterruptHandler(void)
{
    // add your IO_PC5 interrupt custom code
    // or set custom function using IO_PC5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC6 at application runtime
*/
void IO_PC6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC6_InterruptHandler = interruptHandler;
}

void IO_PC6_DefaultInterruptHandler(void)
{
    // add your IO_PC6 interrupt custom code
    // or set custom function using IO_PC6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC7 at application runtime
*/
void IO_PC7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC7_InterruptHandler = interruptHandler;
}

void IO_PC7_DefaultInterruptHandler(void)
{
    // add your IO_PC7 interrupt custom code
    // or set custom function using IO_PC7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD0 at application runtime
*/
void IO_PD0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD0_InterruptHandler = interruptHandler;
}

void IO_PD0_DefaultInterruptHandler(void)
{
    // add your IO_PD0 interrupt custom code
    // or set custom function using IO_PD0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD1 at application runtime
*/
void IO_PD1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD1_InterruptHandler = interruptHandler;
}

void IO_PD1_DefaultInterruptHandler(void)
{
    // add your IO_PD1 interrupt custom code
    // or set custom function using IO_PD1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD2 at application runtime
*/
void IO_PD2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD2_InterruptHandler = interruptHandler;
}

void IO_PD2_DefaultInterruptHandler(void)
{
    // add your IO_PD2 interrupt custom code
    // or set custom function using IO_PD2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD3 at application runtime
*/
void IO_PD3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD3_InterruptHandler = interruptHandler;
}

void IO_PD3_DefaultInterruptHandler(void)
{
    // add your IO_PD3 interrupt custom code
    // or set custom function using IO_PD3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD4 at application runtime
*/
void IO_PD4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD4_InterruptHandler = interruptHandler;
}

void IO_PD4_DefaultInterruptHandler(void)
{
    // add your IO_PD4 interrupt custom code
    // or set custom function using IO_PD4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD5 at application runtime
*/
void IO_PD5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD5_InterruptHandler = interruptHandler;
}

void IO_PD5_DefaultInterruptHandler(void)
{
    // add your IO_PD5 interrupt custom code
    // or set custom function using IO_PD5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD6 at application runtime
*/
void IO_PD6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD6_InterruptHandler = interruptHandler;
}

void IO_PD6_DefaultInterruptHandler(void)
{
    // add your IO_PD6 interrupt custom code
    // or set custom function using IO_PD6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD7 at application runtime
*/
void IO_PD7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD7_InterruptHandler = interruptHandler;
}

void IO_PD7_DefaultInterruptHandler(void)
{
    // add your IO_PD7 interrupt custom code
    // or set custom function using IO_PD7_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RGBLED_R at application runtime
*/
void RGBLED_R_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RGBLED_R_InterruptHandler = interruptHandler;
}

void RGBLED_R_DefaultInterruptHandler(void)
{
    // add your RGBLED_R interrupt custom code
    // or set custom function using RGBLED_R_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RGBLED_G at application runtime
*/
void RGBLED_G_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RGBLED_G_InterruptHandler = interruptHandler;
}

void RGBLED_G_DefaultInterruptHandler(void)
{
    // add your RGBLED_G interrupt custom code
    // or set custom function using RGBLED_G_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       IO_PA0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       IO_PA1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       IO_PA2_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       IO_PA3_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       IO_PA4_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       IO_PA5_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       IO_PA6_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       IO_PA7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTB_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTB.INTFLAGS & PORT_INT0_bm)
    {
       IO_PB0_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT1_bm)
    {
       IO_PB1_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT2_bm)
    {
       IO_PB2_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT3_bm)
    {
       IO_PB3_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT4_bm)
    {
       HBLED_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT5_bm)
    {
       RGBLED_B_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTB.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       IO_PC0_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       IO_PC1_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       IO_PC2_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       IO_PC3_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT4_bm)
    {
       IO_PC4_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT5_bm)
    {
       IO_PC5_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT6_bm)
    {
       IO_PC6_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT7_bm)
    {
       IO_PC7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT0_bm)
    {
       IO_PD0_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT1_bm)
    {
       IO_PD1_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       IO_PD2_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT3_bm)
    {
       IO_PD3_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       IO_PD4_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       IO_PD5_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       IO_PD6_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       IO_PD7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTE_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTE.INTFLAGS & PORT_INT0_bm)
    {
       IO_PE0_InterruptHandler(); 
    }
    if(VPORTE.INTFLAGS & PORT_INT1_bm)
    {
       IO_PE1_InterruptHandler(); 
    }
    if(VPORTE.INTFLAGS & PORT_INT2_bm)
    {
       IO_PE2_InterruptHandler(); 
    }
    if(VPORTE.INTFLAGS & PORT_INT3_bm)
    {
       IO_PE3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTE.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       IO_PF1_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       IO_PF0_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       RGBLED_R_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       RGBLED_G_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/