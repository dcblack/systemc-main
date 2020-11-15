#ifndef TOP_HPP
#define TOP_HPP
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
struct Top
: sc_core::sc_module
{
  // Ports - NONE
  // Constructor
  explicit Top(sc_core::sc_module_name instance_name);
  // Destructor
  ~Top() override;
  // Overrides
  void before_end_of_elaboration() override;
  void end_of_elaboration() override;
  void start_of_simulation() override;
  void end_of_simulation() override;
  // Processes
  void Basic_thread();
private:
  // Helper methods - NONE
  // Attributes - NONE
};//endMODULE Top
#endif
///////////////////////////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
//END $Id$
