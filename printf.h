/* 
 * File:   printf.h
 * Author: bub
 *
 * Created on March 4, 2026, 3:52 PM
 */

#ifndef PRINTF_H
#define	PRINTF_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>

int put_char(char c, FILE *stream);

extern FILE mystdout;

#ifdef	__cplusplus
}
#endif

#endif	/* PRINTF_H */
