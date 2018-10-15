//controller.h
//Controller ~ control unit module for simple RISC CPU
#include "systemc.h"

SC_MODULE(controller) {
  sc_in <bool> clock;
  sc_in <bool> z_flag;
  sc_in <bool> n_flag;
  sc_in <bool> c_flag;
  sc_in <bool> l_flag;

  SC_HAS_PROCESS(controller);

 controller(sc_module_name name) : sc_module(name) {
    SC_METHOD(prc_if);
    sensitive << clock.pos();
    SC_METHOD(prc_rd);
    sensitive << clock.pos();
    SC_METHOD(prc_exe);
    sensitive << clock.pos();
    SC_METHOD(prc_mem);
    sensitive << clock.pos();
    SC_METHOD(prc_wb);
    sensitive << clock.neg();
  }
}
