#include "server.h"
#include "mobile.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_clock c1 ("c1", 5, SC_MS);
  cout << "Clock Period: " << c1.period() << endl;
  //sc_set_time_resolution(1, SC_MS);

  //module instantiation
  server s1("s1");
  mobile mm("mm");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("gaze");

  //association
  //clock wiring
  s1.clock(c1);
  mm.clock(c1);

  //signal trace
  sc_trace(tfile, c1, "c1");

  sc_start(160000, SC_MS); //250,000 MS simulation
  sc_close_vcd_trace_file(tfile);

  return 0;
}
