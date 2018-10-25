//server.h
#include "systemc.h"
SC_MODULE () {
  sc_in<int> message;

  int i = 1;

  void prc();

  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
  }
};
