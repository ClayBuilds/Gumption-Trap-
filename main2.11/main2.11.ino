//Clay McPherson
//7-8-2023

//GUMPTION TRAP MAIN CODE
//This code written for custom PCB v1.2
//Compatible with most arduino microcontrollers, custom pcb not required. Change pinouts in "pindefinitions.h"

//Code Version 2.11

//changes from v2.10:
/*
  -change to more discrete PWM control with writeMicroseconds() rather than controlling throttle with a virtual servo in degrees. this will future proof the system for ESC hardware agnosticism 
  -implement ramping pwm up/down instead of instantaneous movement, see adjustpwm() function
*/

//TESTED and:
/*
  -passes all bench tests
  -pwmrate seems pretty slow, but I'd rather lean towards the slow side for now. 
  -great success on the lake, 2 hour mission worked nicely. Steering gain needs to go up a little. 
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
  
  //make sure SD card is good
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
  if(!mag.begin())              
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
  port.attach(pmot,pwmlow,pwmhigh);
  starboard.attach(smot,pwmlow,pwmhigh);

  port.write(pwmlow);          //set throttles to zero to make sure ESC's will start up.
  starboard.write(pwmlow);
  
  //setup power measurement chips (INA260)
  motpow.begin(0x41);   //note: one module needs a solder jumper so that they have different I2C addresses
  solpow.begin(0x40);
  
  smartDelay(5000); 
  Serial.println("setup over");
}

void loop() 
{
  switchval = readSwitch(swt, false);  //check the mode toggle switch. if out of radio range, default to auto
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
