//for writing data to the sd card. 

#include <SD.h>
#include <SPI.h>

#include "constvars.h"

#ifndef CARD_LOGGER_H
#define CARD_LOGGER_H

void blackboxwrite()
{
  if((millis()-bblast)>(bbint*1000))
  {
    blackbox = SD.open("blackbox.txt", FILE_WRITE);
    if(!blackbox)
    {return;}
    blackbox.println(" ");
    blackbox.print(millis()/1000);
    blackbox.print(", ");
    blackbox.print(autostate);
    blackbox.print(", ");
    blackbox.print(currentLat,6);  //gps coordinates go out to at least 5 decimal points
    blackbox.print(", ");
    blackbox.print(currentLong,6);
    blackbox.print(", ");
    blackbox.print(currentheading);
    blackbox.print(", ");
    blackbox.print(waypoint);
    blackbox.print(", ");
    blackbox.print(portval);
    blackbox.print(", ");
    blackbox.print(starbval);
    blackbox.print(", ");
    blackbox.print(motI);
    blackbox.print(", ");
    blackbox.print(motV);
    blackbox.print(", ");
    blackbox.print(solI);
    blackbox.print(", ");
    blackbox.print(solV);
    blackbox.close();
    bblast = millis();
  }
}

void pingwrite()
{
  if((millis()-depthlast)>(depthint*1000))
  {
    depthlog = SD.open("depthlog.txt", FILE_WRITE);
    if(!depthlog)
    {return;}
    
    depthlog.println(" ");
    depthlog.print(currentLat,6); //just so it prints more digits, otherwise it'll truncate to 2 decimal places
    depthlog.print(", ");
    depthlog.print(currentLong,6);
    depthlog.print(", ");
    depthlog.print(depth);
    depthlog.close();
    depthlast = millis();
  }
}

void logerror(byte e)
{
  errorlog = SD.open("errorlog.txt", FILE_WRITE);
  if(!errorlog)
  {return;}

  switch (e)
  {
    case 1:
      errorlog.println(" ");
      errorlog.print(millis()/1000);    //time at which an error occurred
      errorlog.print(" CURRENT LIMIT EXCEEDED");
      break;
    
    case 2:
      if(millis()-laste2>5000)    //so it doesn't log a million errors in a row
      {
        errorlog.println(" ");
        errorlog.print(millis()/1000);    //time at which an error occurred
        errorlog.print(" GPS SIGNAL LOST");
        laste2 = millis();
      }
      break;
      
    case 3:
      if(millis()-laste3>5000)    //so it doesn't log a million errors in a row
      {
        errorlog.println(" ");
        errorlog.print(millis()/1000);    //time at which an error occurred
        errorlog.print(" CAN'T REACH TARGET HEADING");
        laste3 = millis();
      }
      break;
      
    case 4:
      errorlog.println(" ");
      errorlog.print(millis()/1000);    //time at which an error occurred
      errorlog.print(" MAGNETOMETER INITIALIZATION ERROR");
      break;
      
    case 5:
      errorlog.println(" ");
      errorlog.print(millis()/1000);    //time at which an error occurred
      errorlog.print(" SONAR INITIALIZATION ERROR");
      break;
    
    case 6:
      if(millis()-laste6>5000)
      {
        errorlog.println(" ");
        errorlog.print(millis()/1000);    //time at which an error occurred
        errorlog.print(" LOW SONAR CONFIDENCE");
        laste6 = millis();
      }
      break;
      
    case 7:
      if(millis()-laste7>10000)
      {
        errorlog.println(" ");
        errorlog.print(millis()/1000);    //time at which an error occurred
        errorlog.print(" GPS NOT UPDATING");
        laste7 = millis();
      }
      break;
  }
  
  errorlog.close();
}

#endif
