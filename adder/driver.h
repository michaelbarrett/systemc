
// Driver
// driver.h

#include "systemc.h"

SC_MODULE (driver) {
  sc_out <sc_logic> d_a, d_b, c_cin; //the outputs, there is no input

  //----------------Internal Variables-----------------

  //----------------Methods-----------------
  void prc_driver(); //driver thread

  //----------------Constructor-----------------
  SC_CTOR(driver) {
    SC_THREAD (prc_driver); //thread - runs once at the beginning
  }
};
