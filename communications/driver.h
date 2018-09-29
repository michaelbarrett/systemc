//driver.h
#include "systemc.h"

SC_MODULE (driver) {
  sc_out <bool> d_reset, d_clear;
  sc_out <sc_bv<12> > d_in_data;

  void prc_driver();

  SC_CTOR(driver) {
    SC_THREAD(prc_driver);
  }
};
