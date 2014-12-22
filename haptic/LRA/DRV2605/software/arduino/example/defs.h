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

#ifndef include_defs_h
#define include_defs_h
// OLED
#define OLED_DC			8
#define OLED_CS			5
#define OLED_CLK		13
#define OLED_MOSI		11
#define OLED_RESET		10
// Pin values
#define SW_LRA_M		7
#define SW_MOS_DRV		6
#define DRV_2605_EN		4
#define PWM_OUT			9

// Motors
#define NUM_MOTORS		4
#define MOTOR_PIN_0		A0
#define MOTOR_PIN_1		A1
#define KEY_MOTOR_ID	3

// DRV2605
#define DRV2605_ADDR_WR	0xB4
#define DRV2605_ADDR_RD	0xB5

// EEPROM saved settings
#define MOTOR_VALS_ADDR	0x00	// Address of the calibration bitmask
#define MOTOR_AC_ADDR	0x01	// Address to start saving autocal vals
#define MOTOR_AC_SIZE	0x03	// 3 bytes per autocal
#define MOTOR_AC_LEN	0x0C	// MOTOR_AC_SIZE * NUM_MOTORS

#endif // include_defs_h
