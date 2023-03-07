//this file for autonomous mission control
#include "constvars.h"
#include "miscfuncs.h"
#include "cardlogger.h"

#ifndef AUTO_MODE_h
#define AUTO_MODE_h

void automode()
{
  
//plot a course from current location to goal location (degrees heading)
  goalLat = Carray[0][waypoint];
  goalLong = Carray[1][waypoint];
  goalheading = TinyGPSPlus::courseTo(currentLat,currentLong,goalLat,goalLong);  
  
  if (currentheading < 0)
  {currentheading = 360 + currentheading;}

  hdiff = currentheading-goalheading;     //logic to decide how much throttle to give each motor based off current vs goal heading
  
  if(hdiff>180)   //so that it won't try ant turn around the "long" way left
  {hdiff-=360;}
  
  if(hdiff<(-180))  //so that it won't try and turn around the "long" way right
  {hdiff+=360;}
  
  if(hdiff>=0)
  {
    starbval = 180;
    portval = 180-(hdiff*5.0);      //5x multiplier is steering gain. higher value, more throttling per given angle difference
    if (portval<0)
    {portval = 0;}
  }
  else
  {
    portval = 180;
    starbval = 180+(hdiff*5.0);     //think there was an unknown bug here in the last version with a + where it should be - nevermind its cause if the sign of hdiff
    if (starbval<0)
    {starbval = 0;}
  }

  if(abs(hdiff)<10)       //let both motors be full throttle if its close
  {
    portval = 180;
    starbval = 180;
    lastgoodhead = millis();
  }
  
  if(millis()-lastgoodhead>60000) //log an error if it goes more than 60 seconds without reaching its target heading
  {logerror(3);}
 
  port.write(portval*Tm);              //set the motors to their determined throttles 
  starboard.write(starbval*Tm);

  d = gps.distanceBetween(currentLat, currentLong, goalLat, goalLong);      //check if you made it to a waypoint
  if ((d<12)&&(waypoint<ncoords))
  {waypoint++;}
}

#endif