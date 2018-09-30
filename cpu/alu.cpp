//alu.cpp
//
#include "alu.h"

//on pos clk edge: handles reading and arithmetic evaluation on the alu
void alu :: prc_read_eval() {
  //data_src will be made either imm or r_src
  if (use_imm) { data_src = imm.read(); }
  else { data_src = r_src.read();  }
  //then possibly apply two's
  if (with_twos) { data_src *= -1; }

  //check which instruction is enabled. we will assume one instruction is enabled,
  //otherwise precedence is arbitrary.
  if (add.read()) { data_res = data_src + r_dest.read(); }
  else if (and.read()) { data_res = data_src & r_dest.read(); }
  else if (or.read()) { data_res = data_src | r_dest.read(); }
  else if (xor.read()) { data_res = data_src ^ r_dest.read(); }
  else if (mov.read()) { data_res = data_src; }
  else if (lsh.read()) {
    if (data_src > 0 & data_src < 15) { unsigned(data_res) << data_src; }
    else if (data_src < 0 & data_src < 15) { unsigned(data_res) >> data_src; }
  }
  else if (ash.read()) {
    if (data_src > 0 & data_src < 15) { data_res << data_src; }
    else if (data_src < 0 & data_src < 15) { data_res >> data_src; }
  }
}

//on neg clk edge: handles writing to flags and outputs on the alu
void alu :: prc_write() {
  //set flags
  //PSR: program status register
  //Z (zero), N (negative), C (carry out), L (lower) flags
  

  //set output register if set_oup_reg enabled
  if (set_oup_reg) { result.write(data_res); }
}
