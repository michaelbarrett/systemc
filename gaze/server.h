//server.h
#include "systemc.h"

SC_MODULE (server) {
  sc_in<bool> clock;

  bool free;

  int image_max_x = 1023;
  int image_max_y = 1023;
  int image_set[50][50] //format: {{P1x, P1y, P2x, P2y}, {P1x, P1y, P2x, P2y}, ...}
    = {{50, 20, 400, 320}, //first ROI
       {50, 370, 450, 1000},
       {470, 20, 600, 900},
       {670, 40, 950, 550},
       {680, 700, 1000, 1000}
  };

  void tx(); //used to transmit images
  void rx();

 public:
  void receive_message(int mobile_index, int message); //network_request from mobile
}
