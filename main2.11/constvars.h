//This file for constant variables or parameters used across multiple areas of the code or for configuration purposes

#include "pindefinitions.h"
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <Adafruit_LIS2MDL.h>
#include <Adafruit_INA260.h>
#include <ping1d.h>

#ifndef CONST_VARS_h
#define CONST_VARS_h



const float Pi = 3.15159;


//SD card stuff
File coords;
File blackbox;
File depthlog;
File errorlog;
int bblast = 0;       //millis() of previous black box recording
int bbint = 1;       //seconds between black box recordings
int depthlast = 0;      //millis() of previous depth recording
int depthint = 30;      //seconds between depth measurements
bool cardfailed;
char cardcontents[25];
int cardsize;
byte i = 0;           //indexes for nested loops that read coordinate arrays
byte j = 0;
byte k = 1;
byte n;
const byte maxcoords = 25;    //maximum allowable number of gps coordinate pairs in mission. Helps save RAM

//GPS stuff
TinyGPSPlus gps;
float currentLat;
float currentLong;
float goalLat = 39.03385;
float goalLong = 125.75432;
float Carray [2][maxcoords];        //array of latitude and longitude pairs (row 0 lat row 1 long, column 0 only contains the length)
byte ncoords = maxcoords;                         //number of coordinate pairs
double goalheading;
double hdiff;
byte waypoint = 1;
double d = 100;

//Drive control stuff
Servo port;
Servo starboard;
int portval;        // actual pwm values in microseconds to feed ESCs
int starbval;
int goalport;       //goal pwm values for gradual adjustment
int goalstarb;    
int switchval = 0;  //1 switch flipped 0 switch not flipped. 1 is manual control mode.
bool autostate = true;
int throtval = 0;
int steerval = 0;
const float Tm = 0.3;         //throttle multiplier (0-1). Limits max throttle to x%. leave at 1 for no limiting, this is intended to save power for solar operation. 
const float pwmhigh = 2000;   //pwm range values for installed ESCs. virtually always 1000-2000 for typical RC or drone parts. 
const float pwmlow = 1000;
const float sgain = 2;        //steering gain. at a value of 1, port motor will be zero when 90 degrees off to the right. at a value of 2, port will be zero at 45 degrees off to the right. etc. 
const int pwmrate = 5;      //microseconds of pwm adjustment per 10 miliseconds. for example, a value of 1 would take 10 seconds to go from a pwm of 1000us to 2000us. a value of 5 would take 2 seconds.
unsigned long tlastp = 0;     //time in ms since last pwm adjustment
unsigned long tlasts = 0;
int manhigh; //highest pwm value allowed in manual mode based on throttle limiting and also the physical throttle stick
int ahigh = pwmlow+((pwmhigh-pwmlow)*Tm);  //highest pwm value allowed in auto mode based on throttle limiting


//Magnetometer stuff
Adafruit_LIS2MDL mag = Adafruit_LIS2MDL(12345); 
bool magerr;
float currentheading;
const float xoff = -19.87;        //from magnetometer calibration
const float yoff = -21.22;
const float declination = 1.95;    //from east texas 2022

//Power measurement stuff (INA260)
Adafruit_INA260 motpow = Adafruit_INA260();
Adafruit_INA260 solpow = Adafruit_INA260();
double motI = 0;  //mA
double solI = 0;
double motV = 0;  //mV
double solV = 0;
const double motIlimit = 5000; //mA at which forced throttle down should occur

//depth sounder stuff
Ping1D ping { Serial2 };
int depth = 0;

//error code stuff
int laste2 = 0;
int laste3 = 0;
int laste6 = 0;
int laste7 = 0;
int lastgoodhead = 0;

#endif
