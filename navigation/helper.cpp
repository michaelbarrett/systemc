//helper.cpp
#include "helper.h"

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2.0));
}

double get_center_x(double x1, double y1, double x2, double y2) {
  return ((x1 + x2) / 2.0);
}

double get_center_y(double x1, double y1, double x2, double y2) {
  return ((y1 + y2) / 2.0);
}

double distance(int x1, int y1, int x2, int y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2.0));
}

double get_center_x(int x1, int y1, int x2, int y2) {
  return ((x1 + x2) / 2.0);
}

double get_center_y(int x1, int y1, int x2, int y2) {
  return ((y1 + y2) / 2.0);
}
