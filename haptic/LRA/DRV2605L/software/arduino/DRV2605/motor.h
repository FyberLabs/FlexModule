// This Software is part of the Precision Microdrives Haptic Shield demo and is
// provided under the MIT License

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

#ifndef include_motor_h
#define include_motor_h

#include "defs.h"
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


typedef struct {
	uint8_t id;
	boolean LRA;			// TRUE if LRA, else ERM.
	uint8_t min_duty;		// Minimum PWM duty cycle to start ERM 0 = 0%, 511 = 100%
	uint8_t rated_duty;		// Rated PWM duty cycle to run ERM 0 = 0%, 511 = 100% = 3.3V
	uint8_t max_duty;		// Maximum PWM duty cycle to run ERM 0 = 0%, 511 = 100%
	char part_num[8];		// Part number string.
} MotorInfo;


class Motor
{
public:
	Motor();
	
	void	selectMotor		( uint8_t motorID );
	bool	isCalibrated	        ();
	void	autoCalibrate	        ();
	void	playVibAlert	        ( uint8_t waveform, uint8_t pwr, uint8_t onTime, uint8_t offTime );
	void	playFullHaptic	        ( uint8_t library, uint8_t effect );

	uint8_t	getMotorID		();
	bool	isPlaying		();
	bool	isPlayingVib	        ();
	void	stopVibAlert	        ();

	const char* getMotorName();

private:
	uint8_t	selectedMotor;
	boolean	stopPlaying;

	void readMotorInfo	        ( uint8_t id, MotorInfo* info );
	bool isMotorCaled	        ( uint8_t id );
	void calibrate		        ( MotorInfo* info );
	void setMotorCal	        ( uint8_t id, uint8_t compensation, uint8_t backEMF, uint8_t feedback );
	bool getMotorCal	        ( uint8_t id, uint8_t* compensation, uint8_t* backEMF, uint8_t* feedback );
	void selectGripMotor            ( uint8_t id );

	int calculatePWR	        ( uint8_t waveform, int t );
};

const static uint8_t __attribute__ ((progmem)) halfsineTable[] ={0,16,31,45,59,71,81,89,95,99,100};  //full sine wave 20

// The motor table
const static MotorInfo __attribute__ ((progmem)) motorTable[ NUM_MOTORS ] ={
	{ 0,	false,	56,	66,	87,	"305-000" },	// M0 - ERM 305-000, min 1.1V, rated 1.3V, max 1.7V
	{ 1,	false,	51,	153,	184,	"306-109" },	// M1 - ERM 306-109, min 1.0V rated 3.0V max 3.6V
	{ 2,	false,	77,	230,	255,	"308-102" },	// M2 - ERM 308-102, min 1.5V, rated 4.5V, max 5.5V
	{ 3,	true,	15,	102,	105,	"C10-100" },	// M3 - LRA, C13-000 min 0.3 Vrms, rated 2 Vrms, max 2.05 Vrms
};

#endif // include_motor_h
