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

#ifndef include_drv2605_defs_h
#define include_drv2605_defs_h

// Addresses
#define ADDR_STATUS			0x00
#define ADDR_MODE			0x01
#define ADDR_RTP_INPUT		0x02
#define ADDR_LIBRARY		0x03
#define ADDR_WAV_SEQ1		0x04
#define ADDR_WAV_SEQ2		0x05
#define ADDR_WAV_SEQ3		0x06
#define ADDR_WAV_SEQ4		0x07
#define ADDR_WAV_SEQ5		0x08
#define ADDR_WAV_SEQ6		0x09
#define ADDR_WAV_SEQ7		0x0A
#define ADDR_WAV_SEQ8		0x0B
#define ADDR_GO				0x0C
#define ADDR_ODT			0x0D
#define ADDR_SPT			0x0E
#define ADDR_SNT			0x0F
#define ADDR_BRT			0x10
#define ADDR_A2H_CTRL		0x11
#define ADDR_A2H_MIN_IN		0x12
#define ADDR_A2H_MAX_IN		0x13
#define ADDR_A2H_MIN_OUT	0x14
#define ADDR_A2H_MAX_OUT	0x15
#define ADDR_RATED_VOLT		0x16
#define ADDR_OD_CLAMP		0x17
#define ADDR_AC_COMP		0x18
#define ADDR_AC_BACK_EMF	0x19
#define ADDR_FEEDBACK		0x1A
#define ADDR_CTRL1			0x1B
#define ADDR_CTRL2			0x1C
#define ADDR_CTRL3			0x1D
#define ADDR_AC_MEM			0x1E
#define ADDR_VBAT_VOLT		0x21
#define ADDR_LRA_RES		0x22


// Status
#define STAT_DEVICE_2604	0x80
#define STAT_DEVICE_2605	0xA0

#define STAT_DIAG_BAD		0x08
#define STAT_FB_TIME_OUT	0x04
#define STAT_OVERTEMP		0x02
#define STAT_OC_DETECT		0x01


// Modes
// - Register bits
#define MODE_ACTIVE			0x00
#define MODE_STANDBY		0x40
#define MODE_RESET			0x80
// - Mode definitions
#define MODE_INT_TRIG		0x00
#define MODE_EXT_TRIG_EDGE	0x01
#define MODE_EXT_TRIG_LVL	0x02
#define MODE_PWM_ANALOG		0x03
#define MODE_A2H			0x04
#define MODE_RTP			0x05
#define MODE_DIAGNOSTICS	0x06
#define MODE_AUTOCAL		0x07


// GO bits
#define GO					0x01
#define STOP				0x00


// Feedback control bits
#define FB_MODE_ERM			0x00
#define FB_MODE_LRA			0x80

#define FB_BRAKE_1x			0x00
#define FB_BRAKE_2x			0x10
#define FB_BRAKE_3x			0x20
#define FB_BRAKE_4x			0x30
#define FB_BRAKE_6x			0x40
#define FB_BRAKE_8x			0x50
#define FB_BRAKE_16x		0x60
#define FB_BRAKE_DISABLE	0x70

#define FB_LOOP_SLOW		0x00
#define FB_LOOP_MED			0x04
#define FB_LOOP_FAST		0x08
#define FB_LOOP_VERYFAST	0x0C

#define FB_BEMF_ERM_0p33	0x00
#define FB_BEMF_ERM_1p0		0x01
#define FB_BEMF_ERM_1p8		0x02
#define FB_BEMF_ERM_4p0		0x03

#define FB_BEMF_LRA_5x		0x00
#define FB_BEMF_LRA_10x		0x01
#define FB_BEMF_LRA_20x		0x02
#define FB_BEMF_LRA_30x		0x03

#define FB_BEMF_BITMASK		0x03


// Control bits
// - Control 1
#define CTRL1_STARTUPBOOST	0x80
#define CTRL1_BYPASSCOMP	0x40
#define CTRL1_AC_DOUBLE		0x20
#define CTRL1_DC_COUPLE		0x00

