//server.h
#include "systemc.h"

SC_MODULE (server) {
  sc_in<bool> clock;

  static bool free; //signifies whether server is free to be used

  static sc_event ev_network_request; //a request from a mobile to use the network

  //{{MAXx, MAXy}, {P1x, P1y, P2x, P2y}, [...ROI]}, {...}
  static int image_set[50][50][50];

  void prc_tx(); //used to send images
  void prc_rx(); //X (used to receive gaze data)

  static bool is_free(); //getter

 public:
  static void receive_message(int mobile_index, int message); //a request from a mobile to use the network

  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc_tx);
    sensitive << clock.pos();
    SC_THREAD(prc_rx);
    sensitive << clock.pos();
  }
};
