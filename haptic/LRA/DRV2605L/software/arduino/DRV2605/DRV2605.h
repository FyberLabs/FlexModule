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

#ifndef include_drv2306_h
#define include_drv2306_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class DRV2605
{
public:
	DRV2605();

	bool autoCal		( uint8_t ratedVoltage, uint8_t overdriveClamp, boolean LRA, 
							uint8_t* compensation, uint8_t* backEMF, uint8_t* feedback );

	void playFullHaptic	( uint8_t library, uint8_t effect, 
							uint8_t ratedVoltage, uint8_t overdriveClamp,  
							uint8_t compensation, uint8_t backEMF, uint8_t feedback );

private:
	void I2C_Read		( uint8_t address, uint8_t *data );
        void I2C_Write		( uint8_t address, uint8_t data );
	void setDefaults	();
};

#endif // include_drv2306_h
