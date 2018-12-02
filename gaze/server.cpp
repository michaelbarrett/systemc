//server.cpp
#include "server.h"
#include "mobile.h"

bool server :: free = true;

sc_event server :: ev_network_request;

//{{MAXx, MAXy}, {P1x, P1y, P2x, P2y}, [...ROI]}, {...}
int server :: image_set[50][50][50] =
  {{{1023, 1023}, //first image
    {50, 20, 400, 320}, //first ROI -- each element is one ROI
    {50, 370, 450, 1000},
    {470, 20, 600, 900},
    {670, 40, 950, 550},
    {680, 700, 1000, 1000}
    },
   {{1023, 1023}, //second image
    {40, 10, 390, 900},
    {40, 360, 440, 990},
    {460, 10, 590, 890},
    {660, 30, 940, 540},
    {670, 690, 990, 990}
   },
   {{1023, 1023}, //third image
    {30, 0, 380, 890},
    {30, 350, 430, 980},
    {450, 0, 580, 880},
    {650, 20, 930, 550},
    {660, 680, 980, 980}
   }};

//server transmitter -- sends image data
void server :: prc_tx() {
  while(true) {
    //transmit -- we are busy
    free = false;
    cout << "SERVER: Sending image to mobile 0" << endl;
    mobile::receive_image(0, image_set[0]); //mobile receives first image
    cout << "SERVER: Sending image to mobile 1" << endl;
    mobile::receive_image(1, image_set[1]);
    //now, receive -- we are now free
    free = true;
    ev_receive.notify();
    //wait for "transmit" event when reception is finished
    wait(ev_transmit);
  }
}

//server receiver -- receives gaze data
void server :: prc_rx() {
  while(true) {
    wait(ev_receive);
    //receive
    //wait(ev_network_request);
    cout << "SERVER: Receiving now." << endl;
    //notify transmit
    ev_transmit.notify();
  }
}

//gets the free status of the server
bool server :: is_free() {
  return free;
}

//a request from a mobile to use the server (1: i want to get image data)
void server :: receive_message(int mobile_index, int message) {
  
}
