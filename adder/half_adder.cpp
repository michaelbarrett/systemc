//=================================
// Function: Half Adder
// File Name: half_adder.cpp
//=================================
#include "half_adder.h"

//concurrent method prc_half_adder of the half adder
void half_adder :: prc_half_adder() { 
  sum = a ^ b;
  carry = a & b;
}
