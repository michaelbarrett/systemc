//alu.cpp
//
#include "alu.h"

//on pos clk edge: handles reading and arithmetic evaluation on the alu
void alu :: prc() {
  //data_src will be made either imm or r_src
  if (use_imm) { data_src = imm.read(); }
  else { data_src = r_src.read();  }
  //then possibly apply two's
  if (with_twos) { data_src *= -1; }

  //check which instruction is enabled. we will assume one instruction is enabled,
  //otherwise precedence is arbitrary.
  if (add.read()) { data_res = data_src + r_dest.read(); }
  else if (and_instr.read()) { data_res = data_src & r_dest.read(); }
  else if (or_instr.read()) { data_res = data_src | r_dest.read(); }
  else if (xor_instr.read()) { data_res = data_src ^ r_dest.read(); }
  else if (mov.read()) { data_res = data_src; }
  else if (lsh.read()) {
    if (data_src > 0 & data_src < 15) { unsigned(data_res) << data_src; }
    else if (data_src < 0 & data_src < 15) { unsigned(data_res) >> data_src; }
  }
  else if (ash.read()) {
    if (data_src > 0 & data_src < 15) { data_res << data_src; }
    else if (data_src < 0 & data_src < 15) { data_res >> data_src; }
  }

  //set flags
  //PSR: program status register
  //Z (zero) flag, N (negative), C (carry out), L (lower) flags
  if (data_res.read() == 0) { z_flag.write(true); }
  else { z_flag.write(false); }
  //N (negative) flag
  if (data_res.read() < 0) { n_flag.write(true); }
  else { n_flag.write(false); }
  //C (carry out) flag
  if (data_res.read() > 256) { c_flag.write(true); }
  else { c_flag.write(false); }
  //L (lower) flag
  if (data_res.read() < 0) { l_flag.write(true) }
  else { l_flag.write(false); }
  
  //set output register if set_oup_reg enabled
  if (set_oup_reg) { result.write(data_res); }
}
