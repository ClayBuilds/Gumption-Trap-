//miscellanous functions used for multiple things
#include "constvars.h"

#ifndef MISC_FUNCS_h
#define MISC_FUNCS_h

//for delaying while still reading gps coords
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

//pulls the coordinates off of the SD card
static void readcard()
{ 
  coords = SD.open("COORDS.txt", FILE_READ);
  while(j<(ncoords+1))      //while theres still data to be read
  {
    char aChar = coords.read();           //read all the data, put them into a char array
    if(aChar != '\n' && aChar != '\r')
    {
      cardcontents[i++] = aChar;
      cardcontents[i] = '\0'; 
    }
    else
    {
      if(strlen(cardcontents) > 0)
      {
        float Val = atof(cardcontents);     //convert data into floats

        Carray[k][j] = Val;       
        if(k==1)
        {j++;}
        k++;
        if(k > 1)       //alternate every other one to switch between latitude/longitude
        {k-=2;}

        if(j<2)
        {
          ncoords = Carray[1][0];     //the first number in the file is the number of coordinate pairs. 
        }
      }
      cardcontents[0] = '\0';
      i = 0;
    }
  }
  coords.close(); 
}

//This is to read a pwm radio channel
int readChannel(int inpin, int minlim, int maxlim, int defaultval)
{
  int val = pulseIn(inpin, HIGH, 30000);
  if(val<100)
    {return defaultval;}  
  return map(val, 1000,2000,minlim,maxlim);
}
//This one reads a switch
bool readSwitch(byte switchin, bool defaultval)
{
  int dval = (defaultval)? 100: 0;
  int out = readChannel(switchin, 0,100, dval);       //this out variable is floating around
  return (out>50);                               //making this abs(out) kinda helps but still a ton of floating
}

void printvals()
{
  Serial.print("     motI: ");
  Serial.print(motI);
  Serial.print("     solI: ");
  Serial.print(solI);
  Serial.print("     motV: ");
  Serial.print(motV);
  Serial.print("     solV: ");
  Serial.print(solV);
  Serial.print("     Lat: ");
  Serial.print(currentLat,6);
  Serial.print("     Long: ");
  Serial.print(currentLong,6);
  Serial.print("     Head: ");
  Serial.print(currentheading);
  Serial.print("     Depth: ");
  Serial.println(depth);
}

void printCoords()
{
  for(n=0;n<=ncoords;n++)
  {
    Serial.print(Carray[0][n],6);
    Serial.print(F(" - "));
    Serial.print(Carray[1][n],6);
    Serial.println(F(" "));
  }
} 

#endif
