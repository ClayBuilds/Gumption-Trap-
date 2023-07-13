//this file for reading INA260 sensors and refernce battery voltage

#include "constvars.h"
#include "pindefinitions.h"
#include "cardlogger.h"
#include <Adafruit_INA260.h>
#include <Servo.h>

#ifndef POWER_SENSE_H
#define POWER_SENSE_H

void powersense()
{
  motI = motpow.readCurrent();
  solI = solpow.readCurrent();
  motV = motpow.readBusVoltage();
  solV = solpow.readBusVoltage();
  
  if(solI<0)    //otherwise it would float between 0 and -1.25mA in darkness. 
  {solI = 0;}
  
  if(motI>motIlimit)         //cut throttle in the event of excessive current draw to prevent brownout/shutdown
  {
    port.write(0);          //set throttles to zero
    starboard.write(0);
    logerror(1);
    delay(5000);
  }
}

#endif
