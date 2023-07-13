//This file includes all necessary pin definitions as wired on pcb 
//note: LED_BUILTIN can't be used cause pin 13 is SCK

#ifndef PIN_DEFINITIONS_h
#define PIN_DEFINITIONS_h

const byte gpsrx = 1;   //don't think I actually need rx/tx since I'm not using software serial anymore. These are the serial pins for the GPS module
const byte gpstx = 0;
const byte smot = 3;    //starboard motor PWM signal to ESC
const byte pmot = 4;    //port motor PWM signal to ESC
const byte throt = 20;  //Throttle PWM signal coming from radio receiver in manual mode
const byte steer = 16;  //Steering PWM signal coming from radio receiver in manual mode
const byte swt = 17;    //auxiliary switch signal coming from radio receiver. toggles between auto/manual modes.
const byte cs = 10;     //chip select for SD card
const byte mosi = 11;   // other SPI pins 
const byte miso = 12;
const byte sck = 13;
const byte ping_arduinorx = 7; //don't think I actually need rx/tx since I'm not using software serial anymore. These are serial pins for the sonar module. 
const byte ping_arduinotx = 8;

#endif
