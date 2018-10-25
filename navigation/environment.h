//environment.h
#include "systemc.h"

struct Point
{
  double x, y;
  Point(double xInit, yInit)
    : x(xInit), y(yInit) {
}
};

struct Box
{
  Point botLeft, topRight;
  Box(Point botLeftInit, topRightInit) : botLeft(botLeftInit), topRight(topRightInit) {
  }
}

double distance(Point point1, Point point2)
{
  return  sqrt((point1.x * point2.x) + (point1.y * point2.y));
}

SC_MODULE(environment) {
  //start gps at 0,0
  gps robotx = new Point(0, 0);
  gps roboty = new Point(0, 0);
  //grid map array
  //grid array = all boxes of grid in order -- now the grid is 5 horiz boxes
  //indices are 0, 1, 2, 3, etc
  int[] grid = {new Box(new Point(0, 0), new Point(2, 2)), new Box(new Point(2, 0), new Point(4, 2)), new Box(new Point(4, 0), new Point (6,2)), new Box(new Point(6, 0), new Point(8,2)), new Box(new Point(8, 0), new Point (10, 2))};
  //smth to hold current grid number in path and next grid number in path
  //local variable path
  int* _path; //path

  void prc();
  
  SC_HAS_PROCESS(environment);

 environment(sc_module_name name, int* path) : sc_module(name), _path(path) {
    SC_CTHREAD(prc, clock.pos());
  }
}
