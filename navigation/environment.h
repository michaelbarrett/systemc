//environment.h
#include "systemc.h"

SC_MODULE(environment) {
  //out to robot then to server
  //0 = None
  //1 = "CROSSING"
  sc_out<int> message;
  //holds all the robot coords
  //for robot indices 0, 1, 2, 3, etc
  //Point[] robotCoords
  int robotx = 1;
  int roboty = 1;
  int humanx = 9;
  int humany = 1;

  //grid map array
  //grid array = all boxes of grid in order -- now the grid is 5 horiz boxes
  //{{INDEX, X1, Y1, X2, Y2}, {...}, ...}
  int** grid = {{0, 0, 0, 2, 2}, {1, 2, 0, 4, 2}, {2, 4, 0, 6, 2}, {3, 6, 0, 8, 2}, {4, 8, 0, 10, 2}};
  //local variable path
  int* _path; //path, parameterizable -- PHASE 2: add possibility for multiple paths with multiple robots

  void prc();
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name, int* path) : sc_module(name), _path(path) {
    SC_CTHREAD(prc, clock.pos());
  }
};
