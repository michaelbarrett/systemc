//rf.h
//RF ~ Register File module
#include "systemc.h"

//a reg file is like a DM with 2 inputs and 2 outputs

SC_MODULE(register_file) {
  sc_in <int> addr1, addr2; //write: use addr1, read: address for Rdest and Rsrc
  sc_in <bool> en, rw, clock;
  sc_in <int> d_in; //data input
  sc_out <int> d_out1, d_out2; //data output for Rdest and Rsrc
  int* _data;

  SC_HAS_PROCESS(register_file);
  SC_HAS_PROCESS(prc);

 register_file(sc_module_name name, int* data) : sc_module(name), _data(data) {
    SC_METHOD(prc);
    sensitive << clock.pos();
  }
}

