//environment.h
#include "systemc.h"

//A point is x,y -- used for GPS
struct Point
{
  double x, y;
  Point(double xInit, yInit)
    : x(xInit), y(yInit) {
}
};

//A box is a bottom left corner point and a top right corner point -- used for grid definition and storage
struct Box
{
  Point botLeft, topRight;
  Box(Point botLeftInit, topRightInit) : botLeft(botLeftInit), topRight(topRightInit) {
  }
}

//finds the distance between two gps points
double distance(Point point1, Point point2)
{
  return  sqrt((point1.x * point2.x) + (point1.y * point2.y));
}

SC_MODULE(environment) {
  //holds all the robot coords
  //for robot indices 0, 1, 2, 3, etc
  //Point[] robotCoords
  Point robotp = new Point(1, 1);
  
  Point humanp = new Point(9, 1);
  //grid map array
  //grid array = all boxes of grid in order -- now the grid is 5 horiz boxes
  //grid indices are 0, 1, 2, 3, etc
  int[] grid = {new Box(new Point(0, 0), new Point(2, 2)), new Box(new Point(2, 0), new Point(4, 2)), new Box(new Point(4, 0), new Point (6,2)), new Box(new Point(6, 0), new Point(8,2)), new Box(new Point(8, 0), new Point (10, 2))};
  //smth to hold current grid number in path and next grid number in path
  int currGrid;
  int nextGrid;
  //local variable path
  int* _path; //path, parameterizable -- PHASE 2: add possibility for multiple paths with multiple robots

  void prc();
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name, int* path) : sc_module(name), _path(path) {
    SC_CTHREAD(prc, clock.pos());
  }
}
