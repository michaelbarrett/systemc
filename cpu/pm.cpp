//pm.cpp
//Program Memory Module cpp
#include "pm.h"

void program_memory :: prc() {
  if (en) {
    if (addr.read() < MEM_SIZE_PM) {
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
