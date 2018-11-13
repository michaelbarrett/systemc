#include "environment.h"
#include "robot.h"
#include "server.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_clock c1 ("c1", 5, SC_MS);
  //sc_signal<bool> c1;
  cout << "Clock Period: " << c1.period() << endl;

  //module instantiation
  environment e1("e1");
  robot r1("r1");
  server s1("s1");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("navigation");

  //association
  //clock wiring
  e1.clock(c1);
  r1.clock(c1);
  s1.clock(c1);

  //signal trace
  sc_trace(tfile, c1, "c1");

  sc_start(1000000, SC_MS); //100s
  sc_close_vcd_trace_file(tfile);

  return 0;
}
