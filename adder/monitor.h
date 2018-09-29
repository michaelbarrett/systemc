//=================================
// Function: Monitor
// File Name: monitor.h
//=================================
#include "systemc.h"

SC_MODULE (monitor) {
  sc_in <sc_logic> m_a, m_b, m_cin, m_sum, m_count;

  //----------------Internal variables-----------------

  //----------------Methods-----------------
  void prc_monitor();

  //----------------Constructor-----------------
  SC_CTOR(driver) {
    SC_METHOD (prc_monitor);
    sensitive << m_a << m_b << m_cin << m_sum << m_cout;
  }
};
