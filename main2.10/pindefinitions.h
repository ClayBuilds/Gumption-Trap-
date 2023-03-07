//This file includes all necessary pin definitions as wired on pcb 
//note: LED_BUILTIN can't be used cause pin 13 is SCK

#ifndef PIN_DEFINITIONS_h
#define PIN_DEFINITIONS_h

const byte gpsrx = 1;   //don't think I actually need rx/tx since I'm not using software serial anymore
const byte gpstx = 0;
const byte smot = 3;
const byte pmot = 4;
const byte throt = 20;
const byte steer = 16;
const byte swt = 17;
const byte cs = 10;
const byte mosi = 11;
const byte miso = 12;
const byte sck = 13;
const byte ping_arduinorx = 7; //don't think I actually need rx/tx since I'm not using software serial anymore
const byte ping_arduinotx = 8;

#endif
