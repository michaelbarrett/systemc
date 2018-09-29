//alu.cpp
//
#include "alu.h"

void alu :: prc() {
  //data_src will be made either imm or r_src
  if (use_imm) { data_src = imm.read(); }
  else { data_src = r_src.read();  }
  //then possibly apply two's
  if (with_twos) { data_src *= -1; }
  
  switch(num_instr.read()) {
  case 0:
    //add
    data_res = data_src + r_dest.read();
    break;
  case 1:
    //and
    data_res = data_src & r_dest.read();
    break;
  case 2:
    //or
    data_res = data_src | r_dest.read();
    break;
  case 3:
    //xor
    data_res = data_src ^ r_dest.read();
    break;
  case 4:
    //mov
    data_res = data_src;
    break;
  case 5:
    //lsh
    if (data_src > 0 & data_src < 15) { unsigned(data_res) << data_src; }
    else if (data_src < 0 & data_src < 15) { unsigned(data_res) >> data_src; }
    break;
  case 6:
    //ash
    if (data_src > 0 & data_src < 15) { data_res << data_src; }
    else if (data_src < 0 & data_src < 15) { data_res >> data_src; }
    break;
  }

  //set flags

  //set output register if set_oup_reg enabled
  if (set_oup_reg) { result.write(data_res); }
}
