#include <Arduino.h> 
#include "HMC5883L.h"

HMC5883L::HMC5883L(byte newRes) {
  m_Scale = 1;
  resolution = newRes;
  average = 0;
}

float HMC5883L::turn(float newTarget) {
  float pos = getHeading();
  //if(pos >= 0 && pos < newTarget)
  //  pos+=360;
  //float displacement = pos - newTarget;
  //if(displacement > 180)
  //  displacement = (360+newTarget)-pos;
  return (pos);
  //displacement = constrain(displacement, -60, 60);
  //return map (displacement, -60, 60, -100, 100)/1000.0;

}

float HMC5883L::getHeading() {
  int iteration = 0;
  while(true) {
    if(iteration < resolution) {
      //Get the reading from the HMC5883L and calculate the heading
      MagnetometerScaled scaled = this->ReadScaledAxis(); //scaled values from compass.
      float heading = atan2(scaled.YAxis, scaled.XAxis);

      // Correct for when signs are reversed.
      if(heading < 0) heading += 2*PI;
      if(heading > 2*PI) heading -= 2*PI;

      average += (heading * RAD_TO_DEG) / (float)(int) resolution; //radians to degrees
      iteration++;
    } 
    if(iteration < resolution)
      delay(10);
    else
      break;
  }
  float tmp = average;
  average = 0;
  return tmp;
}

MagnetometerRaw HMC5883L::ReadRawAxis() {
  uint8_t* buffer = Read(DataRegisterBegin, 6);
  MagnetometerRaw raw = MagnetometerRaw();
  raw.XAxis = (buffer[0] << 8) | buffer[1];
  raw.ZAxis = (buffer[2] << 8) | buffer[3];
  raw.YAxis = (buffer[4] << 8) | buffer[5];
  return raw;
}

MagnetometerScaled HMC5883L::ReadScaledAxis() {
  MagnetometerRaw raw = ReadRawAxis();
  MagnetometerScaled scaled = MagnetometerScaled();
  scaled.XAxis = raw.XAxis * m_Scale;
  scaled.ZAxis = raw.ZAxis * m_Scale;
  scaled.YAxis = raw.YAxis * m_Scale;
  return scaled;
}

int HMC5883L::SetScale(float gauss) {
  uint8_t regValue = 0x00;
  if(gauss == 0.88) {
    regValue = 0x00;
    m_Scale = 0.73;
  }
  else if(gauss == 1.3) {
    regValue = 0x01;
    m_Scale = 0.92;
  }
  else if(gauss == 1.9) {
    regValue = 0x02;
    m_Scale = 1.22;
  }
  else if(gauss == 2.5) {
    regValue = 0x03;
    m_Scale = 1.52;
  }
  else if(gauss == 4.0) {
    regValue = 0x04;
    m_Scale = 2.27;
  }
  else if(gauss == 4.7) {
    regValue = 0x05;
    m_Scale = 2.56;
  }
  else if(gauss == 5.6) {
    regValue = 0x06;
    m_Scale = 3.03;
  }
  else if(gauss == 8.1) {
    regValue = 0x07;
    m_Scale = 4.35;
  }
  else
    return ErrorCode_1_Num;

  // Setting is in the top 3 bits of the register.
  regValue = regValue << 5;
  Write(ConfigurationRegisterB, regValue);
}

int HMC5883L::SetMeasurementMode(uint8_t mode) {
  Write(ModeRegister, mode);
}

void HMC5883L::Write(int address, int data) {
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t* HMC5883L::Read(int address, int length)
{
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(address);
  Wire.endTransmission();

  Wire.beginTransmission(HMC5883L_Address);
  Wire.requestFrom(HMC5883L_Address, length);

  uint8_t buffer[length];
  if(Wire.available() == length)
  {
    for(uint8_t i = 0; i < length; i++)
    {
      buffer[i] = Wire.read();
    }
  }
  Wire.endTransmission();

  return buffer;
}

char* HMC5883L::GetErrorText(int errorCode)
{
  if(ErrorCode_1_Num == 1)
    return ErrorCode_1;

  return "error not defined.";
}








