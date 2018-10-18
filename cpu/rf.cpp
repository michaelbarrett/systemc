//rf.cpp
#include "rf.h"

void register_file :: prc_read() {
//if enabled and reading -- read both registers from both addresses
  cout << "RF: Starting READ prc, en is: " << en << " and rw is " << rw << endl;
  if (!en & !rw) {
    if ((addr1.read() < MEM_SIZE_RF) & (addr2.read() < MEM_SIZE_RF)) {
      d_out1.write(_data[addr1.read()]);
      d_out2.write(_data[addr2.read()]);
      /*cout << "RF DATA READ: " << _data[addr1.read()] << " and " << _data[addr2.read()] << endl;*/
    }
    else {
      cout << "addresses " << addr1 << " and " << addr2
	   << " are out of bounds for reading" << endl;
    }
  }
}

void register_file :: prc_write() {
  //if enabled and writing -- use addr1 for writing in RF
  cout << "RF: Starting WRITE prc, en is: " << en << " and rw is " << rw << endl;
  if (!en & rw) {
    if (addr1.read() < MEM_SIZE_RF) {
      _data[addr1.read()] = d_in;
      cout << "RD WROTE DATA: " << _data[addr1.read()] << " TO ADDRESS " << addr1.read() << endl;
    }
    else {
      cout << "address " << addr1 << "is out of bounds for writing " << endl;
    }
  }
}


