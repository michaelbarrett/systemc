//dm.h
//DM ~ Data Memory module ~ similar (same?) to program memory module
#include "systemc.h"

//memory size variable & checks?
//should PM use the same module?
//is an int a word? is that ok to use for words without checks?
//how do we check the size of the initial data input?
//does _data have a word size?

// is RF the same as memory but with two inputs and two outputs? other differences?

const int WORD_SIZE = 16;
const int ADDR_SIZE = 8;
const int MEM_SIZE = 256;

SC_MODULE(data_memory) {
  sc_in <int> d_in; //data input
  sc_in <int> addr; //address
  sc_in <bool> en, rw, clock; //enable, read/write, clock
  sc_out <int> d_out; //data output
  int* _data; //local variable

  SC_HAS_PROCESS(data_memory);
  SC_HAS_PROCESS(prc);

 data_memory(sc_module_name name, int* data) : sc_module(name),  _data(data) {
    SC_METHOD(prc);
    sensitive << clock.pos(); //sequential?
  }
}
