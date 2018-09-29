//Main Program: two_counters
/*This program consists of two 8-bit counters which function together as a countdown timer. Counter1 is loaded with 8 bit input 'in1' when 'load1' is high, and is decremented by 1 when 'dec1' is high. Counter2 is loaded from 8 bit input 'in2' when 'load2' is high, and is decremented by an amount specified in 8-bit input 'in3' when 'dec2' is high.*/
/* Whenever the contents of the two 8-bit counters become the same as each other, then the output flag 'ended' goes high and the counter contents are held until one of them is reloaded from either 'in1' or 'in2'.*/
//main.cpp
#include "driver.h"
#include "counter1.h"
#include "counter2.h"
#include "ended_determiner.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_signal <sc_uint<8> > t_in1, t_in2, t_in3, t_count1, t_count2;
  sc_signal <bool> t_load1, t_load2, t_dec1, t_dec2, t_overflow1, t_overflow2;
  sc_signal <bool> t_ended, t_hold;
  sc_clock c1 ("c1", 5, SC_NS);

  //module instantiation
  counter1 ct1("ct1");
  counter2 ct2("ct2");
  driver d1("d1");
  ended_determiner ed1("ed1");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("two_counters");

  //association
  d1.d_in1(t_in1); //from driver 
  d1.d_in2(t_in2);
  d1.d_in3(t_in3);
  d1.d_load1(t_load1);
  d1.d_load2(t_load2);
  d1.d_dec1(t_dec1);
  d1.d_dec2(t_dec2);

  ct1.clock(c1); //from counter1
  ct1.in1(t_in1);
  ct1.load1(t_load1);
  ct1.dec1(t_dec1);
  ct1.hold(t_hold);
  ct1.count1(t_count1);
  ct1.overflow1(t_overflow1);

  ct2.clock(c1); //from counter2
  ct2.in2(t_in2);
  ct2.in3(t_in3);
  ct2.load2(t_load2);
  ct2.dec2(t_dec2);
  ct2.hold(t_hold);
  ct2.count2(t_count2);
  ct2.overflow2(t_overflow2);

  ed1.ed_count1(t_count1); //from ending_determiner
  ed1.ed_count2(t_count2);
  ed1.ed_overflow1(t_overflow1);
  ed1.ed_overflow2(t_overflow2);
  ed1.load1(t_load1);
  ed1.load2(t_load2);
  ed1.ended(t_ended);
  ed1.hold(t_hold);
  
  //signal trace
  sc_trace(tfile, c1, "c1");
  sc_trace(tfile, t_in1, "t_in1");
  sc_trace(tfile, t_in2, "t_in2");
  sc_trace(tfile, t_in3, "t_in3");
  sc_trace(tfile, t_count1, "t_count1");
  sc_trace(tfile, t_count2, "t_count2");
  sc_trace(tfile, t_load1, "t_load1");
  sc_trace(tfile, t_load2, "t_load2");
  sc_trace(tfile, t_dec1, "t_dec1");
  sc_trace(tfile, t_dec2, "t_dec2");
  sc_trace(tfile, t_overflow1, "t_overflow1");
  sc_trace(tfile, t_overflow2, "t_overflow2");
  sc_trace(tfile, t_ended, "t_ended");
  sc_trace(tfile, t_hold, "t_hold");
  
  sc_start(170, SC_NS);

  sc_close_vcd_trace_file(tfile);
  return 0;
}
