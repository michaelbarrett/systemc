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

  int current_grid[NUM_ROBOTS-1] = {};

  //grid map array
  //{{INDEX, X1, Y1, X2, Y2}, {...}, ...}
  int grid[50][50] =
  int grid[50][50] =
{ //row index 0
 {1, 0, 0, 2, 2}, {2, 2, 0, 4, 2}, {3, 4, 0, 6, 2}, {4, 6, 0, 8, 2}, {5, 8, 0, 10, 2}, {6, 10, 0, 12, 2}, {7, 12, 0, 14, 2},
 {8, 14, 0, 16, 2}, {9, 16, 0, 18, 2}, {10, 18, 0, 20, 2},
 //row index 1
 {11, 0, 2, 2, 4}, {12, 18, 2, 20, 4},
 //row index 2
 {13, 0, 4, 2, 6}, {14, 2, 4, 4, 6}, {15, 4, 4, 6, 6}, {16, 6, 4, 8, 6}, {17, 8, 4, 10, 6}, {18, 10, 4, 12, 6}, {19, 12, 4, 14, 6},
 {20, 14, 4, 16, 6}, {21, 16, 4, 18, 6}, {22, 18, 4, 20, 6}
 //row index 3
 {23, 0, 6, 2, 8}, {24, 10, 6, 12, 8}, {25, 18, 6, 20, 8},
 //row index 4
 {26, 0, 8, 2, 10}, {27, 2, 8, 4, 10}, {28, 4, 8, 6, 10}, {29, 6, 8, 8, 10}, {30, 8, 8, 10, 10}, {31, 10, 8, 12, 10},
 {32, 12, 8, 14, 10}, {33, 14, 8, 16, 10}, {34, 16, 8, 18, 10},  {35, 18, 8, 20, 10},
 //row index 5
 {36, 0, 10, 2, 12}, {37, 12, 10, 14, 12}, {38, 18, 10, 20, 12},
 //row index 6
 {39, 0, 12, 2, 14}, {40, 2, 12, 4, 14}, {41, 4, 12, 6, 14}, {42, 6, 12, 8, 14}, {43, 8, 12, 10, 14}, {44, 10, 12, 12, 14},
 {45, 12, 12, 14, 14}, {46, 14, 12, 16, 14}, {47, 16, 12, 18, 14}, {48, 18, 12, 20, 14},
 //row index 7
 {49, 0, 14, 2, 16}, {50, 18, 14, 20, 16},
 //row index 8
 {51, 0, 16, 2, 18}, {52, 2, 16, 4, 18}, {53, 4, 16, 6, 18}, {54, 6, 16, 8, 18}, {55, 8, 16, 10, 18},  {56, 10, 16, 12, 18},
 {57, 12, 16, 14, 18}, {58, 14, 16, 16, 18}, {59, 16, 16, 18, 18}, {60, 18, 16, 20, 18}
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
