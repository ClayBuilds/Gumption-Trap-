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
  
  portval = (map(steerval, -100,100,0,360))*throtval*.01;
  starbval = (map(steerval, -100,100,360,0))*throtval*.01;

  if(portval>180)
  {portval = 180;}
  if(starbval>180)
  {starbval = 180;}

  if(portval<0)
  {portval = 0;}
  if(starbval<0)
  {starbval = 0;}

  port.write(portval*Tm);
  starboard.write(starbval*Tm);
}

#endif