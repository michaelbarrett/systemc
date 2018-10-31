//server.h
#include "systemc.h"
SC_MODULE (server) {
  sc_in<bool> clock;
  sc_in<int> message;

  //event
  static sc_event ev_env; //signifies message from environment was received

  int i = 1;

  void prc();

 public:
  static void message_from_env(int m);

  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
    //sensitive << clock.pos();
  }
};
