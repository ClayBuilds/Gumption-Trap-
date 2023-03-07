//Clay McPherson
//3-2-2023

//GUMPTION TRAP MAIN CODE
//This code written for PCB v1.2
//Code Version 2.10

//changes from v2.9:
/*
  -fixed bug where it would turn "the long way around" in auto mode (ie 250 degrees left instead of 110 degrees right)
  -this was due to it subtracting 360 if hdiff was more than 180, but not adding 360 if hdiff was less than negative 180
  -increased throttle limit to 50%
  -decreased waypoint closeness threshold to 12m
  -temparily disable e7 cause it goes off constantly even when things work
*/

//TESTED and:
/*
  -
*/

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_LIS2MDL.h>       
#include <Servo.h>
#include <Adafruit_INA260.h>
#include <ping1d.h>

#include "pindefinitions.h"
#include "miscfuncs.h"
#include "constvars.h"
#include "manualmode.h"
#include "automode.h"
#include "powersense.h"
#include "cardlogger.h"
#include "depthping.h"
#include "navigation.h"




void setup() 
{
  Serial.begin(9600);
 
  if(!SD.begin(cs))
  {
    cardfailed = true;
    Serial.println("couldn't initialize");
  }
  else
  {
    cardfailed = false;
    Serial.println("SD Card Initialized");
  }

  if(!SD.exists("COORDS.txt"))
  {
    cardfailed = true;
    Serial.println("File Missing");
  }

  //pull coords off SD Card
  if(!cardfailed)
  {
    readcard();
    printCoords();
  }
  else
  {
    Serial.println(F("Card read failed"));
  }

  //check for magnetometer error
  if(!mag.begin())              //need to uncomment this for mag to work, temp commented for memory space
  {
    magerr = true;
    Serial.println("MAG ERROR");
    logerror(4);
  } 
  
  //setup ping sounder 
  Serial2.begin(9600);
  if(!ping.initialize())
  {
    Serial.println("PING ERROR");
    logerror(5);
  }
  
  //initialize gps serial connection
  Serial1.begin(9600);
  
  //drive control setup
  pinMode(throt, INPUT);
  pinMode(steer, INPUT);
  pinMode(swt, INPUT);

  //initialize motors
  port.attach(pmot,1000,2000);
  starboard.attach(smot,1000,2000);

  port.write(0);          //set throttles to zero to make sure ESC's will start up.
  starboard.write(0);
  
  //setup power measurement chips (INA260)
  motpow.begin(0x41);   //note: one module needs a solder jumper so that they have different I2C addresses
  solpow.begin(0x40);
  
  smartDelay(5000); 
  Serial.println("setup over");
}

void loop() 
{
  switchval = readSwitch(swt, false);  
  powersense();
  depthping();
  printvals();
  blackboxwrite();
  pingwrite();
  navigate();
  
  if(!switchval)  
    {autostate = true;}
  else    
    {autostate = false;}  
    
  if(autostate)    
    {automode();}
  else
    {manualmode();} 
}
