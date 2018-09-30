//rf.cpp
#include "rf.h"

void register_file :: prc() {
  //if enabled and writing -- use addr1 for writing in RF
  if (en & rw) {
    if (addr1.read() < MEM_SIZE) {
      _data[addr1.read()] = d_in;
    }
    else {
      cout << "address" << addr1 << "is out of bounds for writing" << endl;
    }
  }
  //if enabled and reading -- read both registers from both addresses
  else if (en & !rw) {
    if (addr1.read() < MEM_SIZE & addr2.read() < MEM_SIZE) {
      d_out1.write(_data[addr1.read()]);
      d_out2.write(_data[addr2.read()]);
    }
    else {
      cout << "addresses" << addr1 << " and " << addr2
	   << "are out of bounds for reading" << endl;
    }
  }
}
