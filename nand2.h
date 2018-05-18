#pragma once

#include "systemc.h"
SC_MODULE(nand2)          // declare nand2 sc_module
{
  sc_in<bool> A, B;       // input signal ports
  sc_out<bool> F;         // output signal ports
  //sc_in<bool> clk;
  //sc_in< sc_uint<1> > a,b;

  void do_nand2()         // a C++ function
  {

    F.write(!(A.read() && B.read()));

	// TODO: put your implementation here

  }

  SC_CTOR(nand2)          // constructor for nand2
  {
    SC_METHOD(do_nand2);  // register do_nand2 with kernel
    sensitive << A << B;  // sensitivity list
    //sensitive << clk.pos();
  }
};