// - Control 2
#define CTRL2_BIDIR_IN		0x80
#define CTRL2_UNIDIR_IN		0x00
#define CTRL2_BRAKE_STAB	0x40

#define CTRL2_SAMPLE_150us	0x00
#define CTRL2_SAMPLE_200us	0x10
#define CTRL2_SAMPLE_250us	0x20
#define CTRL2_SAMPLE_300us	0x30

#define CTRL2_BT_VSHORT		0x00
#define CTRL2_BT_SHORT		0x04
#define CTRL2_BT_MED		0x08
#define CTRL2_BT_LONG		0x0C

#define CTRL2_ID_VSHORT		0x00
#define CTRL2_ID_SHORT		0x01
#define CTRL2_ID_MED		0x02
#define CTRL2_ID_LONG		0x03

// - Control 3
#define CTRL3_NGTHRESH_OFF	0x00
#define CTRL3_NGTHRESH_2PC	0x40
#define CTRL3_NGTHRESH_4PC	0x80
#define CTRL3_NGTHRESH_8PC	0xC0

#define CTRL3_ERM_CLOSED	0x00
#define CTRL3_ERM_OPEN		0x20
#define CTRL3_SC_DISABLE	0x10

#define CTRL3_RTP_SIGNED	0x00
#define CTRL3_RTP_UNSIGNED	0x08

#define CTRL3_LRA_DRIVE1	0x00
#define CTRL3_LRA_DRIVE2	0x04

#define CTRL3_IN_MODE_PWM	0x00
#define CTRL3_IN_MODE_AN	0x02

#define CTRL3_LRA_AUTORES	0x00
#define CTRL3_LRA_OPEN		0x01
#define CTRL3_LRA_CLOSED	0x00		


// Auto calibration 
#define AC_TIME_150ms		0x00
#define AC_TIME_200ms		0x10
#define AC_TIME_500ms		0x20
#define AC_TIME_1000ms		0x30


// Defaults
#define DEFAULT_STATUS		0xA0	// Addr 0x00
#define DEFAULT_MODE		0x00	// Addr 0x01 - Set default to be active
#define DEFAULT_RTP_INPUT	0x00	// Addr 0x02
#define DEFAULT_LIBRARY		0x00	// Addr 0x03
#define DEFAULT_WAV_SEQ		0x01	// Addr 0x04#
#define DEFAULT_GO		0x00	// Addr 0x0C
#define DEFAULT_OD_OFFSET	0x00	// Addr 0x0D
#define DEFAULT_ST_OFFSETP	0x00	// Addr 0x0E
#define DEFAULT_ST_OFFSETN	0x00	// Addr 0x0F
#define DEFAULT_BT_OFFSET	0x00	// Addr 0x10
#define DEFAULT_A2H_CTRL	0x05	// Addr 0x11
#define DEFAULT_A2H_MIN_IN	0x19	// Addr 0x12
#define DEFAULT_A2H_MAX_IN	0xFF	// Addr 0x13
#define DEFAULT_A2H_MIN_OUT	0x19	// Addr 0x14
#define DEFAULT_A2H_MAX_OUT	0xFF	// Addr 0x15
#define DEFAULT_RATED_VOLT	0x3B	// Addr 0x16
#define DEFAULT_OD_CLAMP	0x89	// Addr 0x17
#define DEFAULT_AC_COMP		0x0C	// Addr 0x18
#define DEFAULT_AC_BACK_EMF	0x1A	// Addr 0x19
#define DEFAULT_FEEDBACK	0x3A	// Addr 0x1A
#define DEFAULT_CTRL1		0x93	// Addr 0x1B
#define DEFAULT_CTRL2		0xB5	// Addr 0x1C
#define DEFAULT_CTRL3		0x84	// Addr 0x1D
#define DEFAULT_AC_MEM		0x20	// Addr 0x1E
#define DEFAULT_VBAT_VOLT	0x00	// Addr 0x21
#define DEFAULT_LRA_RES		0x38	// Addr 0x22

#endif // include_drv2605_defs_h
