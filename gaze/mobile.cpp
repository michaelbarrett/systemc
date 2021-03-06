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
int mobile :: m0_packet_to_image_counter = 0;

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
      m0_packet[tuple_counter][2] = time_ms + random_time;
      tuple_counter += 1;
      //print vector
      /*for (int i = 0; i < tuple_counter; i++) {
	cout << "Tuple " << i << ": ("
	     << m0_packet[i][0] << ", "
	     << m0_packet[i][1] << ", "
	     << m0_packet[i][2] << ")" << endl;
	     }*/
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
	  cout << "Server is receiving gaze data packet " << packet_counter << endl;
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
      m0_display_image_buffer[0][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[1][0] << ", " << 
      m0_display_image_buffer[1][1] << ", " << 
      m0_display_image_buffer[1][2] << ", " << 
      m0_display_image_buffer[1][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[2][0] << ", " << 
      m0_display_image_buffer[2][1] << ", " << 
      m0_display_image_buffer[2][2] << ", " << 
      m0_display_image_buffer[2][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[3][0] << ", " << 
      m0_display_image_buffer[3][1] << ", " << 
      m0_display_image_buffer[3][2] << ", " << 
      m0_display_image_buffer[3][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[4][0] << ", " << 
      m0_display_image_buffer[4][1] << ", " << 
      m0_display_image_buffer[4][2] << ", " << 
      m0_display_image_buffer[4][3] << "}" << endl;
    cout << "MOBILE: SECOND IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[5][0] << ", " << 
      m0_display_image_buffer[5][1] << ", " << 
      m0_display_image_buffer[5][2] << ", " << 
      m0_display_image_buffer[5][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[6][0] << ", " << 
      m0_display_image_buffer[6][1] << ", " << 
      m0_display_image_buffer[6][2] << ", " << 
      m0_display_image_buffer[6][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[7][0] << ", " << 
      m0_display_image_buffer[7][1] << ", " << 
      m0_display_image_buffer[7][2] << ", " << 
      m0_display_image_buffer[7][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[8][0] << ", " << 
      m0_display_image_buffer[8][1] << ", " << 
      m0_display_image_buffer[8][2] << ", " << 
      m0_display_image_buffer[8][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[9][0] << ", " << 
      m0_display_image_buffer[9][1] << ", " << 
      m0_display_image_buffer[9][2] << ", " << 
      m0_display_image_buffer[9][3] << "}" << endl;
    cout << "MOBILE: THIRD IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[10][0] << ", " << 
      m0_display_image_buffer[10][1] << ", " << 
      m0_display_image_buffer[10][2] << ", " << 
      m0_display_image_buffer[10][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[11][0] << ", " << 
      m0_display_image_buffer[11][1] << ", " << 
      m0_display_image_buffer[11][2] << ", " << 
      m0_display_image_buffer[11][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[12][0] << ", " << 
      m0_display_image_buffer[12][1] << ", " << 
      m0_display_image_buffer[12][2] << ", " << 
      m0_display_image_buffer[12][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[13][0] << ", " << 
      m0_display_image_buffer[13][1] << ", " << 
      m0_display_image_buffer[13][2] << ", " << 
      m0_display_image_buffer[13][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[14][0] << ", " << 
      m0_display_image_buffer[14][1] << ", " << 
      m0_display_image_buffer[14][2] << ", " << 
      m0_display_image_buffer[14][3] << "}" << endl;
    cout << "MOBILE: FOURTH IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[15][0] << ", " << 
      m0_display_image_buffer[15][1] << ", " << 
      m0_display_image_buffer[15][2] << ", " << 
      m0_display_image_buffer[15][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[16][0] << ", " << 
      m0_display_image_buffer[16][1] << ", " << 
      m0_display_image_buffer[16][2] << ", " << 
      m0_display_image_buffer[16][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[17][0] << ", " << 
      m0_display_image_buffer[17][1] << ", " << 
      m0_display_image_buffer[17][2] << ", " << 
      m0_display_image_buffer[17][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[18][0] << ", " << 
      m0_display_image_buffer[18][1] << ", " << 
      m0_display_image_buffer[18][2] << ", " << 
      m0_display_image_buffer[18][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[19][0] << ", " << 
      m0_display_image_buffer[19][1] << ", " << 
      m0_display_image_buffer[19][2] << ", " << 
      m0_display_image_buffer[19][3] << "}" << endl;
    cout << "MOBILE: FIFTH IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[20][0] << ", " << 
      m0_display_image_buffer[20][1] << ", " << 
      m0_display_image_buffer[20][2] << ", " << 
      m0_display_image_buffer[20][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[21][0] << ", " << 
      m0_display_image_buffer[21][1] << ", " << 
      m0_display_image_buffer[21][2] << ", " << 
      m0_display_image_buffer[21][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[22][0] << ", " << 
      m0_display_image_buffer[22][1] << ", " << 
      m0_display_image_buffer[22][2] << ", " << 
      m0_display_image_buffer[22][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[23][0] << ", " << 
      m0_display_image_buffer[23][1] << ", " << 
      m0_display_image_buffer[23][2] << ", " << 
      m0_display_image_buffer[23][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[24][0] << ", " << 
      m0_display_image_buffer[24][1] << ", " << 
      m0_display_image_buffer[24][2] << ", " << 
      m0_display_image_buffer[24][3] << "}" << endl;
    cout << "MOBILE: SIXTH IMAGE: ROI 0 ~ {" <<
      m0_display_image_buffer[25][0] << ", " << 
      m0_display_image_buffer[25][1] << ", " << 
      m0_display_image_buffer[25][2] << ", " << 
      m0_display_image_buffer[25][3] << "} ~ ";
    cout << "ROI 1 ~ {" <<
      m0_display_image_buffer[26][0] << ", " << 
      m0_display_image_buffer[26][1] << ", " << 
      m0_display_image_buffer[26][2] << ", " << 
      m0_display_image_buffer[26][3] << "} ~ ";
    cout << "ROI 2 ~ {" <<
      m0_display_image_buffer[27][0] << ", " << 
      m0_display_image_buffer[27][1] << ", " << 
      m0_display_image_buffer[27][2] << ", " << 
      m0_display_image_buffer[27][3] << "} ~ ";
    cout << "ROI 3 ~ {" <<
      m0_display_image_buffer[28][0] << ", " << 
      m0_display_image_buffer[28][1] << ", " << 
      m0_display_image_buffer[28][2] << ", " << 
      m0_display_image_buffer[28][3] << "} ~ ";
    cout << "ROI 4 ~ {" <<
      m0_display_image_buffer[29][0] << ", " << 
      m0_display_image_buffer[29][1] << ", " << 
      m0_display_image_buffer[29][2] << ", " << 
      m0_display_image_buffer[29][3] << "}" << endl;             
    sc_time t = sc_time_stamp();
    cout << "MOBILE: TIME = " << t << endl;
    int time_ms = t.value()/pow(10,9); //time in ms as int
    if (time_ms > 150000 && frame == 0) { //display @ 150,000 MS = 150 sec
      percolate_new_image(0); //mobile 0 -- percolate new image
      frame = 1;
    }
    if (time_ms > 175000 && frame == 1) {
      percolate_new_image(0);
      frame = 2;
    }
    if (time_ms > 200000 && frame == 2) {
      percolate_new_image(0);
      frame = 3;
    }
    if (time_ms > 225000 && frame == 3) {
      percolate_new_image(0);
      frame = 4;
    }
    if (time_ms > 250000 && frame == 4) {
      percolate_new_image(0);
      frame = 5;
    }
    //TODO: Show the other images in timeline sequence
    wait();
  }
}

//receive an image packet from the server
void mobile :: receive_image_packet(int mobile_index, int image_packet[4]) {
  /*if (image_packet[0] == 0 && image_packet[1] == 0 && image_packet[2] == 0 && image_packet[3] == 0) {
    cout << "MOBILE.RECEIVE_IMAGE: No image to receive." << endl;
    return;
    }*/
  cout << "MOBILE.RECEIVE_IMAGE: Received packet is " << image_packet[0] << ", " << image_packet[1] << ", " << image_packet[2] << ", " << image_packet[3] << endl;
  //copy image packet to display_image_buffer
  for (int i = 0; i < 4; i++) {
    m0_display_image_buffer[m0_image_packet_index][i] = image_packet[i];
   
  }
  m0_image_packet_index += 1;

  m0_packet_to_image_counter += 1;
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
