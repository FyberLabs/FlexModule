# DipTrace Auto-Generated DO File
bestsave off
grid via 0.0039
grid wire 0.0039
define (class Dip_Net_Class_0 BOOT0 BOOT1 BOOT0P CP+ CP- ILIM NRST OSC32+ OSC32- PA0 PA1 PA2 PA3 PA4 PA5 PA6 PA7 PA8 PA15 PB0 PB1 PB4 PB5 PB6 PB7 PB8 PB9 PB10 PB12 PB13 PB14 PB15 PH0 PH1 SWCLK SWDIO SWO/PB3 TAMP USB_ID)
circuit class Dip_Net_Class_0 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_0 (width 8)
rule class Dip_Net_Class_0 (clearance 6)
define (class Dip_Net_Class_1)
circuit class Dip_Net_Class_1 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_1 (width 7.874)
rule class Dip_Net_Class_1 (clearance 6)
define (class Dip_Net_Class_2)
circuit class Dip_Net_Class_2 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_2 (width 9.8425)
rule class Dip_Net_Class_2 (clearance 6)
define (class Dip_Net_Class_3)
circuit class Dip_Net_Class_3 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_3 (width 13.7795)
rule class Dip_Net_Class_3 (clearance 6)
define (class Dip_Net_Class_4)
circuit class Dip_Net_Class_4 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_4 (width 5)
rule class Dip_Net_Class_4 (clearance 6)
define (class Dip_Net_Class_5 VCAP1 VDD VDDA)
circuit class Dip_Net_Class_5 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_5 (width 12)
rule class Dip_Net_Class_5 (clearance 6)
define (class Dip_Net_Class_6 Case)
circuit class Dip_Net_Class_6 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_6 (width 12)
rule class Dip_Net_Class_6 (clearance 5)
define (class Dip_Net_Class_7 D+ D- DM DP PA11 PA12)
circuit class Dip_Net_Class_7 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_7 (width 4.5)
rule class Dip_Net_Class_7 (clearance 5.71)
define (class Dip_Net_Class_8 SW VBUS Vbus_con Vbusin)
circuit class Dip_Net_Class_8 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_8 (width 31)
rule class Dip_Net_Class_8 (clearance 6)
define (class Dip_Net_Class_9 3-5V GND GNDin VBAT)
circuit class Dip_Net_Class_9 (use_via DipViaStyle_0 DipViaStyle_1)
rule class Dip_Net_Class_9 (width 42)
rule class Dip_Net_Class_9 (clearance 6)
rule pcb (pin_width_taper down)
bus diagonal
route 20
clean 2
route 25 16
clean 2
filter 5
recorner diagonal
