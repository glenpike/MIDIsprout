#ifndef __MIDIserial_h__
#define __MIDIserial_h__

#include <Arduino.h>
#include "globals.h"
#include <LEDFader.h>

extern unsigned long currentMillis;
extern byte noteLEDs;
extern LEDFader leds[];
extern byte channel;
extern byte QY8;

const byte polyphony = 5; //above 8 notes may run out of ram



extern byte controlVoltage; //output PWM CV on controlLED, pin 17, PB3, digital 11 *lowpass filter
extern byte controlLED; //array index of control LED (CV out)


typedef struct _MIDImessage { //build structure for Note and Control MIDImessages
  unsigned int type;
  int value;
  int velocity;
  long duration;
  long period;
  int channel;
}
MIDImessage;
extern MIDImessage noteArray[polyphony]; //manage MIDImessage data as an array with size polyphony
extern int noteIndex;
extern MIDImessage controlMessage; //manage MIDImessage data for Control Message (CV out)

void setNote(int value, int velocity, long duration, int notechannel);
void setControl(int type, int value, int velocity, long duration);
void checkControl();
void checkNote();
void MIDIpanic();
void midiSerial(int type, int channel, int data1, int data2);

#endif
