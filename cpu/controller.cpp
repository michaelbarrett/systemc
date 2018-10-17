//controller.cpp
//Controller cpp
#include "controller.h"

//IF, instruction fetch ~ reads from program memory from PC address
//and places instruction into IR
void prc_if :: controller() {
  //pm has int addr, out d_out; pm is read-only
  addr_to_pm.write(pc); //set the address of the PM
  //...make sure the output has been set? should this be comb in pm?
  ir = instr_from_pm.read(); //read to ir from pm
}

//RD, decode ~ looks at the opcode of the instruction in IR and translates
//to ALU control signals which are sent to ALU
void controller :: prc_rd() {
  with_twos_to_alu.write(false);
  use_imm_to_alu.write(false);
  set_oup_reg_to_alu.write(true);
  add_to_alu.write(false);
  and_instr_to_alu.write(false);
  or_instr_to_alu.write(false);
  xor_instr_to_alu.write(false);
  mov_instr_to_alu.write(false);
  lsh_instr_to_alu.write(false);
  ash_instr_to_alu.write(false);
  en_to_alu.write(false);

  opcode = ir & 0xF000; // ir & 1111 0000 0000 0000 gets opcode
  r_dest = ir & 0x0F00; // ir & 0000 1111 0000 0000 -> alu
  op_ext = ir & 0x00F0; // ir & 0000 0000 1111 0000
  r_src  = ir & 0x000F; // ir & 0000 0000 0000 1111 -> alu
  imm    = ir & 0x00FF; // ir & 0000 0000 1111 1111 -> alu
  switch (opcode) {
  case 0b0000: //0000
    if (op_ext == 0b0101){//ADD
      add_to_alu.write(true);
    }
    else if (op_ext == 0b1001){//SUB
      add_to_alu.write(true);
      with_twos_to_alu.write(true);
    }	
    else if (op_ext == 0b1011){//CMP
      add_to_alu.write(true);
      with_twos_to_alu.write(true);
      set_oup_reg_to_alu.write(false);
    }
    else if (op_ext == 0b0001){//AND
      and_instr_to_alu.write(true);
    }
    else if (op_ext == 0b0010){//OR
      or_instr_to_alu.write(true);
    }
    else if (op_ext == 0b0011){//XOR
      xor_instr_to_alu.write(true);
    }
    else if (op_ext == 0b1101){//MOV
      mov_instr_to_alu.write(true);
    }
    break;
  case 0b0101: //ADDI
    add_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;

  case 0b1001: //SUBI
    add_to_alu.write(true);
    use_imm_to_alu.write(true);
    with_twos_to_alu.write(true);
    break;

  case 0b1011: //CMPI
    add_to_alu.write(true);
    with_twos_to_alu.write(true);
    use_imm_to_alu.write(true);	
    set_oup_reg_to_alu.write(false);
    break;

  case 0b0001: //ANDI
    and_instr_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;

  case 0b0010: //ORI
    or_instr_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;

  case 0b0011: //XORI
    xor_instr_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;

  case 0b1101: //MOVI
    mov_instr_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;

  case 0b1000:
    if (op_ext == 0b0100){ //LSH
      lsh_instr_to_alu.write(true);
    }
    else if (op_ext == 0b0000 || opo_ext == 0b0001){ //LSHI
      lsh_instr_to_alu.write(true);
      use_imm_to_alu.write(true);
    }
    else if (op_ext == 0b0110){ //ASH
      ash_instr_to_alu.write(true);
    }
    else if (op_ext == 0b0010 || 0b0011){ //ASHI
      ash_instr_to_alu.write(true);
      use_imm_to_alu.write(true);
    }
    break;
  case 0b1111: //LUI
    lsh_instr_to_alu.write(true);
    use_imm_to_alu.write(true);
    break;
  case 0b0100:
    if (op_ext == 0b0000){ //LOAD
      //This is handled by the PRC_MEM stage
    }
    else if (op_ext == 0b0100){ //STOR
      //This is handled by the PRC_MEM stage
    }
    break;
  case 0b1100: //BCOND
    break;
  }
}

//EXE, ALU execute ~ sets the inputs to the ALU so that the operation is performed
void prc_exe :: controller() {
  r_dest = ir & 0x0F00; // ir & 0000 1111 0000 0000 -> alu
  r_src  = ir & 0x000F; // ir & 0000 0000 0000 1111 -> alu
  imm    = ir & 0x00FF; // ir & 0000 0000 1111 1111 -> alu
  
  en_to_alu.write(true);
  //read r_dest and r_src from rf
  rw_to_rf.write(false); //reading from rf
  addr1_to_rf.write(r_dest);
  addr2_to_rf.write(r_src);
  //writing to alu
  rd_to_alu.write(data1_from_rf.read());
  rs_to_alu.write(data2_from_rf.read());
  imm_to_alu.write(imm);
}

//MEM, memory access ~ loads data from memory to regfile if op is load
//or stores data from regfile to memory if op is store
void prc_mem :: controller() {
  int opcode, r_data, op_ext, r_addr;
  opcode = ir & 0xF000; // ir & 1111 0000 0000 0000 gets opcode
  regist = ir & 0x0F00; // ir & 0000 1111 0000 0000
  op_ext = ir & 0x00F0; // ir & 0000 0000 1111 0000
  r_addr = ir & 0x000F; // ir & 0000 0000 0000 1111
  if (opcode == 0x4) { //0100 ~ load or store
    if (op_ext == 0x0) { //load from dm into rf
      rw_to_dm.write(false); //reading from dm into rf
      addr_to_dm.write(r_addr);
      rw_to_rf.write(true); //writing to rf
      addr1_to_rf.write(regist);
      d_in_to_rf.write(data_from_dm.read()); //store read data in rf
    }
    else if (op_ext == 0x4) { //store from rf into dm
      rw_to_rf.write(false); //reading from rf
      addr1_to_rf.write(regist);
      //now write this to dm
      rw_to_dm.write(true); //writing to dm
      addr_to_dm.write(r_addr);
      d_in_to_dm.write(data1_from_rf.read()); //store read data in dm
    }
  }
}

//WB, write ~ writes the result to the regfile rd destination ~ for ALU operations
void prc_wb :: controller() {
  opcode = ir & 0xF000; // ir & 1111 0000 0000 0000 gets opcode
  r_dest = ir & 0x0F00; // ir & 0000 1111 0000 0000 gets reg destination
  if (opcode != 0x4 &&   //if not load, store,
      opcode != 0xC &&   //branch,
      opcode != 0xB &&   //cmp,
      opcode != 0x8) {   //or jump -- then write to rdest from alu result
    rw_to_rf.write(true); //writing to rf
    addr_to_rf.write(r_dest);
    d_in_to_rf.write(result_from_alu.read());
  }
  pc++; //increment program counter so the next instr can be read and operated on
}
