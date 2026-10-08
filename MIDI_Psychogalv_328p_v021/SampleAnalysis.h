#ifndef __SampleAnalysis_h__
#define __SampleAnalysis_h__

#include <Arduino.h>
#include "globals.h"

extern const byte samplesize;
extern int *scaleSelect;
extern byte QY8;

extern volatile unsigned long microseconds; //sampling timer
extern volatile byte index;
extern volatile unsigned long samples[];

const byte analysize = samplesize - 1;  //trim for analysis array
extern byte controlNumber; //set to mappable control, low values may interfere with other soft synth controls!!

extern int noteMin; //C2  - keyboard note minimum
extern int noteMax; //C7  - keyboard note maximum
extern int root; //initialize for root

void sample();
void analyzeSample();

#endif
