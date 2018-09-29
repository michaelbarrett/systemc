//Main Program
//main.cpp
#include "driver.h"
#include "sdet.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_signal <bool> t_data, t_reset, t_clear, t_seq_found;
  sc_clock c1 ("c1", 5, SC_NS);

  //module instantiation
  sdet s1("sdet1");
  driver d1("d1");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("sdet");

  //association
  d1.d_data(t_data); //d1 outputs data to t_data wire
  d1.d_reset(t_reset); //...reset to t_reset wire
  d1.d_clear(t_clear); //...clear to t_clear wire

  s1.clock(c1); //s1 is fed clock directly

  s1.data(t_data); //s1 is fed t_data wire
  s1.reset(t_reset); //...t_reset wire
  s1.clear(t_clear); //...t_clear wire
  s1.seq_found(t_seq_found); //wire to monitor

  //signal trace
  sc_trace(tfile, c1, "c1");
  sc_trace(tfile, t_data, "t_data");
  sc_trace(tfile, t_seq_found, "t_seq_found");
  sc_trace(tfile, t_reset, "t_reset");
  sc_trace(tfile, t_clear, "t_clear");
  sc_trace(tfile, s1.first, "s1.first");
  sc_trace(tfile, s1.second, "s1.second");
  sc_trace(tfile, s1.third, "s1.third");
  sc_trace(tfile, s1.fourth, "s1.fourth");

  sc_start(370, SC_NS);

  sc_close_vcd_trace_file(tfile);
  return 0;
}
