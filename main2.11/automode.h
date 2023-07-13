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
  
  if(hdiff>=0) //left turn
  {
    goalstarb = ahigh;    //set starboard motor to highest speed allowed by the throttle limiter
    goalport = ahigh-(sgain*(hdiff/90)*((ahigh)-pwmlow));      //reduce port motor throttle by an amount proportional to how far off heading it is
    if (goalport<pwmlow)
    {goalport = pwmlow;} //safeguard in case a high gain tries to make it reduce the throttle below zero 
  }
  else  //right turn
  {
    goalport = ahigh;
    goalstarb = ahigh+(sgain*(hdiff/90)*((ahigh)-pwmlow));    //same as left turn, but sign changed because hdiff will be negative here
    if (goalstarb<pwmlow)
    {goalstarb = pwmlow;}
  }

  if(abs(hdiff)<10)       //let both motors be full throttle if its close
  {
    goalport = ahigh;
    goalstarb = ahigh;
    lastgoodhead = millis();
  }
  
  if(millis()-lastgoodhead>60000) //log an error if it goes more than 60 seconds without reaching its target heading
  {logerror(3);}
 
  adjustpwm(goalport, 0);              //set the motors to their determined throttles 
  adjustpwm(goalstarb, 1);

  d = gps.distanceBetween(currentLat, currentLong, goalLat, goalLong);      //check if you made it to a waypoint
  if ((d<12)&&(waypoint<ncoords))
  {waypoint++;}
}

#endif