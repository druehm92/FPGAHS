//----------------------------------------------------------------------
//  Copyright (c) 2007-2008 by Doulos Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 2  16-June-2008 - updated for TLM-2.0
// Version 3  18-June-2008 - updated for TLM-2.0
// Version 4  12-Jan-2009  - fix bug in transport_dbg
// Version 5  26-Sep-2009  - fix bug with set_end_address

// Getting Started with TLM-2.0, Tutorial Example 1 - 3

// For a full description, see http://www.doulos.com/knowhow/systemc/tlm2

//----------------------------------------------------------------------
// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>


#ifndef MEMORY_MOD_H
#define MEMORY_MOD_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc.h"

#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"

#include "median_module.h"

SC_MODULE(Memory)
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;
  tlm_utils::simple_target_socket<Memory> socket_dbg;

  // Image Dimensions
  static const unsigned int width  = 100;
  static const unsigned int height = 100;

  void do_memory();

  // read/write functions (normal protocol and debug interface)
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay );

  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);


  enum { SIZE = (width * height) };

  SC_CTOR(Memory)
  : socket("socket"), socket_dbg("socket_tb")
  {
  	do_memory();
  }

  char mem[SIZE];
};

#endif // MEMORY_MOD_H
