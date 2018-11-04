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
  double robotx[NUM_ROBOTS-1] = {};
  double roboty[NUM_ROBOTS-1] = {};
  double humanx[NUM_HUMANS-1] = {};
  double humany[NUM_HUMANS-1] = {};

  //grid map array
  //grid array = all boxes of grid in order -- now the grid is 5 horiz boxes
  //{{INDEX, X1, Y1, X2, Y2}, {...}, ...}
  int grid[50][50] =
{
 {1, 0, 0, 2, 2}, {2, 2, 0, 4, 2}, {3, 4, 0, 6, 2}, {4, 6, 0, 8, 2}, {5, 8, 0, 10, 2}, {6, 10, 0, 12, 2}, {7, 12, 0, 14, 2},
 {8, 14, 0, 16, 2}, {9, 16, 0, 18, 2}, {10, 18, 0, 20, 2},
 //Second Row
 {11, 0, 2, 2, 4}, {12, 18, 2, 20, 4},
 //Third Row
 {13, 0, 4, 2, 6}, {14, 2, 4, 4, 6}, {15, 4, 4, 6, 6}, {16, 6, 4, 8, 6}, {17, 8, 4, 10, 6}, {18, 10, 4, 12, 6}, {19, 12, 4, 14, 6},
 {20, 14, 4, 16, 6}, {21, 16, 4, 18, 6}, {22, 18, 4, 20, 6},
 //Fourth Row
 
};
  //local variable path
  int* _path; //path, parameterizable -- PHASE 2: add possibility for multiple paths with multiple robots

  void prc();
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name, int* path) : sc_module(name), _path(path) {
    SC_THREAD(prc);
    sensitive << clock.pos();
  }
};
