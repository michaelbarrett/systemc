//counter2.cpp
#include "counter2.h"

void counter2 :: prc_counter2() {
  if (load2) { //loading
    count = in2.read();
    tempCount = count; //tempCount gets the old value of count (before the load)
  }
  else if (hold) {} //holding (do nothing)
  else if (dec2) { //decrementing
    tempCount = count;
    count = count - in3.read();
  }
  //output
  count2.write(count);

  //compare count & tempcount to see if overflow
  if ((!load2) & (count > tempCount)) {
    overflow2.write(true);
  }
}

