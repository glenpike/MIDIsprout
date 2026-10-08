#ifndef __Peripherals_h__
#define __Peripherals_h__

#include <Arduino.h>
#include "globals.h"

extern unsigned long currentMillis;
extern const byte knobPin;
extern LEDFader leds[];
extern byte noteLEDs;

extern unsigned long batteryCheck; //battery check delay timer
extern long batteryLimit; //voltage check minimum, 3.0~2.7V under load; causes lightshow to turn off (save power)
extern byte checkBat;

extern float threshMin; //scaling threshold min
extern float threshMax; //scaling threshold max
extern float knobMin;
extern float knobMax;

void checkKnob();

void knobMode();

void rampUp(int ledPin, int value, int time);

void rampDown(int ledPin, int value, int time);

void checkLED();

void checkButton();

long readVcc();
void checkBattery();

void bootLightshow();

//provide float map function
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);

//debug SRAM memory size
int freeRAM();// print free RAM at any point

#endif
