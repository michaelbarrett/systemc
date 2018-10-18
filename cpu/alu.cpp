//alu.cpp
#include "alu.h"

//on pos clk edge: handles reading and arithmetic evaluation on the alu
void alu :: prc() {
  if (en) {
  
    //data_src will be made either imm or r_src
    if (use_imm) { data_src = imm.read(); }
    else { data_src = r_src.read();  }
    //then possibly apply two's
    if (with_twos) { data_src *= -1; }

    //check which instruction is enabled. we will assume one instruction is enabled,
    //otherwise precedence is arbitrary.
    if (add.read()) { data_res = data_src + r_dest.read();
      cout << "ALU ADD OP: add " << data_src << " data_src + " << r_dest.read() << " r_dest to produce " << data_res << endl;
    }
    else if (and_instr.read()) { data_res = data_src & r_dest.read();
      cout << "ALU BITWISE AND OP: and " << data_src << " data_src with " << r_dest.read() << " r_dest to produce " << data_res << endl;
    }
    else if (or_instr.read()) { data_res = data_src | r_dest.read();
      cout << "ALU BITWISE OR OP: or " << data_src << " data_src with " << r_dest.read() << " r_dest to produce " << data_res << endl;
    }
    else if (xor_instr.read()) { data_res = data_src ^ r_dest.read();
      cout << "ALU BITWISE XOR OP: xor " << data_src << " data_src with " << r_dest.read() << " r_dest to produce " << data_res << endl;
    }
    else if (mov.read()) { data_res = data_src;
      cout << "ALU MOV: mov " << data_src;
    }
    else if (lsh.read()) {
      if (data_src > 0 & data_src < 15) { unsigned(data_res) << data_src; }
      else if (data_src < 0 & data_src < 15) { unsigned(data_res) >> data_src; }
      cout << "ALU LSH" << endl;
    }
    else if (ash.read()) {
      if (data_src > 0 & data_src < 15) { data_res << data_src; }
      else if (data_src < 0 & data_src < 15) { data_res >> data_src; }
      cout << "ALU ASH" << endl;
    }

    //set output register if set_oup_reg enabled
    if (set_oup_reg) { result.write(data_res); }

  }

    //set flags
    //PSR: program status register
    //Z (zero) flag, N (negative), C (carry out), L (lower) flags
    if (data_res == 0) { z_flag.write(true); }
    else { z_flag.write(false); }
    //N (negative) flag
    if (data_res < 0) { n_flag.write(true); }
    else { n_flag.write(false); }
    //C (carry out) flag
    if (data_res > 256) { c_flag.write(true); }
    else { c_flag.write(false); }
    //L (lower) flag
    if (data_res < 0) { l_flag.write(true); }
    else { l_flag.write(false); }
}
