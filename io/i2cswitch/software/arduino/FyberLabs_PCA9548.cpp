/****************************************************************************************
    This is a library for the Fyber Labs i2c Switch Flex Module

    Copyright (c) 2015 Chris Hamilton


    Permission is hereby granted, free of charge, to any person obtaining a copy of this 
    software and associated documentation files (the "Software"), to deal in the Software 
    without restriction, including without limitation the rights to use, copy, modify, 
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
    permit persons to whom the Software is furnished to do so, subject to the following 
    conditions:

    The above copyright notice and this permission notice shall be included in all copies 
    or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*****************************************************************************************/

#include "Fyberlabs_PCA9548.h"

Fyberlabs_PCA9548::Fyberlabs_PCA9548() {
}

boolean Fyberlabs_PCA9548::begin(uint8_t address) {
  _i2c_address = address;

  Wire.begin();
  return true;
}

unint8_t FyberLabs_PCA9548::readSwitchChannel(void) {
  return read8(PCA9548_I2CADDR);
}

void FyberLabs_PCA9548::writeSwitchChannel(uint8_t channel) {
  write8(PCA9548_I2CADDR, channel);
}

//Pass defined solder bridge hex to create the correct address
uint8_t FyberLabs_PCA9548::setSolderBridge(uint8)t address) {
  _i2c_address = _i2c_address | address;
  return _i2c_address;
}

//read/write structure borrowed from Adafruit
uint8_t FyberLabs_PCA9548::read8(uint8_t address) {
  uint8_t ret;

  Wire.beginTransmission(_i2c_address); // start transmission to device 
#if (ARDUINO >= 100)
  Wire.write(address); // sends register address to read from
#else
  Wire.send(address); // sends register address to read from
#endif
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(_i2c_address); // start transmission to device 
  Wire.requestFrom(_i2c_address, 1);// send data n-bytes read
#if (ARDUINO >= 100)
  ret = Wire.read(); // receive DATA
#else
  ret = Wire.receive(); // receive DATA
#endif
  Wire.endTransmission(); // end transmission

  return ret;
}

void FyberLabs_PCA9548::write8(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2c_address); // start transmission to device 
#if (ARDUINO >= 100)
  Wire.write(address); // sends register address to read from
  Wire.write(data);  // write data
#else
  Wire.send(address); // sends register address to read from
  Wire.send(data);  // write data
#endif
  Wire.endTransmission(); // end transmission
}
