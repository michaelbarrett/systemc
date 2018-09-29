//=================================
// Function: Half Adder
// File Name: half_adder.h
//=================================
#include "systemc.h"

SC_MODULE (half_adder) {
  sc_in <sc_bit> a;
  sc_in <sc_bit> b;
  sc_out <sc_bit> sum;
  sc_out <sc_bit> carry;

  //----------------Internal Variables-----------------

  //----------------Methods-----------------
  void prc_half_adder(); //defined in cpp file

  //----------------Constructor-----------------
  SC_CTOR(half_adder) {
    SC_METHOD (prc_half_adder);
    sensitive << a << b;
  }
};
