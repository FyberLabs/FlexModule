#include "DRV2605.h"
#include "i2c.h"
#define __PROG_TYPES_COMPAT__
#include <avr/pgmspace.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "defs.h"
#include "DRV2605_defs.h"

DRV2605::DRV2605()
{
	sbi( TWCR, TWEN );	// Enable TWI
}

bool DRV2605::autoCal( uint8_t ratedVoltage, uint8_t overdriveClamp, boolean LRA, uint8_t* compensation, uint8_t* backEMF, uint8_t* feedback )
{
	// Set defaults
	setDefaults();

	// Work out control registers
	uint8_t fb = FB_BRAKE_4x | FB_LOOP_FAST;// | (LRA ? FB_MODE_LRA : FB_MODE_ERM);
	uint8_t control1 = DEFAULT_CTRL1;

	if( LRA )
	{
		fb |= FB_MODE_LRA;
	}
	else
	{
		fb |= FB_MODE_ERM;
	}

	// Write required registers
	I2C_Write( ADDR_RATED_VOLT,		ratedVoltage );
	I2C_Write( ADDR_OD_CLAMP,		overdriveClamp );
	I2C_Write( ADDR_FEEDBACK,		fb );
	I2C_Write( ADDR_CTRL1,			control1 );
	I2C_Write( ADDR_MODE,			MODE_AUTOCAL );

	fb = GO;
	control1 = 0;
	I2C_Write( ADDR_GO,			GO );

	do
	{
		I2C_Read( ADDR_GO, &fb );
		delay( 100 );
		++control1;
	} while( fb & GO && control1 < 100 );

	// Read status bit
	I2C_Read( ADDR_STATUS, &fb );

	if( fb & STAT_DIAG_BAD )
	{
		//Results did not converge
		Serial.print(F( "Fail: " ));
		Serial.print( control1 );
		Serial.print(F( " tries. Status " ));
		Serial.println( fb, BIN );
		return false;
	}

	Serial.print(F( "Status " ));
	Serial.println( fb, BIN );

	I2C_Read( ADDR_AC_COMP,			compensation );
	I2C_Read( ADDR_AC_BACK_EMF,		backEMF );
	I2C_Read( ADDR_FEEDBACK,		feedback );
	return true;
}

void DRV2605::playFullHaptic( uint8_t library, uint8_t effect, uint8_t ratedVoltage, uint8_t overdriveClamp, uint8_t compensation, uint8_t backEMF, uint8_t feedback )
{
	// Set defaults
	setDefaults();

	// Work out control registers
	uint8_t fb = FB_BRAKE_4x | FB_LOOP_FAST | (6 == library ? FB_MODE_LRA : FB_MODE_ERM);	// Library 6 means LRA
	uint8_t control1 = DEFAULT_CTRL1;
	uint8_t control2 = DEFAULT_CTRL2;
	uint8_t control3 = DEFAULT_CTRL3;

	// Set saved BEMF Gain
	fb |= ( feedback & FB_BEMF_BITMASK );

	// Set open or closed loop based on library
	if( 1 == library )
		control3 |= CTRL3_ERM_OPEN;	// Set bit 5 for open loop operation
	else
		control3 &= ~CTRL3_ERM_OPEN;	// Clear bit 5 for closed loop operation

	noInterrupts();		// Protect I2C transaction from MPR121 interrupt.
	i2cSendStart();
		i2cSendByte( DRV2605_ADDR_WR );		// write 0xB4
		i2cSendByte( 0x16 );				// write first register address
		i2cSendByte( ratedVoltage );
		i2cSendByte( overdriveClamp );
		i2cSendByte( compensation );
		i2cSendByte( backEMF );
		i2cSendByte( fb );
		i2cSendByte( control1 );
		i2cSendByte( control2 );
		i2cSendByte( control3 );
	i2cSendStop();
	i2cSendStart();
		i2cSendByte( DRV2605_ADDR_WR );		// write 0xB4
		i2cSendByte( 0x03 );				// write first register address
		i2cSendByte( library );
		i2cSendByte( effect );
		i2cSendByte( MODE_ACTIVE );
	i2cSendStop();
	interrupts();

	I2C_Write( ADDR_MODE,			MODE_ACTIVE );     //0x01

	fb = GO;
	control1 = 0;
	I2C_Write( ADDR_GO,			GO );
	do
	{
		// For effect 118, we have to stop by clearing the GO bit.
		if ( 118 == effect ) 
		{
			// Let it run for 1 seconds.
			if ( 10 == control1 ) 
			{
				I2C_Write( ADDR_GO, STOP );     // Clear GO bit to stop effect.
			}

			delay( 100 );            
			++control1;
		}

		// Read GO bit to see if effect is still playing.
		I2C_Read( 0x0C, &fb );   
	} while ( fb & GO );
}

void DRV2605::setDefaults()
{ 
	noInterrupts();			// Protect I2C transaction from MPR121 interrupt.
	i2cSendStart();
		i2cSendByte( DRV2605_ADDR_WR );		// write 0xB4
		i2cSendByte( 0x01 );				// write 0xB4
		i2cSendByte( DEFAULT_MODE );
		i2cSendByte( DEFAULT_RTP_INPUT );
		i2cSendByte( DEFAULT_LIBRARY );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_WAV_SEQ );
		i2cSendByte( DEFAULT_GO );
		i2cSendByte( DEFAULT_OD_OFFSET );
		i2cSendByte( DEFAULT_ST_OFFSETP );
		i2cSendByte( DEFAULT_ST_OFFSETN );
		i2cSendByte( DEFAULT_BT_OFFSET );
		i2cSendByte( DEFAULT_A2H_CTRL );
		i2cSendByte( DEFAULT_A2H_MIN_IN );
		i2cSendByte( DEFAULT_A2H_MAX_IN );
		i2cSendByte( DEFAULT_A2H_MIN_OUT );
		i2cSendByte( DEFAULT_A2H_MAX_OUT );
		i2cSendByte( DEFAULT_RATED_VOLT );
		i2cSendByte( DEFAULT_OD_CLAMP );
		i2cSendByte( DEFAULT_AC_COMP );
		i2cSendByte( DEFAULT_AC_BACK_EMF );
		i2cSendByte( DEFAULT_FEEDBACK );
		i2cSendByte( DEFAULT_CTRL1 );
		i2cSendByte( DEFAULT_CTRL2 );
		i2cSendByte( DEFAULT_CTRL3 );
		i2cSendByte( DEFAULT_AC_MEM );
		i2cSendByte( DEFAULT_VBAT_VOLT );
		i2cSendByte( DEFAULT_LRA_RES );
	i2cSendStop();
	interrupts();
}

void DRV2605::I2C_Read( uint8_t address, uint8_t *data )
{
	noInterrupts();		// Protect I2C transaction from MPR121 interrupt, timer0, and usart
	i2cSendStart();		// start
		i2cSendByte(DRV2605_ADDR_WR);	// write 0xB4
		i2cSendByte(address);			// write register address
		i2cSendStart();					// repeated start
		i2cSendByte(DRV2605_ADDR_RD);	// write 0xB5
		data[0] = i2cReceiveByte(0);	// NACK	
	i2cSendStop();
	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI
	interrupts();
}

void DRV2605::I2C_Write( uint8_t address, uint8_t data )
{
	noInterrupts();		// Protect I2C transaction from MPR121 interrupt.
	i2cSendStart();
		i2cSendByte(DRV2605_ADDR_WR);	// write 0xB4
		i2cSendByte(address);			// write register address
		i2cSendByte(data);
	i2cSendStop();
	interrupts();
}
