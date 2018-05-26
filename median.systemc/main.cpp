// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
// 
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
// 
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

// #include "median_top.h"
#include "median_module.h"
#include "memory.h"
#include "median_tb.h"

using namespace std;


int sc_main(int argc, char* argv[])
{
  sc_signal<bool> StartSig, FinishSig;

// a clock that has a positive edge only at 10 ns 
  sc_clock TestClk("TestClock", 10, SC_NS,0.5, 10, SC_NS);

  Median_tb TB1("Testbench");
  TB1.start(StartSig);
  TB1.finish(FinishSig);
  TB1.clk(TestClk); // Module Input Clock

  median_module DUT("DUT_MedianFilter");
  DUT.clk(TestClk);
  DUT.start(StartSig);
  DUT.finish(FinishSig);

  Memory DUT_MEM("DUT_ImgMem");
  // bind median-filter initiator to memory interface
  DUT.socket.bind( DUT_MEM.socket );

  // bind testbench initiator to median target
  TB1.mem_if.bind( DUT_MEM.socket_dbg );

  sc_start();  // run forever

  return 0;

}
