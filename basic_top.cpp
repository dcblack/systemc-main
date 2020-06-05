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
#include <map>
#include <algorithm>
#include <cctype>
using namespace sc_core;
using namespace std;

// Private stuff (similar to using static variables in C)
namespace {
  const char* const MSGID="/Doulos Inc/SystemC-Example/basic_top";
  const char* const RCSID="/$Id$";
  void parse_command_line( void );
  const char* message_type( decltype(SC_INFO) type );
  auto simplify = [](unsigned char c){ return (c == '-')?'_':std::tolower(c); };
  void inject_summary( void );
  void inject_errors( void );
  std::multimap<decltype(SC_RUNNING),decltype(SC_INFO)> inject_mmap;
}

////////////////////////////////////////////////////////////////////////////>>/
// Constructor <<
Basic_top::Basic_top(sc_module_name instance_name)
: sc_module(instance_name)
{
  parse_command_line();
  // Connectivity -- NONE
  // Processes
  SC_HAS_PROCESS(Basic_top);
  SC_THREAD(Basic_thread);
  inject_errors();
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
  inject_errors();
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::end_of_elaboration(void)
{
  REPORT(INFO,"End of elaboration");
  inject_errors();
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::start_of_simulation( void )
{
  REPORT(INFO,"Start of simulation");
  inject_errors();
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::end_of_simulation(void)
{
  REPORT(INFO,"End of simulation");
  inject_errors();
}

////////////////////////////////////////////////////////////////////////////>>/
void Basic_top::Basic_thread( void )
{
  REPORT(INFO,"Executing " << __func__ << " with a simple 42 second delay.");
  inject_errors();
  wait(42,SC_SEC);
  REPORT(INFO,"Shutting down simulation");
  sc_stop();
}

////////////////////////////////////////////////////////////////////////////>>/
namespace {

  //----------------------------------------------------------------------------
  void parse_command_line( void )
  {
    bool test_reporting( false );
    auto inject_when = SC_RUNNING;

    INFO(ALWAYS,"Parsing command-line");

    for ( int i = 1; i < sc_argc(); ++i ) {
      string arg( sc_argv()[i] );

      if ( arg == "-help" ) {
          REPORT(FATAL, ""
          << "Options\n"
          << "-------\n"
          << "\n"
          << "+ -test\n"
          << "+ -help\n"
          << "+ -verbosity none|low|medium|high|debug\n"
          << "+ -debug\n"
          << "+ -when <STATE>\n"
          << "  + Where <STATE> is one of:\n"
          << "    | elab | beoe | eoe | sos | sim | psd | eos\n"
          << "    | stop | elaboration | before_end_of_elaboration\n"
          << "    | end_of_elaboration | start_of_simulation\n"
          << "    | running | paused | end_of_simulation | stoppped\n"
          << "+ -inject warning|error|fatal\n"
          << "\n"
          );
      } else if ( arg == "-test" or arg == "-t" ) {
          INFO(ALWAYS,"Testing");
          test_reporting = true;
      } else if ( arg == "-verbosity" or arg == "-v" ) {
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
      } else if ( arg == "-debug" ) {
        sc_report_handler::set_verbosity_level( SC_DEBUG );
        INFO( ALWAYS,"Debugging" );
      } else if ( arg == "-when" or arg == "-w" ) {
        if( i == sc_argc() ) {
          REPORT( WARNING, "Ignoring -inject missing an argument" );
          continue;
        }
        arg = string(sc_argv()[++i]);
        std::transform( arg.begin(), arg.end(), arg.begin(), simplify );
        if ( arg == "elaboration"                      or arg == "elab" ) {
          inject_when = SC_ELABORATION;
        } else if ( arg == "before_end_of_elaboration" or arg == "beoe" ) {
          inject_when = SC_END_OF_ELABORATION;
        } else if ( arg == "end_of_elaboration"        or arg == "eoe" ) {
          inject_when = SC_END_OF_ELABORATION;
        } else if ( arg == "start_of_simulation"       or arg == "sos" ) {
          inject_when = SC_START_OF_SIMULATION;
        } else if ( arg == "running"                   or arg == "sim" ) {
          inject_when = SC_RUNNING;
        } else if ( arg == "paused"                    or arg == "psd" ) {
          inject_when = SC_PAUSED;
        } else if ( arg == "end_of_simulation"         or arg == "eos" ) {
          inject_when = SC_END_OF_SIMULATION;
        } else if ( arg == "stopped"                   or arg == "stop" ) {
          inject_when = SC_END_OF_SIMULATION;
	} else {
	  REPORT( WARNING, "Ignoring unknown -when type: '" << arg << "'!?" );
        }
      } else if ( arg == "-inject"                    or arg == "-i") {
        if( i == sc_argc() ) {
          REPORT( WARNING, "Ignoring -inject missing an argument" );
          continue;
        }
        arg = string(sc_argv()[++i]);
        std::transform( arg.begin(), arg.end(), arg.begin(), simplify );
        INFO( ALWAYS,"Injecting " << arg );
        if ( arg == "warning" ) {
          inject_mmap.insert(std::make_pair(inject_when,SC_WARNING));
        }
	else if ( arg == "error" ) {
          inject_mmap.insert(std::make_pair(inject_when,SC_ERROR));
        }
	else if ( arg == "fatal" ) {
          inject_mmap.insert(std::make_pair(inject_when,SC_FATAL));
        }
        else {
	  REPORT( WARNING, "Ignoring unknown -inject type: '" << arg << "'!?" );
        }
      } else {
        REPORT( WARNING, "Ignoring unknown command-line argument: '" << arg << "'!?" );
      }
    }//endfor

    inject_summary();

    if ( test_reporting ) {
      INFO( ALWAYS,  "Testing always verbosity message in " << __func__ );
      INFO( LOW,     "Testing low    verbosity message in " << __func__ );
      INFO( MEDIUM,  "Testing medium verbosity message in " << __func__ );
      INFO( HIGH,    "Testing high   verbosity message in " << __func__ );
      INFO( DEBUG,   "Testing debug  verbosity message in " << __func__ );

    }
  }//end parse_command_line()

  const char* message_type( decltype(SC_INFO) type )
  {
    switch (type) {
      case SC_INFO:    return "Info";
      case SC_WARNING: return "Warning";
      case SC_ERROR:   return "Error";
      case SC_FATAL:   return "Fatal";
      default:         return "UNKNOWN";
    }
  }

  //----------------------------------------------------------------------------
  void inject_summary( void )
  {
    for( const auto& p : inject_mmap ) {
	INFO( ALWAYS, p.first << " -> " << message_type(p.second) );
    }
  }

  //----------------------------------------------------------------------------
  void inject_errors( void )
  {
      auto range = inject_mmap.equal_range( sc_get_status() );
      for( auto it=range.first; it!=range.second; ++it) {
        if ( it->second == SC_WARNING ) {
          REPORT( WARNING, "Testing warning" );
        } else if ( it->second == SC_ERROR ) {
          REPORT( ERROR,   "Testing error" );
        } else if ( it->second == SC_FATAL ) {
          REPORT( FATAL,   "Testing fatal" );
        }
      }
  }//end inject_errors

}//endnamespace

///////////////////////////////////////////////////////////////////////////////
// Copyright 2018 Doulos Inc. All rights reserved.
// Licensed under Apache 2.0 - see accompanying LICENSE FILE.
//END $Id$
