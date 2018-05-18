#pragma once

#include "systemc.h"
#include "nand2.h"

// TODO: implement EXOR module here using only nand2 components
// inputs: bool A, B
// output bool F

SC_MODULE(exor2)          // declare nand2 sc_module
{
  sc_in<bool> A, B;       // input signal ports
  sc_out<bool> F;         // output signal ports
  //sc_in<bool> clk;
  //sc_in< sc_uint<1> > a,b;

  nand2 n1,n2,n3,n4;
  sc_signal<bool> S1,S2,S3;

  SC_CTOR(exor2) :n1("N1"), n2("N2"), n3("N3"), n4("N4")          // constructor for nand2
  {
      //1.NAND Gate
      n1.A(A);
      n1.B(B);
      n1.F(S1);

      //2.NAND Gate
      n2.A(A);
      n2.B(S1);
      n2.F(S2);

      //3.NAND Gate
      n3.A(S1);
      n3.B(B);
      n3.F(S3);

      //4.NAND Gate
      n4.A(S2);
      n4.B(S3);
      n4.F(F);
  }
};
