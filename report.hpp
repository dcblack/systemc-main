//@brief: Improve reporting providing two macros, REPORT and INFO, that allow
// for streaming syntax like cout. Also add macros to aid initial development
// with NOT_YET_IMPLEMENTED and TODO.
//
//@Syntax:
//   REPORT(message_type, message_stream);
//   INFO(verbosity_level, message_stream);
//   TODO(message_stream);
//   NOT_YET_IMPLEMENTED();
//
//   message types are: FATAL, ERROR, WARNING, and INFO
//   verbosity levels are: ALWAYS, LOW, MEDIUM, HIGH, DEBUG
//
// Assumes you define in every source file:
//
//   #include "report.hpp"
//   namespace {
//     const char* MSGID{"/Company/Group/Project/Module"};
//   }

//@Example:
//   #include "report.hpp"
//   namespace {
//     const char* MSGID{"/Doulos/Example/Report"};
//   }
//   REPORT(ERROR,"Data " << data << " doesn't match expected " << expected);
//   INFO(DEBUG,"Packet contains " << packet);
//   TODO("Fix report handler to remove blank line after REPORT_INFO");
//   NOT_YET_IMPLEMENTED();
//

#ifndef REPORT_HPP
#define REPORT_HPP
#include <systemc>
#include <sstream>
#include <iomanip>
extern std::ostringstream mout;
#define REPORT(message_type,message_stream) \
do {\
  mout.str("");\
  mout << std::dec << message_stream << std::ends;\
  SC_REPORT_##message_type(MSGID,mout.str().c_str());\
} while (0)

#define SC_ALWAYS SC_NONE
#define INFO(verbosity_level,message_stream) \
do {\
  if(sc_core::sc_report_handler::get_verbosity_level() >= sc_core::SC_##verbosity_level) {\
    mout.str("");\
    mout << std::dec << message_stream << " at " << sc_core::sc_time_stamp() << std::ends;\
    SC_REPORT_INFO_VERB(MSGID,mout.str().c_str(),sc_core::SC_##verbosity_level);\
  }\
} while (0)

#define TODO(message_stream) REPORT( WARNING, "TODO: " << message_stream )
#define NOT_YET_IMPLEMENTED() REPORT( WARNING, __func__ << " is not yet implemented." )

#endif