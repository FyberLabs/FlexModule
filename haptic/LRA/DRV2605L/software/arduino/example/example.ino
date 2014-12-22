#include <Wire.h>
#include <defs.h>
#include <types.h>

// This Software demo for the Precision Microdrives Haptic Shield is provided
// under the MIT License

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// Include system headers
#define __PROG_TYPES_COMPAT__
#include <avr/pgmspace.h>

#include <i2c.h>

// Debug
#include "debug.h"

// Include our headers
#include "Metro.h"
#include "motor.h"

// Init timer for 2s, and auto-reset when we get a positive check
Metro timer( 2000, 1 );
Motor motor = Motor();

void setup()
{
	// Setup serial
	Serial.begin( 9600 );
	Serial.print( F("FreeMem=") );
	Serial.println( freeRAM() );
	
	setupPins();
	i2cInit( 200 );
	
	// Set up the motor
	motor.selectMotor( 0 );
	motor.autoCalibrate();

	// Ensure any time for calibration is ignored.
	timer.reset();
}

void loop()
{
	// Example code - check for some condition
	// N.B. We play an effect every second
	uint8_t condition = timer.check();
	
	if( condition )
	{
		// Do an effect
		motor.playFullHaptic( 1, 53 );
	}
}

void setupPins()
{
	pinMode( SW_LRA_M,		OUTPUT );	// Output for switching LRA+/- v.s. M+/-
	pinMode( SW_MOS_DRV,	OUTPUT );	// Output for switching +3.3V/MOS- v.s. DRV+/-
	pinMode( DRV_2605_EN,	OUTPUT );	// Output for ERV2605 ENable
	pinMode( PWM_OUT,		OUTPUT );	// Output for PWM

	digitalWrite( SW_LRA_M,		LOW );	// Select M+ and M- 
	digitalWrite( SW_MOS_DRV,	HIGH );	// Select +3.3V and MOS- 
	digitalWrite( DRV_2605_EN,	LOW );	// Disable the DRV2605 (low power mode)
	digitalWrite( PWM_OUT,		LOW );	// PWM output low for now 

	pinMode( MOTOR_PIN_0,	OUTPUT );	// Motor select 1
	pinMode( MOTOR_PIN_1,	OUTPUT );	// Motor select 2
}	// setupPins


