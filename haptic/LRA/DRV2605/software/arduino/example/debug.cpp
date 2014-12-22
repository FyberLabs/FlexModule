#include "debug.h"
#include "defs.h"

#define __PROG_TYPES_COMPAT__
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SPI.h>

int freeRAM() 
{
	extern int __heap_start, *__brkval; 
	int v; 
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


