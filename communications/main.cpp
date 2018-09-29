//Communications test
/*Implements a simple communications interface. There is a data packet which is received by module packet_receiver. The data packet is structured like so:

in_data[11:8] is the header, used to determine input type. When in_data is type 1 (0001), the output of the program follows the input data payload.
in_data[7:4] contains the data payload.
in_data[3:1] are not used.
in_data[0] is an odd parity bit. It is '1' if the data payload is even parity without errors.

Example data:
in_data 1F1, 0E0, 171, 0E0

*/
//main.cpp
#include "driver.h"
#include "packet_receiver.h"

int sc_main(int argc, char* argv[]) {
  //ports decl
  sc_signal <bool> t_reset, t_clear;
  sc_signal <sc_bv<12> > t_in_data;
  sc_signal <sc_bv<4> > t_payload;
  sc_signal <sc_bv<8> > t_count;
  sc_signal <sc_bv<8> > t_error;
  sc_clock c1 ("c1", 5, SC_NS);

  //module instantiation
  packet_receiver pr1("pr1");
  driver d1("d1");

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("communications");

  //association
  d1.d_reset(t_reset);
  d1.d_clear(t_clear);
  d1.d_in_data(t_in_data);

  pr1.clock(c1); //pr1 is fed clock directly

  pr1.reset(t_reset);
  pr1.clear(t_clear);
  pr1.in_data(t_in_data);

  pr1.payload(t_payload);
  pr1.count(t_count);
  pr1.error(t_error);

  //signal trace
  sc_trace(tfile, c1, "c1");
  sc_trace(tfile, t_in_data, "t_in_data");
  sc_trace(tfile, t_clear, "t_clear");
  sc_trace(tfile, t_reset, "t_reset");
  sc_trace(tfile, t_payload, "t_payload");
  sc_trace(tfile, t_count, "t_count");
  sc_trace(tfile, t_error, "t_error");

  sc_start(70, SC_NS);

  sc_close_vcd_trace_file(tfile);
  return 0;
}
