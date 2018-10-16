//controller.h
//Controller ~ control unit module for simple RISC CPU
#include "systemc.h"

SC_MODULE(controller) {
  sc_in <bool> clock;
  sc_in <bool> z_flag;
  sc_in <bool> n_flag;
  sc_in <bool> c_flag;
  sc_in <bool> l_flag;

  //to and from PM
  sc_in <int> instr_from_pm;
  sc_out <int> addr_to_pm;

  int ir = 0; //instruction register (init = 0)
  int pc = 0; //program counter (init = 0)

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
