#include "environment.h"
#include "robot.h"
#include "server.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_signal<int> t_message_to_robot, t_message_to_server;
  sc_clock c1 ("c1", 5, SC_NS);
  //sc_signal<bool> c1;
  //cout << c1.period() << endl;

  //parameters for paramaterized modules
  int path[] = {0, 1, 2, 3, 4};

  //module instantiation
  environment e1("e1", &path[0]);
  robot r1("r1");
  server s1("s1");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("navigation");

  //association
  //clock wiring
  e1.clock(c1);
  r1.clock(c1);
  s1.clock(c1);
  //wiring for message signal
  e1.message(t_message_to_robot);
  r1.message_i(t_message_to_robot);
  r1.message_o(t_message_to_server);
  s1.message(t_message_to_server);

  //signal trace
  sc_trace(tfile, c1, "c1");
  
  sc_start(1000, SC_NS);
  sc_close_vcd_trace_file(tfile);

  return 0;
}
