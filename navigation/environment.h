//environment.h
#include "systemc.h"

const double MAX_SPEED_X = 0.002;
const double MAX_SPEED_Y = 0.002;
const double HUMAN_SPEED_X = 0.005;
const double HUMAN_SPEED_Y = 0.005;
const int NUM_ROBOTS = 4;
const int NUM_HUMANS = 6;
const int NUM_ROWS = 3;

SC_MODULE(environment) {
  sc_in<bool> clock;
  //SENDING: out to robot then to server
  //0 = None
  //1 = "CROSSING"
  //RECEIVING: from server thru robot
  //0 = None
  //1 = Ack
  static int message_received;
  //holds all the robot coords
  //for robot indices 0, 1, 2, 3, etc
  //Point[] robotCoords
  static bool path_fin[NUM_ROBOTS];
  static double start_time[NUM_ROBOTS];
  static double robotx[NUM_ROBOTS];
  static double roboty[NUM_ROBOTS];
  static double robot_speed[NUM_ROBOTS];
  static double humanx[NUM_HUMANS];
  static double humany[NUM_HUMANS];
  static int human_grids[NUM_HUMANS];
  static int human_grid_list_data[50][50];

  //stop state in env: 0 = not stopped, 1 = stopped due to no ack, 2 = " due to human, 3 = stopped due to pos error, 4 = idle
  static int stop_state[NUM_ROBOTS];

  static int current_grid[NUM_ROBOTS];

  //grid map array
  //{{INDEX, X1, Y1, X2, Y2}, {...}, ...}
  static int grid[60][60];

  //local variable path
  //int* _path; //path, parameterizable -- PHASE 2: add possibility for multiple paths with multiple robots

  void prc();

 public:
  static void receive_message(int m);

  static int get_current_grid_human(int human_index);
  static void set_current_grid_human(int human_index, int grid_index);
  static int get_next_grid_human(int human_index, int current_grid);
  static double get_x_center_of_grid(int grid_index);
  static double get_y_center_of_grid(int grid_index);
  static int my_grid_index(int robot_index);
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc);
    sensitive << clock.pos();
  }
};
