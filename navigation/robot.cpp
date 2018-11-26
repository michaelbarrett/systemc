//robot.cpp
#include "helper.h"
#include "robot.h"

void robot :: prc() {
  while(1) {
    wait();
  }
}

void robot :: receive_message(int robot_index, int m) {
  server::receive_message(int robot_index, int m);
}

void robot :: send_message(int robot_index, int m) {
  environment::receive_message(int robot_index, int m);
}
