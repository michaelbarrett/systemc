//Function: Main Program
//File Name: main.cpp
#include "driver.h"
#include "monitor.h"
#include "full_adder.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_signal <sc_logic> t_a, t_b, t_cin, t_sum, t_cout;

  //module instantiation
  full_adder f1("fa1");
  monitor m1("m1");
  driver d1("d1");

  //trace file define
  sc_trace_file *tfile = sc_create_vcd_trace_fie("full_adder");

  //signal association
  f1 << t_a << t_b << t_cin << t_sum << t_cout;

  d1.d_a(t_a);
  d1.d_b(t_b);
  d1.d_cin(t_cin);

  m1(t_a, t_b, t_cin, t_sum, t_cout);

  //signal trace
  sc_trace(tfile, t_a, "t_a");
  sc_trace(tfile, t_b, "t_b");
  sc_trace(tfile, t_cin, "t_cin");
  sc_trace(tfile, t_sum, "t_sum");
  sc_trace(tfile, t_cout, "t_cout");

  sc_start(100, SC_NS);

  sc_close_vcd_trace_file(tfile);
  return 0;
}
  
