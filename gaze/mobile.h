//mobile.h
#include "systemc.h"

SC_MODULE (mobile) {
  sc_in<bool> clock;

  bool free;
  bool server_is_free;

  int current_display_image[50][50];

  void tx();
  void rx(); //used to receive images

 public:
  void receive_image(int image[][]);
}
