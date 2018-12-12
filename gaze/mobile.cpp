//mobile.cpp
#include "server.h"
#include "mobile.h"

sc_event mobile :: ev_image_to_mobile; //indicates an image was sent to a mobile

//current display image is [0] - [4]
int mobile :: m0_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m1_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m2_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m0_image_packet_index = 0; //fills up over time
int mobile :: m1_image_packet_index = 0;
int mobile :: m2_image_packet_index = 0;
//current gaze point
int mobile :: gaze_point[2] = {((IMAGE_SIZE_X / 2) - 1),
			       ((IMAGE_SIZE_Y / 2) - 1)}; //center of image

//mobile gaze UFO movement
void mobile :: ufo() {
  while(true) {
    
    wait();
  }
}

//mobile receiver -- receives images
void mobile :: prc_rx() {
  while(true) {
    wait(ev_image_to_mobile);  //wait until an image is sent to mobile
    cout << "MOBILE: The image size = 8 MB." << endl;
    cout << "MOBILE: The first ROI of the image is {" <<
      m1_display_image_buffer[0][0] << ", " << 
      m1_display_image_buffer[0][1] << ", " << 
      m1_display_image_buffer[0][2] << ", " << 
      m1_display_image_buffer[0][3] << "}" << endl;
    wait();
  }
}

//mobile transmitter -- sends gaze data
void mobile :: prc_tx() {
  while(true) {
    if (server::is_free) {
      //ACTIONS
      //send "can I use the network" (network_request)
      //server says yes or no
      //if no, wait a random time (wait(random))
      //if yes, send from server when network signal goes high (signal = data ready)
      server::receive_message(0, 1);
      server::receive_message(1, 1);	
    }
    wait();
  }
}

//receive an image packet from the server
void mobile :: receive_image_packet(int mobile_index, int image_packet[4]) {
  cout << "MOBILE.RECEIVE_IMAGE: An image packet was sent to mobile "
       << mobile_index << "." << endl;
  cout << "MOBILE.RECEIVE_IMAGE: Packet is " << image_packet[0] << ", " << image_packet[1] << ", " << image_packet[2] << ", " << image_packet[3] << endl;
  //copy image packet to display_image_buffer
  for (int i = 0; i < 50; i++) {
    m0_display_image_buffer[m0_image_packet_index][i] = image_packet[i];
  }
  m0_image_packet_index += 1;
  ev_image_to_mobile.notify();
}
