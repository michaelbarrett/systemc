//mobile.h
#include "systemc.h"

SC_MODULE (mobile) {
  sc_in<bool> clock;

  static sc_event ev_image_to_mobile; //indicates an image was sent to a mobile

  static int current_display_image[50][50];

  void prc_tx(); //X (used to send gaze data)
  void prc_rx(); //used to receive images

 public:
  //an image transmission from given mobile to the server
  static void receive_image(int mobile_index, int image[50][50]);

  SC_HAS_PROCESS(mobile);

 mobile(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc_tx);
    sensitive << clock.pos();
    SC_THREAD(prc_rx);
    sensitive << clock.pos();
  }
};
