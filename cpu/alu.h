//alu.h
//ALU ~ Arithmetic Logic Unit module
#include "systemc.h"

SC_MODULE(alu) {
  //control signals
  sc_in <bool> with_twos; //if asserted, do two's complement on inp Rsrc
  sc_in <bool> use_imm; //if asserted, imm val is used rather than Rsrc
  sc_in <bool> set_oup_reg; //if asserted, set the output register (off for cmp)
  //num_instr: 0 = add/sub, 1 = and, 2 = or, 3 = xor, 4 = mov, 5 = lsh, 6 = ash
  sc_in <int> num_instr;
  
  //data signals
  sc_in <int> imm, r_src, r_dest; //Imm, and Rsrc and Rdest from RF
  sc_out <int> result; //output to Rdest of RF
  
  int data_src;
  int data_res;

  SC_HAS_PROCESS(alu);
  SC_HAS_PROCESS(prc);

  alu(sc_module_name name) : sc_module(name) {
    SC_METHOD(prc);
    sensitive << clock.pos();
  }
}
