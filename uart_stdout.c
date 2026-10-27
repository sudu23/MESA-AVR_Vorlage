/*
 * printf.c
 * Version: 1.0.0
 *
 *  Author: bub
 */

#include "mcc_generated_files/system/system.h"
#include <stdio.h>

int put_char(char c, FILE *stream)
{
    if (c == '\n')
    {
        while(!USART2_IsTxReady())
        {;}
        USART2_Write('\r');
    }
    
    while(!USART2_IsTxReady())
    {;}
    USART2_Write(c);
    
    return 0;
}

FILE mystdout = FDEV_SETUP_STREAM(put_char, NULL, _FDEV_SETUP_WRITE);
