#ifndef BASIC_TOP_HPP
#define BASIC_TOP_HPP
// -*- C++ -*- vim600:syntax=cpp:sw=2:tw=78
// COMMENT BLOCK <<////////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
//
// DESCRIPTION
//! \brief Top level connectivity for basic.
//
// This is part of a more extensive example for coding SystemC
// main.cpp and the top-level. See also README.md.
//
////////////////////////////////////////////////////////////////////////////>>/
#include <systemc>
struct Basic_top
: sc_core::sc_module
{
  // Ports - NONE
  // Constructor
  Basic_top(sc_core::sc_module_name instance_name);
  // Destructor
  virtual ~Basic_top(void);
  // Overrides
  void before_end_of_elaboration(void);
  void end_of_elaboration(void);
  void start_of_simulation(void);
  void end_of_simulation(void);
  // Processes
  void Basic_thread(void);
private:
  // Helper methods - NONE
  // Attributes - NONE
};//endMODULE Basic_top
#endif
///////////////////////////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
//END $Id$
