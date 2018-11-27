//mobile.h
#include "systemc.h"

SC_MODULE (mobile) {
  sc_in<bool> clock;

  static sc_event ev_image_to_mobile; //indicates an image was sent to a mobile

  int current_display_image[50][50];

  void tx(); //X (used to send gaze data)
  void rx(); //used to receive images

 public:
  //an image transmission from given mobile to the server
  static void receive_image(int mobile_index, int image[][]);
}
