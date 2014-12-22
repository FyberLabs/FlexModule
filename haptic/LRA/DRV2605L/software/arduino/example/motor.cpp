#include "motor.h"
#include "DRV2605.h"
#include "Metro.h"
#include <EEPROM.h>

bool playing = false;
bool playingVIB = false;

DRV2605 drv2605 = DRV2605();
MotorInfo currentMotor;

// We save auto calibration results from the DRV2605 in RAM
// This stops us having to auto-calibrate every time we switch motors
uint8_t calibrations[ NUM_MOTORS ][ 3 ];
bool calibrated[ NUM_MOTORS ] = { false, false, false, false };

Motor::Motor()
:	stopPlaying( false )
,	selectedMotor( 255 )
{
}

// ---
// Public API functions
// ---
void Motor::selectMotor( uint8_t motorID )
{
	selectedMotor = motorID;
	readMotorInfo( selectedMotor, &currentMotor );

	Serial.print( F("Selecting motor " ));
	Serial.println( currentMotor.part_num );

	selectGripMotor( motorID );
}

bool Motor::isCalibrated()
{
	return selectedMotor >= 0 && selectedMotor < NUM_MOTORS && calibrated[ selectedMotor ];
}

void Motor::autoCalibrate()
{
	if( selectedMotor < 0 || selectedMotor >= NUM_MOTORS )
		return;

	calibrate( &currentMotor );
}

void Motor::playVibAlert( uint8_t waveform, uint8_t pwr, uint8_t onTime, uint8_t offTime )
{
	stopPlaying = false;
	
	if( isPlaying() || isPlayingVib() )
	{
		Serial.println( F( "Already playing effect" ) );
		return;
	}

	if( currentMotor.LRA )
	{
		Serial.println( F("No Vib Alerts on LRA motor" ));
		return;
	}

	Serial.println( F("Playing Vib Alert" ));
	playing = true;
	playingVIB = true;
	uint8_t on = true;
	uint8_t lTime = onTime;      // contains time in ms * 100

	uint8_t pwr_range = currentMotor.rated_duty - currentMotor.min_duty;
	uint16_t currentPWR;

	// Setup PWM for 31.25kHz and specified % duty.
	TCCR1A |= (1<<COM1A1) | (1<<WGM10);   // 8 bit fast  PWM, not inverted, output on OC1A (D9) A.K.A. PWM_OUT
	TCCR1B |= (1<<WGM12) | (1<<CS10);    //  8 bit fast PWM, prescaler /1
	OCR1A = 0;

	long startTime = millis();

	while( !stopPlaying )
	{
		int t = (millis() - startTime) / lTime ;  

		if( on )
		{        
			currentPWR = ( (uint16_t) pwr * pwr_range ) / ( uint16_t ) 100;  // pwr is 0 to 100
			currentPWR = (uint16_t) (currentPWR * calculatePWR( waveform, t )) / ( uint16_t ) 100;  // calculate power returns 0 - 100
			currentPWR += currentMotor.min_duty;
			OCR1A = currentPWR;	// OCR1 is 0-255 

			if( t >= 100 )	// 30ms * 100( min time period)
			{
				if( offTime > 0 )
				{
					lTime = offTime;
					on = false;
					OCR1A = 0;
				}

				startTime = millis();
			}
		}

		else if( t >= 100 )        // if on = false and t=> 1 now should be immediate
		{
			startTime = millis();
			lTime = onTime;
			on = true;
		}
	}//while

	TCCR1A = 0x00; // No PWM
	TCCR1B = 0x00; // stop timer 1
	OCR1A=0;
	digitalWrite( PWM_OUT, LOW ); // PWM output low until further notice.
	playingVIB = false; 
	playing = false;
}

void Motor::playFullHaptic( uint8_t library, uint8_t effect )
{
	if( isPlaying() || isPlayingVib() )
	{
		Serial.println( F( "Already playing effect" ) );
		return;
	}
	
	stopPlaying = false;
	playing = true;

	digitalWrite( SW_LRA_M,		LOW );	// Select the grip
	digitalWrite( SW_MOS_DRV,	LOW );	// Select DRV+ and DRV- 
	digitalWrite( DRV_2605_EN,	HIGH );	// Enable the DRV2605

	uint8_t compensation, backEMF, feedback;
	if( !getMotorCal( selectedMotor, &compensation, &backEMF, &feedback ) )
	{
		Serial.println( F("Not playing effect. Motor is not calibrated. Need to call autoCalibrate for this motor.") );
		playing = false;
		return;
	}

	if( currentMotor.LRA )
	{
		library = 6;
	}
	else
	{
		if( library < 1 )
			library = 1;
		else if( library > 5 )
			library = 5;
	}

	if( effect < 1 )
		effect = 1;
	else if( effect > 124 )
		effect = 124;

	Serial.print( F("Playing library ") );
	Serial.print( library, DEC );
	Serial.print( F(" effect ") );
	Serial.print( effect, DEC );
	Serial.print( F(" on ") );
	Serial.println( getMotorName() );

	drv2605.playFullHaptic( library, effect, currentMotor.rated_duty, currentMotor.max_duty, compensation, backEMF, feedback );

	digitalWrite( DRV_2605_EN,	LOW );	// Disable the DRV2605 (low power mode)
	digitalWrite( SW_MOS_DRV,	HIGH );	// Select +3.3V and MOS- 
	digitalWrite( SW_LRA_M,		LOW );	// Select M+ and M-

	playing = false;
}

