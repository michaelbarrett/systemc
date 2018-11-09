//server.cpp
#include "helper.h"
#include "server.h"

int server :: message = 0;
int server :: message_robot_index = 0;
sc_event server :: ev_env;

int server :: grid_list_data[50][50] =
  {
   {1, 11, 13, 14, 15, 16, 17, 18, 24, 31, 30, 29, 28, 27, 26, 36, 39},
   {10, 12, 22, 21, 20, 19}
  };

int server :: robot_status[50][50] =
  {
   {1, 1, 0},
   {1, 10, 0}
  };

//gets the current grid of a robot from server data.
int server :: get_current_grid_robot(int robot_index) {
  return robot_status[robot_index][1];
}

//sets the current grid of a robot in server data.
void server :: set_current_grid_robot(int robot_index, int new_current_grid) {
  robot_status[robot_index][1] = new_current_grid;
}

//gets the next grid of a robot from server data (using grid list data)
int server :: get_next_grid_robot(int robot_index) {
  //get the grid list and put it in robot_grid_list
  int robot_grid_list[20];
  int size_elements = sizeof(robot_grid_list)/sizeof(robot_grid_list[0]);
  for (int i = 0; i < size_elements; i++) {
    robot_grid_list[i] = grid_list_data[robot_index][i];
  }
  //linear search for current grid variable, then return the next one
  int current_grid_robot = get_current_grid_robot(robot_index);

  for (int i = 0; i < size_elements; i++) {
    cout << robot_grid_list[i] << ", " << endl;
  }
  
  for (int i = 0; i < size_elements; i++) {
    if (robot_grid_list[i] == current_grid_robot) {
      if ((i+1) < size_elements) {
	return robot_grid_list[i+1]; //return the next one in the path after current
      }
      else {
	return -1; //no next grid
      }
    }
  }
  return -1;
}

//returns whether the given grid is occupied by any robot.
bool server :: is_grid_occupied(int grid_index) {
  for (int i = 0; i<sizeof(robot_status); i++) {
    if ((get_current_grid_robot(i)) == grid_index) { return true; }
  }
  return false;
}

void server :: prc() {
  while(1) {
    wait(ev_env); //wait for a message from the environment
    cout << "SERVER: Received message from environment." << endl;
    if (message == 1) {
      cout << "SERVER: CROSSING received from robot" << endl;
      //now check if there is a robot in the NEXT GRID of that robot
      //and if not, send "ack".
      //Q: Which robot is sending the message?
      //Q: Into which grid is this robot entering?
      int next_grid_index = get_next_grid_robot(message_robot_index);
      if (is_grid_occupied(next_grid_index)) {
	
      }
    }
    if (message == 2) {
      cout << "SERVER: STOPPED received from robot" << endl;
      }
    wait();
    }
}

//Called when a message is sent to the server. Notifies the "ev_env" event and sets the "message" variable to the one corresponding to the particular event.
void server :: receive_message(int robot_index, int m) {
  message = m;
  message_robot_index = robot_index;
  ev_env.notify();
  cout << "ev_env notified." << endl;
}

//Called to send messages through robots to environment.
//0 = Nothing, 1 = Acknowledged (Ack)
void server :: send_message(int robot_index, int m) {
  
}
