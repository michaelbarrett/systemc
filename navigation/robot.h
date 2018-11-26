//robot.h
#include "systemc.h"
SC_MODULE (robot) {
  sc_in<bool> clock;

  static int message; //signifies message contents sent from environment
  static int message_robot_index; //signifies which robot sent the message

  void prc();

 public:
  static void receive_message(int robot_index, int m);
  static void send_message(int robot_index, int m);

  SC_HAS_PROCESS(robot);

 robot(sc_module_name name) : sc_module(name) {
    SC_THREAD(prc);
    sensitive << clock.pos();
  }
};
