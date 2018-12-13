//mobile.cpp
#include "server.h"
#include "mobile.h"

sc_event mobile :: ev_image_to_mobile; //indicates an image was sent to a mobile

//current display image is [0] - [4]
int mobile :: m0_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m1_display_image_buffer[(PACKETS_PER_IMAGE * IMAGE_AMOUNT)][PACKET_ARRAY_LENGTH] = {0};
int mobile :: m0_image_packet_index = 5; //fills up over time; displayed image (0-4)
int mobile :: m1_image_packet_index = 5; //is not directly written to, but shifted in
//current frame
int mobile :: frame = 0;
//current gaze point
int mobile :: gaze_point[2] = {((IMAGE_SIZE_X / 2) - 1),
			       ((IMAGE_SIZE_Y / 2) - 1)}; //center of image
int mobile :: m0_packet[MAX_GAZE_PACKET_SIZE][3] = {0};

//mobile gaze UFO movement -- also functions as tx, sends gaze tuple packets
void mobile :: ufo() {
  srand (time(NULL)); //seed
  int tuple_counter = 0;
  int packet_counter = 0;
  while(true) {
    int roi = 0;
    gaze_point[0] = rand() % 1024; //x
    gaze_point[1] = rand() % 1024; //y
    //prep vars - get current time
    sc_time t = sc_time_stamp();
    int time_ms = t.value()/pow(10,9); //time in ms as int
    //also, get random time
    int random_time = rand() % 3000;
    if (frame != 0) { //if we are not showing an image, don't collect data
      /*cout << "Check X against: " << m0_display_image_buffer[0][0] << " and "
	   << m0_display_image_buffer[0][2] << endl;
      cout << "Check Y against: " << m0_display_image_buffer[0][1] << " and "
      << m0_display_image_buffer[0][3] << endl;*/
      if (gaze_point[0] > m0_display_image_buffer[0][0]
	  && gaze_point[0] < m0_display_image_buffer[0][2] //if x w/in ROI 1
	  && gaze_point[1] > m0_display_image_buffer[0][1]
	  && gaze_point[1] < m0_display_image_buffer[0][3]) { //& y w/in ROI 1
	roi = 1;
      }
      else if (gaze_point[0] > m0_display_image_buffer[1][0]
	       && gaze_point[0] < m0_display_image_buffer[1][2] //if x w/in ROI 2
	       && gaze_point[1] > m0_display_image_buffer[1][1]
	       && gaze_point[1] < m0_display_image_buffer[1][3]) { //& y w/in ROI 2
	roi = 2;
      }
      else if (gaze_point[0] > m0_display_image_buffer[2][0]
	       && gaze_point[0] < m0_display_image_buffer[2][2] //if x w/in ROI 3
	       && gaze_point[1] > m0_display_image_buffer[2][1]
	       && gaze_point[1] < m0_display_image_buffer[2][3]) { //& y w/in ROI 3
	roi = 3;
      }
      else if (gaze_point[0] > m0_display_image_buffer[3][0]
	       && gaze_point[0] < m0_display_image_buffer[3][2] //if x w/in ROI 2
	       && gaze_point[1] > m0_display_image_buffer[3][1]
	       && gaze_point[1] < m0_display_image_buffer[3][3]) { //& y w/in ROI 2
	roi = 4;
      }
      else if (gaze_point[0] > m0_display_image_buffer[4][0]
	       && gaze_point[0] < m0_display_image_buffer[4][2] //if x w/in ROI 2
	       && gaze_point[1] > m0_display_image_buffer[4][1]
	       && gaze_point[1] < m0_display_image_buffer[4][3]) { //& y w/in ROI 2
	roi = 5;
      }
      cout << "Gaze point: (" << gaze_point[0] << ", "
	   << gaze_point[1] << ")" << endl;
      cout << "Mobile eyes looking at ROI " << roi << endl;

      //make a tuple: (ROI, start time [MS], end time [MS]) and packetize
      m0_packet[tuple_counter][0] = roi;
      m0_packet[tuple_counter][1] = time_ms;
      cout << "time_ms: " << time_ms << endl;   
      m0_packet[tuple_counter][2] = time_ms + random_time;
      cout << "time_ms + random_time: " << (time_ms + random_time) << endl;
      tuple_counter += 1;
      cout << "m0_packet packet contents: " << endl;
      //print vector
      for (int i = 0; i < tuple_counter; i++) {
	cout << "Tuple " << i << ": ("
	     << m0_packet[i][0] << ", "
	     << m0_packet[i][1] << ", "
	     << m0_packet[i][2] << ")" << endl;
      }
    }
    //after dealing with tuple creation, send a packet if we have >=20 tuples ready
    if (tuple_counter >= MIN_GAZE_PACKET_SIZE) { //20 tuples
      if (server::is_free) {
	//ACTIONS
	//send "can I use the network" (network_request)
	//server says yes or no
	//if no, wait a random time (wait(random))
	//if yes, send from server when network signal goes high (signal = data ready)
	for (int i = 0; i < tuple_counter; i++) { //server receives entire packet
	  server::receive_tuple_packet(0, packet_counter, i, m0_packet[i]); 
	}
	//now clear the m0_packet, and reset tuple_counter
	for (int i = 0; i < tuple_counter; i++) {
	  m0_packet[i][0] = 0;
	  m0_packet[i][1] = 0;
	  m0_packet[i][2] = 0; 
	}
	tuple_counter = 0;
	packet_counter += 1; //inc packet counter before we start filling next packet
      }
    }
    //wait random time
    wait(random_time, SC_MS); //WAIT RANDOM TIME -- from 0ms to 3,000ms (3 sec)
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
    int time_ms = t.value()/pow(10,9); //time in ms as int
    cout << "MOBILE: TVAL = " << time_ms << endl; 
    if (time_ms > 150000 && frame == 0) { //display @ 150,000 MS = 150 sec
      percolate_new_image(0); //mobile 0 -- percolate new image
      frame = 1;
    }
    //TODO: Show the other images in timeline sequence
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
      m0_display_image_buffer[o][i] = m0_display_image_buffer[o+5][i];
    }
  }
}
