//robot.cpp
#include "robot.h"

void robot :: prc() {
  while(1) {
    message_o.write(message_i);
  }
}
