//server.cpp
#include "server.h"

void server :: prc() {
  i = 1;
  while(1) {
    if (message.read() == 1) {
      cout << "CROSSING received from robot" << i << endl;
      i++;
    }
    if (message.read() == 2) {
      cout << "STOPPED received from robot" << endl;
    }
  }
}
