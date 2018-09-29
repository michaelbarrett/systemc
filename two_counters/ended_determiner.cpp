//ended_determiner.cpp
//ended is written if the counters have the same count, or if one of them overflows
#include "ended_determiner.h"

void ended_determiner :: prc_ended_determiner() {
  if (ed_count1.read() == ed_count2.read()) {
    ended.write(true);
  }
  else if (ed_overflow1.read() | ed_overflow2.read()) {
    ended.write(true);
  }
  else {
    ended.write(false);
  }

  if (ended.read() & (load1 | load2)) {
    ended.write(false);
  }
  
  //ended.write(ended_signal); //output ended -- No more signal
}

void ended_determiner :: prc_hold_determiner() {
  //logic:
  //if ended and neither load is asserted, then we hold
  //if ended and either load is asserted, then turn off ended (moved to ended det.)
  //if not ended, turn off hold
  if (ended.read() & (!(load1 | load2))) {
    hold.write(true); //output hold
  }
  else if (!ended.read()) {
    hold.write(false); //output hold
  }
}
