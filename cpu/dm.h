//dm.h
//DM ~ Data Memory module ~ similar (same?) to program memory module
#include "systemc.h"

const int MEM_SIZE_DM = 256;

SC_MODULE(data_memory) {
  sc_in <int> d_in; //data input
  sc_in <int> addr; //address
  sc_in <bool> en, rw, clock; //enable, read/write, clock
  sc_out <int> d_out; //data output
  int* _data; //local variable

  void prc();
  
  SC_HAS_PROCESS(data_memory);
  
 data_memory(sc_module_name name, int* data) : sc_module(name),  _data(data) {
    SC_METHOD(prc);
    sensitive << clock.pos(); //sequential?
  }
};
