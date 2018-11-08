//robot.h
#include "systemc.h"
SC_MODULE (robot) {
  sc_in<bool> clock;

  void prc();

  SC_HAS_PROCESS(robot);

 robot(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc);
    sensitive << clock.pos();
  }
};
