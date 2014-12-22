//      This library provides the high-level functions needed to use the I2C
//	serial interface supported by the hardware of several AVR processors.
#include "i2c.h"


void i2cInit(unsigned int bitrate_kHz)
{
	unsigned char bitrate_div;
	
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);  // Prescaler = divide by 1. Note:  Only good for 31KHz to 1MHz.  For lower, use proscaler.
    bitrate_div = ( ( ( (int32_t)F_CPU / ( (int32_t)1000 * (int32_t)bitrate_kHz )) - (int32_t)16 ) / (int32_t)2);

	TWBR = bitrate_div;
	TWCR = (1<<TWEN);	// Enable TWI
}
//------------------------- I2C Start -------------------------------------------------------
void i2cSendStart(void)
{	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);	// send start condition
	while (!(TWCR & (1<<TWINT)));
}

//------------------------ I2C Stop ---------------------------------------------------------

void i2cSendStop(void)
{
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		// transmit stop condition
		while (!(TWCR & (1<<TWSTO)));				// change !!!! this line is added
}

//------------------------ I2C send byte -----------------------------------------------------

void i2cSendByte(unsigned char data)			// faster byte sending
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

//------------------------- I2C receive byte --------------------------------------------------

unsigned char i2cReceiveByte(unsigned char ackFlag)
{
	if(ackFlag)ackFlag=1;  // flag might be > 1 so sign it to 1
	TWCR = (1<<TWINT)|(ackFlag<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}
