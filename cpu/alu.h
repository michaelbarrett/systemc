//alu.h
//ALU ~ Arithmetic Logic Unit module for simple RISC CPU ~ datapath
#include "systemc.h"

SC_MODULE(alu) {
  sc_in <bool> en;
  //control signals, from controller mux logic
  sc_in <bool> with_twos; //if asserted, do two's complement on inp Rsrc
  sc_in <bool> use_imm; //if asserted, imm val is used rather than Rsrc
  sc_in <bool> set_oup_reg; //if asserted, set the output register (off for cmp)
  //Instructions: 0: add/sub, 1: and, 2: or, 3: xor, 4: mov, 5: lsh, 6: ash
  sc_in <bool> add; //add or subtract
  sc_in <bool> and_instr; //bitwise and
  sc_in <bool> or_instr; //bitwise or
  sc_in <bool> xor_instr; //bitwise xor
  sc_in <bool> mov; //mov
  sc_in <bool> lsh; //+15/-15 range logical left shift
  //(or, with negative argument, a logical right shift)
  sc_in <bool> ash; //+15/-15 range arithmetic left shift
  //(or, with negative argument, a logical right shift)
  
  //data signals
  sc_in <int> imm, r_src, r_dest; //Imm, and Rsrc and Rdest from RF
  sc_out <int> result; //output to Rdest of RF
  //flags held in PSR, program status register
  sc_out <bool> z_flag;
  sc_out <bool> n_flag;
  sc_out <bool> c_flag;
  sc_out <bool> l_flag;
  
  int data_src;
  int data_res;

  void prc();

  SC_HAS_PROCESS(alu);

  alu(sc_module_name name) : sc_module(name) {
    SC_METHOD(prc);
    sensitive << with_twos << use_imm << set_oup_reg << add << and_instr << or_instr << xor_instr << mov << lsh << ash << imm << r_src << r_dest;
  }
};
