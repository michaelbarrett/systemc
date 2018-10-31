//server.cpp
#include "server.h"

sc_event server::ev_env;

void server :: prc() {
  i = 1;
  while(1) {
    cout << "SERVER: process running" << endl;
    wait(ev_env);
    cout << "SERVER: Received message from environment." << endl;
    /*if (message.read() == 1) {
      cout << "CROSSING received from robot" << i << endl;
      i++;
    }
    if (message.read() == 2) {
      cout << "STOPPED received from robot" << endl;
      }*/
    wait();
    }
}

void server :: message_from_env(int m) {
  cout << "Hi from server message_from_env." << endl;
  ev_env.notify();
  cout << "ev_env notified." << endl;
}
