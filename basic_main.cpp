//FILE basic_main.cpp (systemc)
// $Info: Entry point for executing simulation for 'basic'.$
//-----------------------------------------------------------------------------
//#include "main.h"
#include "basic_top.h"
#include "wallclock.h"
#include "report.h"
std::ostringstream mout;

namespace {
  const char* MSGID = "/Doulos Inc/{:PROJECT:}/main";
  double elaboration_time=-1.0, starting_time=-1.0, finished_time=-1.0;
  int summary(void);
}

int sc_main(int argc, char *argv[])
{
  Basic_top* basic_top;
  // Elaborate
  elaboration_time = get_cpu_time();
  try {
    basic_top = new Basic_top("basic_top");
  } catch (sc_core::sc_exception& e) {
    REPORT(INFO,"\n" << e.what() << "\n\n*** Please fix elaboration errors and retry. ***");
    return summary();
  } catch (std::exception& e) {
    REPORT(INFO,"\n" << e.what() << "\n\n*** Please fix elaboration errors and retry. ***");
    return summary();
  } catch (...) {
    REPORT(INFO,"\n Error: *** Caught unknown exception during elaboration. ***");
    return summary();
  }//endtry

  // Simulate
  try {
    REPORT(INFO,"Starting kernel");
    starting_time = get_cpu_time();
    sc_core::sc_start();
    finished_time = get_cpu_time();
    REPORT(INFO,"Exited kernel at " << sc_core::sc_time_stamp());
  } catch (sc_core::sc_exception& e) {
    REPORT(WARNING,"\n\nCaught exception during active simulation.\n" << e.what());
  } catch (std::exception& e) {
    REPORT(WARNING,"\n\nCaught exception during active simulation.\n" << e.what());
  } catch (...) {
    REPORT(WARNING,"Error: Caught unknown exception during active simulation.");
  }//endtry

  // Clean up
  if (! sc_core::sc_end_of_simulation_invoked()) {
    try {
      REPORT(INFO,"ERROR: Simulation stopped without explicit sc_stop()");
    } catch(sc_core::sc_exception& e) { REPORT(INFO,"\n\n" << e.what()); }
    sc_core::sc_stop(); //< this will invoke end_of_simulation() callbacks
  }//endif

  return summary();

}

//-----------------------------------------------------------------------------
namespace {
  // Summarize results
  int summary(void)
  {
    std::string kind = "Simulation";
    if ( starting_time < 0.0 ) {
      kind = "Elaboration";
      starting_time = finished_time = get_cpu_time();
    } 
    if ( finished_time < 0.0 ) {
      finished_time = get_cpu_time();
    }
    auto errors = sc_core::sc_report_handler::get_count(sc_core::SC_ERROR)
                + sc_core::sc_report_handler::get_count(sc_core::SC_FATAL);
    REPORT(INFO, "\n" << std::string(80,'#') << "\nSummary for " << sc_core::sc_argv()[0] << ":\n  "
      << "CPU elaboration time " << std::setprecision(4) << (starting_time - elaboration_time) << " sec\n  "
      << "CPU simulation  time " << std::setprecision(4) << (finished_time - starting_time) << " sec\n  "
      << std::setw(2) << sc_core::sc_report_handler::get_count(sc_core::SC_WARNING) << " warnings" << "\n  "
      << std::setw(2) << sc_core::sc_report_handler::get_count(sc_core::SC_ERROR)   << " errors"   << "\n  "
      << std::setw(2) << sc_core::sc_report_handler::get_count(sc_core::SC_FATAL)   << " fatals"   << "\n\n"
      << kind << " " << (errors?"FAILED":"PASSED")
    );
    return (errors?1:0);
  }
}

///////////////////////////////////////////////////////////////////////////////
// -*- C++ -*- vim:sw=2:tw=0:fdm=marker:fmr=<<<,>>>
//END main.cpp $Id$ >>>}
