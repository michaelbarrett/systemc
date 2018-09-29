//=================================
// Function: Full Adder
// File Name: full_adder.h
//=================================
#include "half_adder.h"

SC_MODULE (full_adder) {
  sc_in <sc_bit> a, b, carry_in;
  sc_out <sc_bit> sum;
  sc_out <sc_bit> carry_out;
  sc_signal <sc_bit> c1, s2, s1; //local ports

  //----------------Internal Variables-----------------

  //----------------Methods-----------------
  void prc_or();

  //----------------Constructor-----------------
  //the full adder consists of two half adders, one or gate, and interconnections
  half_adder *ha1_ptr, *ha2_ptr; //instantiation of half adders

  SC_CTOR(full_adder) {
    ha1_ptr = new half_adder("ha1");
    ha2_ptr = new half_adder("ha2");

    //named associations (interconnections)
    //looks wrong???
    ha1_ptr->a(a);
    ha2_ptr->b(b);
    ha1_ptr->sum(s1);
    ha1_ptr->carry(c1); 
    
    //positional associations
    (*ha2_ptr) (s1, carry_in, sum, c2);

    SC_METHOD(prc_or);
    sensitive << c1 << c2;
  }

  //----------------Destructor-----------------
  ~full_adder() {
    delete ha1_ptr; //free up memory
    delete ha2_ptr;
  }
};
