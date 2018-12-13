//server.cpp
#include "server.h"
#include "mobile.h"

bool server :: free = true;

sc_event server :: ev_network_request;
sc_event server :: ev_receive;
sc_event server :: ev_transmit;

int server :: image_size[2] = {IMAGE_SIZE_X, IMAGE_SIZE_Y}; //xsize, ysize
//{{MAXx, MAXy}, {P1x, P1y, P2x, P2y}, [...ROI]}, {...}
int server :: image_set[PACKETS_PER_IMAGE * IMAGE_AMOUNT][PACKET_ARRAY_LENGTH] =
  //image = 1K * 1k * 8bits = 8MB per image
  //takes 8 seconds to send image from S -> M, the bandwidth is 1MB/s  
  //each image has a "display start time" -- 12:00, 12:01, 12:02, etc
  //~~ images ~~
  //first image: image_set[0] - [4]
  {{50, 20, 400, 320}, //first ROI -- each element is one ROI, = 1 packet of info
   {50, 370, 450, 1000},
   {470, 20, 600, 900},
   {670, 40, 950, 550},
   {680, 700, 1000, 1000},
   //second image: image_set[5] - [9]
   {40, 10, 390, 900},
   {40, 360, 440, 990},
   {460, 10, 590, 890},
   {660, 30, 940, 540},
   {670, 690, 990, 990},
   //third image: image_set[10] - [14]
   {30, 0, 380, 890},
   {30, 350, 430, 980},
   {450, 0, 580, 880},
   {650, 20, 930, 550},
   {660, 680, 980, 980},
   //fourth image: image_set[15] - [19]
   {40, 10, 390, 900},
   {40, 360, 440, 990},
   {460, 10, 590, 890},
   {660, 30, 940, 540},
   {670, 690, 990, 990},
   //fifth image: image_set[20] - [24]
   {50, 20, 400, 320},
   {50, 370, 450, 1000},
   {470, 20, 600, 900},
   {670, 40, 950, 550},
   {680, 700, 1000, 1000}};
int server :: packets_received[MAX_GAZE_PACKET_AMT][MAX_GAZE_PACKET_SIZE][3];

//server transmitter -- sends image data
void server :: prc_tx() {
  int i = 0;
  while(true) {
    //transmit -- we are busy
    free = false;
    cout << "SERVER: Sending image packet " << i << " to mobile 0" << endl;
    mobile::receive_image_packet(0, image_set[i]); //mobile receives pointer packet
    wait(1600, SC_MS); //it takes 8 seconds to send an image, 1.6 for one packet of 5

    //now, receive -- we are now free
    free = true;
    cout << "SERVER: Free, receiving images" << endl;
    ev_receive.notify(); //trigger receiver actions
    //wait for "transmit" event when reception is finished
    wait(ev_transmit);

    i += 1; //point i to next packet
    wait();
  }
}

//server receiver -- receives gaze data
void server :: prc_rx() {
  while(true) {
    wait(ev_receive);
    //receive
    //wait(ev_network_request);
    cout << "SERVER: Receiving; waiting for request to use the network." << endl;
    wait(sc_time(1000, SC_NS), ev_network_request); //window time specified here
    //notify transmit
    ev_transmit.notify();
    wait();
  }
}

//gets the free status of the server
bool server :: is_free() {
  return free;
}

//a request from a mobile to use the server (1: gaze data)
void server :: receive_tuple_packet(int mobile_index,
				    int packet_num,
				    int tuple_num, int tuple[3]) {
  cout << "SERVER.RECEIVE_MESSAGE: A request was sent to server from mobile "
       << mobile_index << "." << endl;
  cout << "Mobile " << mobile_index << " is sending gaze data." << endl;
  packets_received[packet_num][tuple_num][0] = tuple[0];
  packets_received[packet_num][tuple_num][1] = tuple[1];
  packets_received[packet_num][tuple_num][2] = tuple[2];  
  ev_network_request.notify();
}
