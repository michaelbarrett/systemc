//robot.h
#include "systemc.h"
SC_MODULE (robot) {
  sc_in<int> message_i;
  sc_out<int> message_o;

  void prc();

  SC_HAS_PROCESS(robot);

 robot(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
  }
};
