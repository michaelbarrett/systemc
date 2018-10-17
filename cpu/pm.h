//pm.h
//PM ~ Program Memory module
#include "systemc.h"

//there is no d_in, and no read/write input, since program memory is read only; data is passed in during initialization.

SC_MODULE(program_memory) {
  sc_in <int> addr; //address
  sc_in <bool> en, clock; //enable, clock
  sc_out <int> d_out; //data output
  int* _data; //local variable

  void prc();

  SC_HAS_PROCESS(program_memory);

 program_memory(sc_module_name name, int* data) : sc_module(name),  _data(data) {
    SC_METHOD(prc);
    sensitive << clock.pos(); //sequential?
  }
};
