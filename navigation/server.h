//server.h
#include "systemc.h"
SC_MODULE (server) {
  sc_in<bool> clock;
  int message;

  void prc();

 public:
  static void message_from_env(int m);
  
  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
  }
};
