//environment.h
#include "systemc.h"

SC_MODULE(environment) {
  sc_in<bool> clock;
  //out to robot then to server
  //0 = None
  //1 = "CROSSING"
  int my_message;
  sc_out<int> message;
  //holds all the robot coords
  //for robot indices 0, 1, 2, 3, etc
  //Point[] robotCoords
  double robotx = 1;
  double roboty = 1;
  double humanx = 9;
  double humany = 1;

  //grid map array
  //grid array = all boxes of grid in order -- now the grid is 5 horiz boxes
  //{{INDEX, X1, Y1, X2, Y2}, {...}, ...}
  int grid[50][50] = {{1, 0, 0, 2, 2}, {2, 2, 0, 4, 2}, {3, 4, 0, 6, 2}, {4, 6, 0, 8, 2}, {5, 8, 0, 10, 2}};
  //local variable path
  int* _path; //path, parameterizable -- PHASE 2: add possibility for multiple paths with multiple robots

  void prc();
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name, int* path) : sc_module(name), _path(path) {
    SC_CTHREAD(prc, clock.pos());
    //   sensitive << clock.pos();
  }
};
