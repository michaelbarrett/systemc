//mobile.h
#include "systemc.h"
#include <vector>
#include <tuple>

using std::vector;
using std::tuple;

SC_MODULE (mobile) {
  sc_in<bool> clock;

  static sc_event ev_image_to_mobile; //indicates an image was sent to a mobile

  static int m0_display_image_buffer[PACKETS_PER_IMAGE * IMAGE_AMOUNT][PACKET_ARRAY_LENGTH];
  static int m1_display_image_buffer[PACKETS_PER_IMAGE * IMAGE_AMOUNT][PACKET_ARRAY_LENGTH];
  static int m0_image_packet_index;
  static int m1_image_packet_index;
  static int frame;
  static int gaze_point[2]; //{x, y}
  static int m0_packet[MAX_GAZE_PACKET_SIZE][3];

  void ufo(); //used for gaze movement & as a transmitter to send gaze data
  void prc_rx(); //used to receive images

 public:
  //an image transmission from given mobile to the server
  static void receive_image_packet(int mobile_index, int image[3]);
  static void percolate_new_image(int mobile_index);

  SC_HAS_PROCESS(mobile);

 mobile(sc_module_name name) : sc_module(name) {
    SC_THREAD(ufo);
    sensitive << clock.pos();
    SC_THREAD(prc_rx);
    sensitive << clock.pos();
  }
};
