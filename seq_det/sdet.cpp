//Sequence Detector
//sdet.cpp
#include "sdet.h"

void sdet :: prc_sdet() {
  if (reset) {
    first = data.read();
    second = first.read();
    third = second.read();
    fourth = third.read();
  }
  else { //reset, active low
    first = false;
    second = false;
    third = false;
    fourth = false;
  }
}

void sdet :: prc_output() {
  if (!clear) {
    seq_found.write( fourth & (!third) & second & first); //1011 detection -- fourth is the oldest value, first is the newest
  }
  else { //clear, active high
    seq_found.write(false);
  }
}
