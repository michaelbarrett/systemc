//counter1.h
//is loaded from in1[7:0] when load1 is high, and decrememted by 1 when dec1 is high
//the internal and output count is held when hold is high
#include "systemc.h"

SC_MODULE(counter1) {
  sc_in <sc_uint<8> > in1;
  sc_in <bool> clock, load1, dec1, hold;

  sc_out <sc_uint<8> > count1;
  sc_out <bool> overflow1;

  //internal variables
  sc_uint<8> count, tempCount;

  //fun decl
  void prc_counter1();
  
  SC_CTOR(counter1) {
    SC_METHOD(prc_counter1);
    sensitive << clock.pos();
  }
};
