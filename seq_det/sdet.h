//sdet.h
//Sequence Detector
//Output is '1' if 1011 is detected in input.
#include "systemc.h"

SC_MODULE(sdet) {
  //reset is active low, clears all internal registers.
  //clear is active high, clears output registers.
  sc_in <bool> clock, data, reset, clear;
  //seq_found is '1' if 1011 is detected in input sequence and '0' otherwise.
  sc_out <bool> seq_found;

  //----------------internal variables-----------------
 public: sc_signal <bool> first, second, third, fourth; // four internal registers

  //----------------methods-----------------
  void prc_sdet(); //synchronous part
  void prc_output(); //combinational part

  //----------------constructor-----------------
  SC_CTOR(sdet) {
    SC_METHOD(prc_sdet);
    sensitive << clock.pos() << reset;
    SC_METHOD(prc_output);
    sensitive << first << second << third << clear;
  }
};

