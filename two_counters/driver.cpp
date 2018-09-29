//driver.cpp
#include "driver.h"

void driver :: prc_driver() {
  d_in1 = 14;
  d_in2 = 5;
  d_in3 = 3;
  wait(5, SC_NS);
  d_load1 = true;
  d_load2 = true;
  d_dec1 = true;
  d_dec2 = false;
  //they should be loaded
  wait(5, SC_NS);
  d_load1 = false;
  d_load2 = false;
  d_dec1 = true;
  d_dec2 = false;
  //now in1 should start decreasing by 1 until it reaches 5
  wait(60, SC_NS);
  d_in1 = 3;
  d_in2 = 15;
  wait(5, SC_NS);
  d_load1 = true;
  d_load2 = true;
  d_dec1 = true;
  d_dec2 = false;
  //they should be reloaded
  wait(5, SC_NS);
  d_load1 = false;
  d_load2 = false;
  d_dec1 = false;
  d_dec2 = true;
  //now in2 should start decreasing by 3, thus: 15, 12, 9, 6, 3
  wait(50, SC_NS);
  d_in1 = 5;
  d_in2 = 7;
  wait(5, SC_NS);
  d_load1 = true;
  d_load2 = true;
  d_dec1 = true;
  d_dec2 = false;
  //they should be reloaded
  wait(5, SC_NS);
  d_load1 = false;
  d_load2 = false;
  d_dec1 = false;
  d_dec2 = true;
  //now in2 should start decreasing by 3, thus: 7, 4, 1, -2 (overflow)
  wait(40, SC_NS);

}
