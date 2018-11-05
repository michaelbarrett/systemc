//server.cpp
#include "server.h"

sc_event server::ev_env;

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
  int robot_grid_list = grid_list_data[robot_index];
  int current_grid_robot = get_current_grid_robot(robot_index);
  for (int i = 0; i < sizeof(robot_grid_list); i++) {
    if (robot_grid_list[i] == current_grid_robot) {
      if ((i+1) < sizeof(robot_grid_list)) {
	return robot_grid_list[i+1]; //return the next one in the path after current
      }
      else {
	return -1; //no next grid
      }
    }
  }
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
      //Q: Into which grid is this robot entering?
      if (is_grid_occupied()) {
	
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
  ev_env.notify();
  cout << "ev_env notified." << endl;
}

//Called to send messages through robots to environment.
//0 = Nothing, 1 = Acknowledged (Ack)
void server :: send_message(int robot_index, int m) {
  
}
