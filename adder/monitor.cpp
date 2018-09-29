//=================================
// Function: Monitor
// File Name: monitor.cpp
//=================================
#include "monitor.h"

void monitor :: prc_driver() {
  cout << "At time " << sc_time_stamp() << "::";
  cout << "(a, b, carry_in): " << m_a << m_b << m_cin;
  cout << " sum, carry_out): " << m_sum << m_cout << endl;
}
}
