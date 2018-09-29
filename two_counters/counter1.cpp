//counter1.cpp
#include "counter1.h"

void counter1 :: prc_counter1() {
  if (load1) { //loading
    count = in1.read();
    tempCount = count; //tempCount gets the old value of count (before the load)
  }
  else if (hold) {} //holding (do nothing)
  else if (dec1) { //decrementing
    tempCount = count;
    count--;
  }
  //output
  count1.write(count);

  //compare count & tempcount to see if overflow
  if ((!load1) & (count > tempCount)) {
    overflow1.write(true);
  }
}
