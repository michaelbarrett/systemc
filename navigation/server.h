//server.h
#include "systemc.h"
SC_MODULE (server) {
  sc_in<bool> clock;
  int message;

  //format: {[ROBOT INDEX]: < GRID LIST > ...}
  int grid_list_data[50][50] =
    {
     {1, 11, 13, 14, 15, 16, 17, 18},
     {10, 12, 22, 21, 20, 19, 18}
    };

  //format: {[ROBOT INDEX]: ROBOT SPEED, CURRENT GRID, STATUS}
  //status: 0 = ok, 1 = stop at the grid due to no ack, 2 = stop due to obstacles
  //3 = stop due to position error
  int robot_status[50][50] =
    {
     {0.1, 1, 0},
     {0.1, 10, 0}
    };

  void prc();

 public:
  static void receive_message(int m);
  static void send_message(int m);

  static int get_current_grid_robot(int robot_index);
  static void set_current_grid_robot(int robot_index, int new_current_grid);
  static int get_next_grid_robot(int robot_index);
  static bool is_grid_occupied(int grid_index);
  
  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
  }
};
