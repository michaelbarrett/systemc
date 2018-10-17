//rf.h
//RF ~ Register File module
#include "systemc.h"

//a reg file is like a DM with 2 inputs and 2 outputs

//we are using 4-bit addressing, so we have registers $r0 to $r15
//$r0 is always zero
//$r1 is PC ~ program counter

SC_MODULE(register_file) {
  sc_in <int> addr1, addr2; //write: use addr1, read: address for Rdest and Rsrc
  sc_in <bool> en, rw, clock;
  sc_in <int> d_in; //data input
  sc_out <int> d_out1, d_out2; //data output for Rdest and Rsrc
  int* _data;

  void prc_read();
  void prc_write();
  
  SC_HAS_PROCESS(register_file);

 register_file(sc_module_name name, int* data) : sc_module(name), _data(data) {
    SC_METHOD(prc_read);
    sensitive << clock.pos();

    SC_METHOD(prc_write);
    sensitive << clock.neg();
  }
};
