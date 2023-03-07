#include "constvars.h"
#include "cardlogger.h"
#include <ping1d.h>
#include <SoftwareSerial.h>

#ifndef DEPTH_PING_H
#define DEPTH_PING_H

void depthping()
{
  if(ping.update())
  {
    depth = ping.distance();
    int c = ping.confidence();
    
    if(c<10)
    {
      logerror(6);  //give an error if low confidence
    }
  }
}

#endif