uint8_t Motor::getMotorID()
{
	return selectedMotor;
}

bool Motor::isPlaying()
{
	return playing;
}

bool Motor::isPlayingVib()
{
	return playingVIB;
}

void Motor::stopVibAlert()
{
	stopPlaying = true;
}

const char* Motor::getMotorName()
{
	return currentMotor.part_num;
}


// ---
// Helper functions
// ---

void Motor::readMotorInfo( uint8_t id, MotorInfo* info )
{
	info->id = pgm_read_byte( &motorTable[ id ].id );
	info->LRA = pgm_read_byte( &motorTable[ id ].LRA );
	info->min_duty = pgm_read_byte( &motorTable[ id ].min_duty );
	info->rated_duty = pgm_read_byte( &motorTable[ id ].rated_duty );
	info->max_duty = pgm_read_byte( &motorTable[ id ].max_duty );
	info->LRA = pgm_read_byte( &motorTable[ id ].LRA );
	
	for( uint8_t i = 0 ; i < 7 ; ++i ) 
	{ // strncpy_P() doesn't like a volatile target, so do it like this:
		info->part_num[ i ] = pgm_read_byte( &motorTable[ id ].part_num[ i ] );
	}
	
	info->part_num[ 7 ] = 0; // Be sure zero terminated.
}

bool Motor::isMotorCaled( uint8_t id )
{
	if( id < 0 || id >= NUM_MOTORS )
		return false;

	return calibrated[ id ];
}

void Motor::calibrate( MotorInfo* info )
{
	digitalWrite( SW_LRA_M,		LOW );	// Select the LRA on the shield or M+ and M- to connect the grip.
	digitalWrite( SW_MOS_DRV,	LOW );	// Select DRV+ and DRV- 
	digitalWrite( DRV_2605_EN,	HIGH );	// Enable the DRV2605

	// Select motor on grip
	selectGripMotor( info->id );

	// Auto calibrate the motor
	uint8_t compensation, backEMF, feedback;

	if( drv2605.autoCal( 
			info->rated_duty,
			info->max_duty,
			info->LRA,
			&compensation, &backEMF, &feedback ) )
	{
		Serial.println( F("AutoCal success" ));
		setMotorCal( info->id, compensation, backEMF, feedback );
	}
	else
	{
		Serial.println( F("AutoCal failed" ));
	}

	digitalWrite( DRV_2605_EN,	LOW );	// Disable the DRV2605 (low power mode)
	digitalWrite( SW_MOS_DRV,	HIGH );	// Select +3.3V and MOS- 
	digitalWrite( SW_LRA_M,		LOW );	// Select M+ and M-
}

void Motor::setMotorCal( uint8_t id, uint8_t compensation, uint8_t backEMF, uint8_t feedback )
{
	if( id < 0 || id >= NUM_MOTORS )
		return;

	calibrations[ id ][ 0 ] = compensation;
	calibrations[ id ][ 1 ] = backEMF;
	calibrations[ id ][ 2 ] = feedback;
	calibrated[ id ] = true;
}

bool Motor::getMotorCal( uint8_t id, uint8_t* compensation, uint8_t* backEMF, uint8_t* feedback )
{
	if( id < 0 || id >= NUM_MOTORS )
		return false;
		
	if( !calibrated[ id ] )
		return false;

	*compensation = calibrations[ id ][ 0 ];
	*backEMF = calibrations[ id ][ 1 ];
	*feedback = calibrations[ id ][ 2 ];
	return true;
}

void Motor::selectGripMotor( uint8_t id )
{
	digitalWrite( MOTOR_PIN_0,	id % 2 == 0 ? LOW : HIGH );
	digitalWrite( MOTOR_PIN_1,	id > 1 ? HIGH : LOW );
}

int Motor::calculatePWR( uint8_t waveform, int t )
{
	if( t < 0 )  t = 0;
	else if( t > 100 ) t = 100;

	switch( waveform )
	{
		// Square
		default:
		case 0:
			t = 100;  // not this is divider in 
			break;

		// Sine
		case 1:	
			t /= 5;    // reduce range to <0 , 20>
			t -= 10;    // move range from <0, 20> to <-10 ,10>
			t = 10 - (abs( t ));   // now range is 0-10-0 
			t = pgm_read_byte( &halfsineTable[ t ]);
			break;

		// Triangle
		case 2:
			t -= 50;    // move range from <0, 100> to <-50 ,50>
			t = 100 - (abs( t ) * 2 );
			break;

		// Sawtooth
		case 3:
			//   return t without changes          
			break;
	}

	return t; 
}
