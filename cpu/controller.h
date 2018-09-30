//controller.h
//Controller ~ control unit module for simple RISC CPU
#include "systemc.h"

SC_MODULE(controller) {
  sc_in <bool> z_flag;
  sc_in <bool> n_flag;
  sc_in <bool> c_flag;
  sc_in <bool> l_flag;

  SC_HAS_PROCESS(prc_pipeline);
}
