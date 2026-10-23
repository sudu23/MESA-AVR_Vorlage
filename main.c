 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2026] Microchip Technology Inc. and its subsidiaries.

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

/*------------------------------------------------------------------------------
    Includes 
*/
#include "mcc_generated_files/system/system.h"
#include "util/delay.h"
#include "cyclesync.h"
#include "printf.h"
#include "PCF8574A.h"
#include "DS3234.h"
#include "MCP23008.h"

/*------------------------------------------------------------------------------
    Defines 
*/
#define LEDS_C  VPORTC.OUT
#define LEDS_D  VPORTD.OUT
#define TASTEN  VPORTA.IN
#define SCHALTER_LINKS ((VPORTE.IN)&0x0F)
#define SCHALTER_RECHTS ((VPORTB.IN)&0x0F)

/*------------------------------------------------------------------------------
    Global Variables 
*/

/*------------------------------------------------------------------------------
    Function Prototypes 
*/

/*
    Main application
*/
int main(void)
{
    //Local Variables
    ds3234_time_t mytime = {0};
    uint8_t value = 0;
    bool rtc_int;
    
    // Initialization microcontroller
    SYSTEM_Initialize();
    
    // Initialization cycle system with TIC-parameter 
    CycleSyncInit(1000);
    
    //set the output stream and show welcome message
    stdout = &mystdout;
    printf("MESA-AVR\n");
    
    // Initialization gpio
    RGBLED_R_SetHigh();
    RGBLED_G_SetHigh();
    RGBLED_B_SetHigh();
    
    // Initialization MESA-AVR-Extension Port-Expander
    //MCP23008_Init();
    
    //Set RTC-Time
//    mytime.year = 2026;
//    mytime.month = 8;
//    mytime.day = 20;
//    mytime.hour = 15;
//    mytime.minute = 22;
//    mytime.second = 0;
//    DS3234_SetTime(&mytime);
    
    //DS3234_GetTime(&mytime);
    printf("Zeit: %u:%u\n", (unsigned int)mytime.hour, (unsigned int)mytime.minute);
    printf("Datum: %u.%u.%u\n", (unsigned int)mytime.day, mytime.month, mytime.year);
    
    while(1)
    {
        CycleSync();
        
        HBLED_Toggle();
        
        //...programm...
        LEDS_C = ~TASTEN; 
        LEDS_D = SCHALTER_RECHTS | (SCHALTER_LINKS&0x0f)<<4;

        MCP23008_WriteByte(PCF8574A_PF,value);        
        MCP23008_WriteByte(PCF8574A_PG, (0xff-value));
        value++;
        
        MCP23008_MIXEDSIGNALS_SetLED1(value&0x01);
        MCP23008_ReadPin(PCF8574A_MIXEDSIGNALS,6,&rtc_int);       
        MCP23008_MIXEDSIGNALS_SetLED2(rtc_int);
        
        //DS3234_GetTime(&mytime);
        printf("Zeit: %u:%u\n", (unsigned int)mytime.hour, (unsigned int)mytime.minute);        
    }    
}
