//BEGIN basic_top.cpp (systemc)
// -*- C++ -*- vim600:syntax=cpp:sw=2:tw=78:fmr=<<<,>>>
// COMMENT BLOCK <<<///////////////////////////////////////////////////////////
//{:<COPYRIGHT>:}
// 
// DESCRIPTION
//! \brief Top level connectivity for 'basic'.
//
// {:LONG_DESCRIPTION:}
//
////////////////////////////////////////////////////////////////////////////>>>
#include "basic_top.h"
#include "report.h"
using namespace sc_core;
namespace {
  const char* const MSGID="/Doulos Inc/{:PRODUCT:}/basic_top";
  const char* const RCSID="/$Id$";
}

////////////////////////////////////////////////////////////////////////////>>/
// Constructor <<
Basic_top::Basic_top(sc_module_name instance_name)
: sc_module(instance_name)
//, {:OBJECT_CONSTRUCTION:}
{
  SC_REPORT_ERROR(MSGID,"{:REPLACE_HERE_BELOW\n"
      "\n\n"
      "###############################################################\n"
      "###############################################################\n"
      "##                                                           ##\n"
      "##   REPLACE THIS ERROR MESSAGE AND ANY OTHER PLACEHOLDERS   ##\n"
      "##   SURROUNDED BY {: :} PAIRS YOU FIND IN THIS SOURCEFILE   ##\n"
      "##   WITH YOUR CODE. DELETE UNUSED PLACEHOLDERS.             ##\n"
      "##                                                           ##\n"
      "###############################################################\n"
      "###############################################################\n"
      "\n\n"
  "REPLACE_HERE_ABOVE:}\n");
  // Connectivity
  /*{:To_be_supplied:}*/
  // No processes
}//endconstructor

////////////////////////////////////////////////////////////////////////////>>/
// Destructor <<
Basic_top::~Basic_top(void) {
}

////////////////////////////////////////////////////////////////////////////>>/


///////////////////////////////////////////////////////////////////////////////
//{:<?COPYRIGHT>:}
//END $Id$
