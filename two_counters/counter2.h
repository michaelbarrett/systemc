//counter2.h
//is loaded from in2[7:0] when load2 is high, and decremented by in3[7:0]
//when dec2 is high. The internal and output count is held when hold is high
#include "systemc.h"

SC_MODULE(counter2) {
  sc_in <sc_uint<8> > in2, in3;
  sc_in <bool> clock, load2, dec2, hold;

  sc_out <sc_uint<8> > count2;
  sc_out <bool> overflow2;

  //internal variables
  sc_uint<8> count, tempCount;

  //fun decl
  void prc_counter2();

  SC_CTOR(counter2) {
    SC_METHOD(prc_counter2);
    sensitive << clock.pos();
  }
};
