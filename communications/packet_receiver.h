//packet_receiver.h
#include "systemc.h"

SC_MODULE(packet_receiver) {
  //inputs: clock, reset (active low), clear (active high), in_data
  //in_data: first 4 bits are header/type, next 4 are payload, last one is parity
  //the parity bit is '1' if the data payload is meant to be even parity
  sc_in <bool> clock, reset, clear;
  sc_in <sc_bv<12> > in_data;
  sc_bv<12> var_in_data;
  //outputs
  //all outputs are registered and cleared when 'reset' is low or 'clear' is high
  sc_out <sc_bv<4> > payload; //is changed to contain the data payload for type 1
  sc_out <sc_bv<8> > count; //running count of type 1 datas (header denotes 1)
  sc_out <sc_bv<8> > error; //running count of type 1 datas w incorrect parity

  //internal variables
  sc_uint<8> var_count;
  sc_uint<8> var_error;
  
  //methods
  void prc_packet_receiver(); //synchronous part
  void prc_output(); //combinational part

  SC_CTOR(packet_receiver) {
    SC_METHOD(prc_packet_receiver);
    sensitive << clock.pos() << reset;
    SC_METHOD(prc_output);
    sensitive << clear << clock.pos();
  }
};
