//dm.cpp
//Data Memory Module cpp
#include "dm.h"

void data_memory :: prc() {
  //if enabled and writing
  if (en & rw) {
    //we look at the address and the data input and based on this change local _data
    //data array _data can be any length, it is supplied in module instantiation
    if (addr.read() < MEM_SIZE_DM) {
      _data[addr.read()] = d_in;
    }
    else {
      cout << "address" << addr << "is out of range for writing" << endl;
    }
  }
  //if enabled and reading
  else if (en & !rw) {
    if (addr.read() < MEM_SIZE_DM) {
      d_out.write(_data[addr.read()]);
    }
    else {
      cout << "address" << addr << "is out of range for reading" << endl;
    }
  }
  //if disabled
  else {
    //do nothing
  }
}
