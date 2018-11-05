//server.h
#include "systemc.h"
SC_MODULE (server) {
  sc_in<bool> clock;
  int message;

  //format: {ROBOT INDEX, < GRID LIST > ...}
  int grid_list_data[50][50] =
    {
     {0, 1, 11, 13, 14, 15, 16, 17, 18},
     {1, 10, 12, 22, 21, 20, 19, 18}
    };

  //format: {ROBOT INDEX, ROBOT SPEED, CURRENT GRID, STATUS}
  //status: 0 = ok, 1 = stop at the grid due to no ack, 2 = stop due to obstacles
  //3 = stop due to position error
  int robot_status[50][50] =
    {
     {0, 1, 1, 0},
     {1, 1, 10, 0}
    };

  void prc();

 public:
  static void message_from_env(int m);
  
  SC_HAS_PROCESS(server);

 server(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(prc, clock.pos());
  }
};
