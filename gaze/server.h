//server.h
#include "constants.h"
#include "systemc.h"

SC_MODULE (server) {
  sc_in<bool> clock;

  static bool free; //signifies whether server is free to be used

  static sc_event ev_network_request; //a request from a mobile to use the network
  static sc_event ev_receive; //internal event
  static sc_event ev_transmit; //internal event

  static int image_size[2]; //xsize, ysize
  //{{MAXx, MAXy}, {P1x, P1y, P2x, P2y}, [...ROI]}, {...}
  static int image_set[PACKETS_PER_IMAGE * IMAGE_AMOUNT][PACKET_ARRAY_LENGTH];
  static int packets_received[MAX_GAZE_PACKET_AMT][MAX_GAZE_PACKET_SIZE][3];

  void prc_tx(); //used to send images
  void prc_rx(); //X (used to receive gaze data)

  static bool is_free(); //getter

 public:
  //a request from a mobile to use the network
  static void receive_tuple_packet(int mobile_index,
				   int packet_num, int tuple_num, int tuple[3]);

  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc_tx);
    sensitive << clock.pos();
    SC_THREAD(prc_rx);
    sensitive << clock.pos();
  }
};
