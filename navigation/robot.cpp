//robot.cpp
#include "robot.h"

void robot :: prc() {
  while(1) {
    /*if (message_i.read() == 1) {
      cout << "prc is running and message_i is " << message_i.read() << endl;
      }*/
    message_o.write(message_i.read());
    
  }
}
