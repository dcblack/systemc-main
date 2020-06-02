//BEGIN basic_top.cpp (systemc)
// -*- C++ -*- vim600:syntax=cpp:sw=2:tw=78:fmr=<<<,>>>
// COMMENT BLOCK <<<///////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
// 
// DESCRIPTION
//! \brief Top level connectivity for 'basic'.
//
// This is part of a more extensive example for coding SystemC
// main.cpp and the top-level. See also README.md.
//
////////////////////////////////////////////////////////////////////////////>>>
#include "basic_top.hpp"
#include "report.hpp"
#include <cstdlib>
using namespace sc_core;
using namespace std;

namespace {
  const char* const MSGID="/Doulos Inc/SystemC-Example/basic_top";
  const char* const RCSID="/$Id$";
  void parse_command_line( void );
}

////////////////////////////////////////////////////////////////////////////>>/
// Constructor <<
Basic_top::Basic_top(sc_module_name instance_name)
: sc_module(instance_name)
//, {:OBJECT_CONSTRUCTION:}
{
  // Connectivity
  /*{:To_be_supplied:}*/
  // Processes
  SC_HAS_PROCESS(Basic_top);
  SC_THREAD(Basic_thread);
  REPORT(INFO,"Constructed " << name());
}//endconstructor

////////////////////////////////////////////////////////////////////////////>>/
// Destructor <<
Basic_top::~Basic_top(void) {
  REPORT(INFO,"Destroyed " << name());
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::before_end_of_elaboration(void)
{
  REPORT(INFO,"Before end of elaboration");
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::end_of_elaboration(void)
{
  REPORT(INFO,"End of elaboration");
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::start_of_simulation( void )
{
  REPORT(INFO,"Start of simulation");
  parse_command_line();
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::end_of_simulation(void)
{
  REPORT(INFO,"End of simulation");
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::Basic_thread( void )
{
  wait(42,SC_SEC);
  sc_stop();
}

////////////////////////////////////////////////////////////////////////////>>/
namespace {
  void parse_command_line( void )
  {
    bool inject_warning( false );
    bool inject_error( false );
    bool inject_fatal( false );
    bool test_reporting( false );

    for ( int i = 1; i < sc_argc(); ++i ) {
      string arg( sc_argv()[i] );

      if ( arg == "-test" ) {
          INFO(ALWAYS,"Testing");
          test_reporting = true;
      } else if ( arg == "-verbosity" ) {
        if( i == sc_argc() ) {
          REPORT(WARNING,"Ignoring -verbosity missing an argument");
          continue;
        }
        arg = string(sc_argv()[++i]);
        INFO(ALWAYS,"Setting verbosity " << arg);
        if ( arg == "none" ) {
          sc_report_handler::set_verbosity_level( SC_NONE );
        }
        else if ( arg == "low" ) {
          sc_report_handler::set_verbosity_level( SC_LOW );
        }
        else if ( arg == "medium" ) {
          sc_report_handler::set_verbosity_level( SC_MEDIUM );
        }
        else if ( arg == "high" ) {
          sc_report_handler::set_verbosity_level( SC_HIGH );
        }
        else if ( arg == "debug" ) {
          sc_report_handler::set_verbosity_level( SC_DEBUG );
        }
        else {
          REPORT( WARNING, "Ignoring unknown verbosity: '" << arg << "'!?" );
        }
      }
      else if ( arg == "-debug" ) {
        sc_report_handler::set_verbosity_level( SC_DEBUG );
        INFO( ALWAYS,"Debugging" );
      }
      else if ( arg == "-inject" ) {
        if( i == sc_argc() ) {
          REPORT( WARNING, "Ignoring -inject missing an argument" );
          continue;
        }
        arg = string(sc_argv()[++i]);
        INFO( ALWAYS,"Injecting " << arg );
        if ( arg == "warning" ) {
          inject_warning = true;
        }
        else if ( arg == "error" ) {
          inject_error   = true;
        }
        else if ( arg == "fatal" ) {
          inject_fatal   = true;
        }
      }
      else {
        REPORT( WARNING, "Ignoring unknown command-line argument: '" << arg << "'!?" );
      }

    }//endfor

    if ( test_reporting ) {
      INFO( ALWAYS,  "Testing always verbosity message in " << __func__ );
      INFO( LOW,     "Testing low    verbosity message in " << __func__ );
      INFO( MEDIUM,  "Testing medium verbosity message in " << __func__ );
      INFO( HIGH,    "Testing high   verbosity message in " << __func__ );
      INFO( DEBUG,   "Testing debug  verbosity message in " << __func__ );

      if ( inject_warning ) {
        REPORT( WARNING, "Testing warning" );
      }

      if ( inject_error ) {
        REPORT( ERROR,   "Testing error" );
      }

      if ( inject_fatal ) {
        REPORT( FATAL,   "Testing fatal" );
      }
      REPORT(INFO,"Done testing " << __func__);
    }
  }
}//endnamespace

///////////////////////////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
//END $Id$
