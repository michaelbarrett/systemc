//server.h
#include "systemc.h"
SC_MODULE (server) {
  sc_in<bool> clock;
  
  static int message; //signifies message contents sent from environment
  static int message_robot_index; //signifies which robot sent the message

  static sc_event ev_env;

  static int grid_list_data[50][50];
  static int node_list_data[50][50];
  static int human_grid_list_data[50][50];

  static int robot_status[50][50];
  static int node_ordering[50][50];

  //format: {[ROBOT INDEX]: < GRID LIST > ...}

  //format: {[ROBOT INDEX]: ROBOT SPEED, CURRENT GRID, STATUS}
  //status: 0 = ok, 1 = stop at the grid due to no ack, 2 = stop due to obstacles
  //3 = stop due to position error

  void prc();

 public:
  static void receive_message(int robot_index, int m);
  static void send_message(int robot_index, int m);

  static int get_expected_arrival_time_node(int node_index, int robot_index);
  static int get_robot_status(int robot_index);
  static void set_robot_status(int robot_index, int status);
  static int get_current_grid_robot(int robot_index);
  static int get_current_node_robot(int robot_index);
  static void set_current_grid_robot(int robot_index, int new_current_grid);
  static void set_current_node_robot(int robot_index, int new_current_node);
  static int get_next_grid_robot(int robot_index);
  static int get_next_node_robot(int robot_index);
  static bool is_grid_occupied(int grid_index);
  
  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc);
    sensitive << clock.pos();
  }
};
