#include "scale.h"

int scaleSearch(int note, int scale[], int scaleSize) {
 for(byte i=1;i<=scaleSize;i++) {
  if(note == scale[i]) { return note; }
  else { if(note < scale[i]) { return scale[i]; } } //highest scale value less than or equal to note
  //otherwise continue search
 }
 //didn't find note and didn't pass note value, uh oh!
 return scale[scaleSize];// clamp it to the highest note
}


int scaleNote(int note, int scale[], int root) {
  //input note mod 12 for scaling, note/12 octave
  //search array for nearest note, return scaled*octave
  int scaled = note%12;
  int octave = note/12;
  int scaleSize = (scale[0]);
  //search entire array and return closest scaled note
  scaled = scaleSearch(scaled, scale, scaleSize);
  scaled = (scaled + (12 * octave)) + root; //apply octave and root
  return scaled;
}
