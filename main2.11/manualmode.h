//this file for manual drive control code
#include "constvars.h"
#include "pindefinitions.h"
#include "miscfuncs.h"

#ifndef MANUAL_MODE_h
#define MANUAL_MODE_h

void manualmode()
{
  //read pwm inputs from rc receiver
  throtval = readChannel(throt,0,100,0);
  steerval = readChannel(steer, -100,100,0);
  
  //find max pwm value based on limits and throttle
  manhigh = pwmlow+((pwmhigh-pwmlow)*Tm*throtval*.01);
  //set pwm values for both motors linearly between bounds based on steering input, reduce by the throttle amount
  portval = (map(steerval, -100,0,pwmlow,manhigh));
  starbval = (map(steerval, 0,100,manhigh,pwmlow));
  
  //safeguards to prevent out of bounts pwm output
  if(portval>(pwmlow+((pwmhigh-pwmlow)*Tm)))
  {portval = (pwmlow+((pwmhigh-pwmlow)*Tm));}
  if(starbval>(pwmlow+((pwmhigh-pwmlow)*Tm)))
  {starbval = (pwmlow+((pwmhigh-pwmlow)*Tm));}

  if(portval<pwmlow)
  {portval = pwmlow;}
  if(starbval<pwmlow)
  {starbval = pwmlow;}

  port.writeMicroseconds(portval);
  starboard.writeMicroseconds(starbval);
}

#endif