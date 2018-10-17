//main.cpp
#include "driver.h"
#include "dm.h"
#include "pm.h"
#include "controller.h"
#include "alu.h"

int sc_main(int argc, char* argv[]) {
  //ports decl (communication)
  sc_signal <bool> t_z_flag, t_n_flag, t_c_flag, t_l_flag; //flags
  sc_signal <bool> t_instr_from_pm, t_addr_to_pm; //pm-to-ctrl
  sc_signal <bool> t_with_twos_to_alu, t_use_imm_to_alu, t_set_oup_reg_to_alu, t_add_to_alu, t_and_instr_to_alu, t_or_instr_to_alu, t_xor_instr_to_alu, t_mov_to_alu, t_lsh_to_alu, t_ash_to_alu, t_en_to_alu; //ctrl-to-alu control
  sc_signal <bool> t_result_from_alu, t_rd_to_alu, t_rs_to_alu, t_imm_to_alu; //alu
  sc_signal <bool> t_data_from_dm, t_addr_to_dm, t_d_in_to_dm; //ctrl-to-dm
  sc_signal <bool> t_data_from_rf, t_rs_to_rf, t_rd_to_rf; //ctrl-to-rf
  //clock to feed modules
  sc_clock c1 ("c1", 5, SC_NS);

  //module instantiation
  int programMemory[256] = { /* Program here */
			    0b0000000101010010} ; //add r1, r2
  int dataMemory[256] = { 0 };
  int registerFile[256] = { 0, 1, 2 };

  pm pm1("pm1", &programMemory); //PM
  dm dm1("dm1", &dataMemory); //DM
  rf rf1("rf1", &registerFile); //RF
  alu alu1("alu1"); //ALU
  controller controller1("controller1"); //Controller

  //trace file definition
  sc_trace_file *tfile = sc_create_vcd_trace_file("communications");
  
  //association
  //PM
  pm1.addr(t_addr_pm);
  pm1.d_out(t_instr_pm);
  //DM
  dm1.rw(); //rw should be controlled!!
  dm1.d_in(t_d_in_to_dm);
  dm1.addr(t_addr_to_dm);
  dm1.d_ou(t_data_from_dm);
  //RF (are we setting these correctly?)
  rf1.rw(); //rw should be controlled!!
  rf1.addr1(t_rd_to_rf);
  rf1.addr2(t_rs_to_rf);
  rf1.d_in(t_result_from_alu); //??
  rf1.d_out1(t_data_from_rf);
  rf1.d_out2(); //!!
  //ALU //control sigs
  alu1.with_twos(t_with_twos_to_alu);
  alu1.use_imm(t_use_imm_to_alu);
  alu1.set_oup_reg(t_set_oup_reg_to_alu);
  alu1.add(t_add_to_alu);
  alu1.and_instr(t_and_instr_to_alu);
  alu1.or_instr(t_or_instr_to_alu);
  alu1.xor_instr(t_xor_instr_to_alu);
  alu1.mov(t_mov_to_alu);
  alu1.lsh(t_lsh_to_alu);
  alu1.ash(t_ash_to_alu);
  //data
  alu1.r_src(t_rs_to_alu);
  alu1.r_dest(t_rd_to_alu);
  alu1.imm(t_imm_to_alu);
  alu.result(t_result_from_alu);
  //Controller //flags
  controller1.z_flag(t_z_flag);
  controller1.n_flag(t_n_flag);
  controller1.c_flag(t_c_flag);
  controller1.l_flag(t_l_flag);
  //control sigs
  controller1.instr_from_pm(t_instr_from_pm);
  controller1.addr_to_pm(t_addr_to_pm);
  controller1.with_twos_to_alu(t_with_two_to_alu);
  controller1.use_imm_to_alu(t_use_imm_to_alu);
  controller1.set_oup_reg_to_alu(t_set_oup_reg_to_alu);
  controller1.add_to_alu(t_add_to_alu);
  controller1.add_instr_to_alu(t_add_instr_to_alu);
  controller1.or_instr_to_alu(t_or_instr_to_alu);
  controller1.xor_instr_to_alu(t_xor_instr_to_alu);
  controller1.mov_instr_to_alu(t_mov_to_alu);
  controller1.lsh_instr_to_alu(t_lsh_to_alu);
  controller1.ash_instr_to_alu(t_ash_to_alu);
  controller1.en_to_alu(t_en_to_alu);
  //to and from alu
  controller1.result_from_alu(t_result_from_alu);
  controller1.rd_to_alu(t_rd_to_alu);
  controller1.rs_to_alu(t_rs_to_alu);
  controller1.imm_to_alu(t_imm_to_alu);
  //to and from dm
  controller1.data_from_dm(t_data_from_dm);
  controller1.addr_to_dm(t_addr_to_dm);
  controller1.d_in_to_dm(t_d_in_to_dm);
  //to and from rf
  controller1.data_from_rf(t_data_from_rf);
  controller1.t_rs_to_rf(t_rs_to_rf);
  controller1.t_rd_to_rf(t_rd_to_rf);
  //to and from pm
  controller1.instr_from_pm(t_instr_from_pm);
  controller1.addr_to_pm(t_addr_to_pm);

  //signal trace
  sc_trace(tfile, c1, "c1");

  sc_start(70, SC_NS);

  sc_close_vcd_trace_file(tfile);
  return 0;
}
