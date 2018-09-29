//=================================
// Function: Driver
// File Name: driver.cpp
//=================================
#include "driver.h"

void driver :: prc_driver() {
  sc_uint<3> pattern; //3 bit wide int

  pattern = 0; //init 000
  while(1) {
    d_a = pattern[0];
    d_b = pattern[1];
    d_cin = pattern[2];
    wait (5, SC_NS);
    pattern++; //000, 001, 010, 011, ...
  }
}
