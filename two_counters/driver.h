//driver.h
#include "systemc.h"

SC_MODULE(driver) {
  sc_out <sc_uint<8> > d_in1, d_in2, d_in3;
  sc_out <bool> d_load1, d_load2, d_dec1, d_dec2;

  void prc_driver();

  SC_CTOR(driver) {
    SC_THREAD(prc_driver);
  }
};
