#ifndef BASIC_TOP_H
#define BASIC_TOP_H
// -*- C++ -*- vim600:syntax=cpp:sw=2:tw=78
// COMMENT BLOCK <<////////////////////////////////////////////////////////////
//{:<COPYRIGHT>:}
//
// DESCRIPTION
//! \brief Top level connectivity for basic.
//
// {:LONG_DESCRIPTION:}
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
  // Processes - NONE
private:
  // Helper methods - NONE
  // Attributes - NONE
};//endMODULE Basic_top
#endif
///////////////////////////////////////////////////////////////////////////////
//END $Id$
