//controller.h
//Controller ~ control unit module for simple RISC CPU
#include "systemc.h"

SC_MODULE(controller) {
  sc_in <bool> clock;
  //flag inputs needed for conditional branch operation
  sc_in <bool> z_flag;
  sc_in <bool> n_flag;
  sc_in <bool> c_flag;
  sc_in <bool> l_flag;

  //to and from PM
  sc_in <int> instr_from_pm;
  sc_out <int> addr_to_pm;

  //to ALU (control signals)
  sc_out <bool> with_twos_to_alu;
  sc_out <bool> use_imm_to_alu;
  sc_out <bool> set_oup_reg_to_alu;
  sc_out <bool> add_to_alu;
  sc_out <bool> and_instr_to_alu;
  sc_out <bool> or_instr_to_alu;
  sc_out <bool> xor_instr_to_alu;
  sc_out <bool> mov_to_alu;
  sc_out <bool> lsh_to_alu;
  sc_out <bool> ash_to_alu;
  sc_out <bool> en_to_alu;

  //to and from ALU (data)
  sc_in <int> result_from_alu;
  sc_out <int> rd_to_alu;
  sc_out <int> rs_to_alu;
  sc_out <int> imm_to_alu;

  //to and from DM ~ rw
  sc_in <int> data_from_dm;
  sc_out <int> addr_to_dm;
  sc_out <int> d_in_to_dm;
  sc_out <int> rw_to_dm;

  //to and from RF ~ rw
  sc_in <int> data1_from_rf;
  sc_int <int> data2_from_rf;
  sc_out <int> addr1_to_rf;
  sc_out <int> addr2_to_rf;
  sc_out <int> d_in_to_rf;
  sc_out <int> rw_to_rf;

  int ir = 0; //instruction register (init = 0)
  int pc = 0; //program counter (init = 0)
  int control = 0;

  int mem_result; //result of memory op
  
  SC_HAS_PROCESS(controller);

 controller(sc_module_name name) : sc_module(name) {
    SC_METHOD(prc_if);
    sensitive << clock.pos();
    SC_METHOD(prc_rd);
    sensitive << clock.pos();
    SC_METHOD(prc_exe);
    sensitive << clock.pos();
    SC_METHOD(prc_mem);
    sensitive << clock.pos();
    SC_METHOD(prc_wb);
    sensitive << clock.neg();
  }
}
