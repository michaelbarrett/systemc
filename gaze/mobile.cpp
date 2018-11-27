//mobile.cpp
#include "server.h"
#include "mobile.h"

sc_event mobile :: ev_image_to_mobile; //indicates an image was sent to a mobile

int mobile :: current_display_image[50][50];

//mobile receiver -- receives images
void mobile :: prc_rx() {
  while(true) {
    wait(ev_image_to_mobile);  //wait until an image is sent to mobile
    cout << "MOBILE: An image was sent to mobile." << endl;
    cout << "MOBILE: The image size = " << sizeof(current_display_image) << endl;
    if (server::is_free) {
      //ACTIONS
      //send "can I use the network" (network_request)
      //server says yes or no
      //if no, wait a random time (wait(random))
      //if yes, send from server when network signal goes high (signal = data ready)
    }
    
    wait();
  }
}

//mobile transmitter -- sends gaze data
void mobile :: prc_tx() {
  while(true) {
    
    wait();
  }
}

//an image transmission from the server
void mobile :: receive_image(int mobile_index, int image[][50]) {
  //current_display_image = image;
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      current_display_image[i][j] = image[i][j];
    }
  }
  ev_image_to_mobile.notify();
}
