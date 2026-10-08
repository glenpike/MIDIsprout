
/*------------
MIDI_PsychoGalvanometer v021
Accepts pulse inputs from a Galvanic Conductance sensor
consisting of a 555 timer set as an astablemultivibrator and two electrodes.
Through sampling pulse widths and identifying fluctuations, MIDI note and control messages
are generated.  Features include Threshold, Scaling, Control Number, and Control Voltage
using PWM through an RC Low Pass filter.
MIDIsprout.com
-------------*/
#include <LEDFader.h> //manage LEDs without delay() jgillick/arduino-LEDFader https://github.com/jgillick/arduino-LEDFader.git
#include "globals.h"
#include "Peripherals.h"
#include "MIDIserial.h"
#include "SampleAnalysis.h"

//******************************
//set scaled values, sorted array, first element scale length
int scaleMajor[]  = {7,1, 3, 5, 6, 8, 10, 12};
int scaleDiaMinor[]  = {7,1, 3, 4, 6, 8, 9, 11};
int scaleIndian[]  = {7,1, 2, 2, 5, 6, 9, 11};
int scaleMinor[]  = {7,1, 3, 4, 6, 8, 9, 11};
int scaleChrom[] = {12,1,2,3,4,5,6,7,8,9,10,11,12};
int *scaleSelect = scaleChrom; //initialize scaling
// int root = 0; //initialize for root
//*******************************

const byte interruptPin = INT0; //galvanometer input
const byte knobPin = A0; //knob analog input

byte channel = 1;
byte QY8= 0;  //sends each note out chan 1-4, for use with General MIDI like Yamaha QY8 sequencer

const byte samplesize = 10; //set sample array size

volatile unsigned long microseconds; //sampling timer
volatile byte index = 0;
volatile unsigned long samples[samplesize];

unsigned long previousMillis = 0;
unsigned long currentMillis = 1;


LEDFader leds[LED_NUM] = { // 6 LEDs (perhaps 2 RGB LEDs)
  LEDFader(3),
  LEDFader(5),
  LEDFader(6),
  LEDFader(9),
  LEDFader(10),
  LEDFader(11)  //Control Voltage output or controlLED
};
int ledNums[LED_NUM] = {3,5,6,9,10,11};

byte noteLEDs = 1;  //performs lightshow set at noteOn event


void setup()
{
  pinMode(knobPin, INPUT);
  randomSeed(analogRead(0)); //seed for QY8
  Serial.begin(31250);  //initialize at MIDI rate
  controlMessage.value = 0;  //begin CV at 0
  //MIDIpanic(); //dont panic, unless you are sure it is nessisary
  checkBattery(); // shut off lightshow if power is too low
  if(noteLEDs) bootLightshow(); //a light show to display on system boot
  attachInterrupt(interruptPin, sample, RISING);  //begin sampling from interrupt

}

void loop()
{
  currentMillis = millis();   //manage time
  checkBattery(); //on low power, shutoff lightShow, continue MIDI operation
  checkKnob(); //check knob value
  if(index >= samplesize)  { analyzeSample(); }  //if samples array full, also checked in analyzeSample(), call sample analysis
  checkNote();  //turn off expired notes
  checkControl();  //update control value
  //checkButton();  //not implemented in this build
  checkLED();  //LED management without delay()
  previousMillis = currentMillis;   //manage time
}





