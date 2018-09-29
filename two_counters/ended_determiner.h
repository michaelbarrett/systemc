//ended_determiner.h
//contains methods determining 'ended' and 'hold' values
#include "systemc.h"

SC_MODULE(ended_determiner) {
  //ports for ended determiner
  sc_in <sc_uint<8> > ed_count1, ed_count2;
  sc_in <bool> ed_overflow1, ed_overflow2;
  sc_out <bool> ended;

  //ports for hold determiner
  sc_in <bool> load1, load2;
  sc_out <bool> hold;

  //fun decl
  void prc_ended_determiner();
  void prc_hold_determiner();

  SC_CTOR(ended_determiner) {
    SC_METHOD(prc_ended_determiner);
    sensitive << ed_count1 << ed_count2 << ed_overflow1 << ed_overflow2;
    SC_METHOD(prc_hold_determiner);
    sensitive << ended << load1 << load2;
  }
};
