//mobile.cpp
#include "server.h"
#include "mobile.h"

sc_event mobile :: ev_image_to_mobile; //indicates an image was sent to a mobile

//current display image is [0] - [4]
int mobile :: m0_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m1_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m2_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m0_image_packet_index = 5; //fills up over time --
int mobile :: m1_image_packet_index = 5; //the displayed image is not directly
int mobile :: m2_image_packet_index = 5; //written to.
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
    cout << "MOBILE: FIRST IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[0][0] << ", " << 
      m0_display_image_buffer[0][1] << ", " << 
      m0_display_image_buffer[0][2] << ", " << 
      m0_display_image_buffer[0][3] << "}" << endl;
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[1][0] << ", " << 
      m0_display_image_buffer[1][1] << ", " << 
      m0_display_image_buffer[1][2] << ", " << 
      m0_display_image_buffer[1][3] << "}" << endl;
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[2][0] << ", " << 
      m0_display_image_buffer[2][1] << ", " << 
      m0_display_image_buffer[2][2] << ", " << 
      m0_display_image_buffer[2][3] << "}" << endl;
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[3][0] << ", " << 
      m0_display_image_buffer[3][1] << ", " << 
      m0_display_image_buffer[3][2] << ", " << 
      m0_display_image_buffer[3][3] << "}" << endl;
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[4][0] << ", " << 
      m0_display_image_buffer[4][1] << ", " << 
      m0_display_image_buffer[4][2] << ", " << 
      m0_display_image_buffer[4][3] << "}" << endl;
    cout << "MOBILE: SECOND IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[5][0] << ", " << 
      m0_display_image_buffer[5][1] << ", " << 
      m0_display_image_buffer[5][2] << ", " << 
      m0_display_image_buffer[5][3] << "}" << endl;
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[6][0] << ", " << 
      m0_display_image_buffer[6][1] << ", " << 
      m0_display_image_buffer[6][2] << ", " << 
      m0_display_image_buffer[6][3] << "}" << endl;
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[7][0] << ", " << 
      m0_display_image_buffer[7][1] << ", " << 
      m0_display_image_buffer[7][2] << ", " << 
      m0_display_image_buffer[7][3] << "}" << endl;
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[8][0] << ", " << 
      m0_display_image_buffer[8][1] << ", " << 
      m0_display_image_buffer[8][2] << ", " << 
      m0_display_image_buffer[8][3] << "}" << endl;
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[9][0] << ", " << 
      m0_display_image_buffer[9][1] << ", " << 
      m0_display_image_buffer[9][2] << ", " << 
      m0_display_image_buffer[9][3] << "}" << endl;            
    sc_time t = sc_time_stamp();
    cout << "MOBILE: TIME = " << t << endl;
    cout << "MOBILE: TVAL = " << t.value()/pow(10, 9) << endl; //time in ms as int
    /*if (t >= 120 && t <= 140) {
      percolate_new_image(0);
      }*/
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
  for (int i = 0; i < 4; i++) {
    m0_display_image_buffer[m0_image_packet_index][i] = image_packet[i];
    cout << "MRI LOOP: adding " << image_packet[i] << " to index " << i << endl;
  }
  cout << "MRI COPY TEST: m0_image_packet_index = " << m0_image_packet_index << endl;
  cout << "MRI COPY TEST: " << m0_display_image_buffer[m0_image_packet_index][0] <<
    " " << m0_display_image_buffer[m0_image_packet_index][1] <<
    " " << m0_display_image_buffer[m0_image_packet_index][2] <<
    " " << m0_display_image_buffer[m0_image_packet_index][3] << endl;
  m0_image_packet_index += 1;
  ev_image_to_mobile.notify();
}

//display new image and shift buffer
void mobile :: percolate_new_image(int mobile_index) {
  cout << "MOBILE: Displaying new image and shifting buffer" << endl;
  int m0_buffer_size = sizeof(m0_display_image_buffer)/sizeof(m0_display_image_buffer[0]);
  for (int o = 0; o < m0_buffer_size; o++) {
    for (int i = 0; i < 4; i++) {
      m0_display_image_buffer[o][i] = m0_display_image_buffer[o+1][i];
    }
  }
}
