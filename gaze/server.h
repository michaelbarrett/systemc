//server.h
#include "systemc.h"

SC_MODULE (server) {
  sc_in<bool> clock;

  static bool free; //signifies whether server is free to be used

  static sc_event ev_network_request; //a request from a mobile to use the network

  //{{MAXx, MAXy}, {P1x, P1y, P2x, P2y}, [...ROI]}, {...}
  static int image_set[50][50][50];

  static void tx(); //used to send images
  static void rx(); //X (used to receive gaze data)

  static bool is_free(); //getter

 public:
  static void receive_message(int mobile_index, int message); //a request from a mobile to use the network
}
