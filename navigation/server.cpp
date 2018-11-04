//server.cpp
#include "server.h"

sc_event server::ev_env;

void server :: prc() {
  while(1) {
    wait(ev_env); //wait for a message from the environment
    cout << "SERVER: Received message from environment." << endl;
    if (message == 1) {
      cout << "SERVER: CROSSING received from robot" << i << endl;
      i++;
    }
    if (message == 2) {
      cout << "SERVER: STOPPED received from robot" << endl;
      }
    wait();
    }
}

//Called when a message is sent to the server. Notifies the "ev_env" event and sets the "message" variable to the one corresponding to the particular event.
void server :: message_from_env(int m) {
  message = m;
  ev_env.notify();
  cout << "ev_env notified." << endl;
}
