#include "constvars.h"
#include <TinyGPSPlus.h>
#include <Adafruit_LIS2MDL.h>

#ifndef NAVIGATION_H
#define NAVIGATION_H

void navigate()
{
  smartDelay(100);
  
  if(gps.location.isValid())                  
  {
    currentLat = gps.location.lat();
    currentLong = gps.location.lng();  
  }
  else
  {
    logerror(2);  //loss of GPS data
  }
  
  if(!(gps.location.isUpdated()))
  {
    //logerror(7);  //error if gps isn't updating
  }
  
  sensors_event_t event;  //read mag sensor
  mag.getEvent(&event);

  currentheading = (((atan2(-(event.magnetic.y-yoff),(event.magnetic.x-xoff)) * 180) / Pi)+declination);
}

#endif