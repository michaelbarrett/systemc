//mobile.cpp
#include "systemc.h"

//mobile receiver -- receives images
void mobile :: prc_rx() {
  while(true) {
    if (server_is_free) {
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
