// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#ifndef MEDIAN_MOD_TB_H
#define MEDIAN_MOD_TB_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"
#include <tlm.h>
#include "tlm_utils/simple_initiator_socket.h"

SC_MODULE(Median_tb)
{
  sc_in<bool> clk;
  
  // Testbench Interface
  sc_out<bool> start;    // inidcates start of operation
  sc_in<bool>  finish;  // indicates that operation is finished

  // interface to image-memory of median module
  tlm_utils::simple_initiator_socket<Median_tb> mem_if;

  // Image Dimensions
  static const unsigned int width  = 100;
  static const unsigned int height = 100;
  
  void do_median_tb();
  void read_image_uut( unsigned char img[][height] );

  SC_CTOR(Median_tb) : mem_if("tb_memory_interface")
  {
    SC_THREAD(do_median_tb);
    sensitive << clk.pos();
  }
};

#endif // MEDIAN_MOD_TB_H
